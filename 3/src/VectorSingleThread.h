#include <random>
#include <cmath>
#include "Vector.h"
#include "IOperations.h"

template <typename T>
class VectorSingleThread : public Vector<T>, public IOperations<T> {
public:
    VectorSingleThread(size_t n) : Vector<T>(n) {}

    ~VectorSingleThread() {}

    void initializedConst(T value) override {
        if (value == 0){
            throw std::runtime_error("Деление на ноль запрещено");
        }

        for (auto& elem : this->data) {
            elem = value;
        }
        this->isInitialized = true;
    }

    void initializedRandom(int startRandomValue, int endRandomValue) override {
        if (startRandomValue == 0 || endRandomValue == 0) {
            throw std::runtime_error("Деление на ноль запрещено");
        }

        if (!(startRandomValue < endRandomValue)) {
            throw std::invalid_argument("Начальное значение должно быть меньше конечного");
        }

        std::random_device randomDevice;
        std::mt19937 randomGenerator(randomDevice());
        std::uniform_int_distribution<std::mt19937::result_type> randomRange(startRandomValue, endRandomValue);

        for (auto& elem : this->data) {
            elem = randomRange(randomGenerator);
        }
        this->isInitialized = true;
    }

    void invertValues() override {
        this->checkInitialization();

        /* Проверка на ноль в методах для работы с данными, 
        чтобы не нагружать лишний раз вычислительные методы */ 
        for (auto& value : this->data) {
            value = static_cast<T>(1) / value;
        }
    }

    T minimumValue() override {
        this->checkInitialization();
        
        T minValue = this->data[0];
        for (const T& elem : this->data) {
            if (elem < minValue) {
                minValue = elem;
            }
        }
        return minValue;
    }

    size_t minimumIndexByValue() override {
        this->checkInitialization();
        
        T minValue = this->data[0];
        size_t minIndex = 0;
        
        for (size_t i = 1; i < this->data.size(); ++i) {
            if (this->data[i] < minValue) {
                minValue = this->data[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    T maximumValue() override {
        this->checkInitialization();
        
        T maxValue = this->data[0];
        for (const T& elem : this->data) {
            if (elem > maxValue) {
                maxValue = elem;
            }
        }
        return maxValue;
    }

    size_t maximumIndexByValue() override {
        this->checkInitialization();
        
        T maxValue = this->data[0];
        size_t maxIndex = 0;
        
        for (size_t i = 1; i < this->data.size(); ++i) {
            if (this->data[i] > maxValue) {
                maxValue = this->data[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    T avgValue() override {
        this->checkInitialization();
        return static_cast<T>(sumValue()) / this->data.size();
    }

    unsigned __int32 sumValue() override {
        this->checkInitialization();

        T sum = T(0);
        for (const T& elem : this->data) {
            sum += elem;
        }
        return sum;
    }

    unsigned __int64 euclidMonheton() override {
        this->checkInitialization();

        T sumOfSquares = T(0);
        for (const T& elem : this->data) {
            sumOfSquares += elem * elem;
        }
        return std::sqrt(static_cast<T>(sumOfSquares));
    }

    unsigned __int32 scalarMultiply(const Vector<T>& other) override {
        this->checkInitialization();
        
        if (this->data.size() != other.getData().size()) {
            throw std::invalid_argument("Размеры векторов не совпадают");
        }
        
        T productSum = T(0);
        for (size_t i = 0; i < this->data.size(); ++i) {
            productSum += this->data[i] * other.getData()[i];
        }
        return productSum;
    }
};