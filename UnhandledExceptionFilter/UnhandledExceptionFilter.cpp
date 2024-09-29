#include <windows.h>
#include <iostream>
#include <fstream>
#include <ctime>

// Function to write crash information to a log file
void WriteCrashInfo(const std::string& info) {
    std::ofstream logFile("crash_log.txt", std::ios::app);
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
       //  logFile << "Crash Time: " << std::ctime(&now);
        logFile << info << std::endl;
        logFile.close();
    }
}

// Custom unhandled exception filter
LONG WINAPI CustomUnhandledExceptionFilter(EXCEPTION_POINTERS* exceptionInfo) {
    std::string crashInfo = "Unhandled Exception Occurred\n";
    crashInfo += "Exception Code: " + (exceptionInfo->ExceptionRecord->ExceptionCode);
    // crashInfo += "Exception Address: " + (exceptionInfo->ExceptionRecord->;

    WriteCrashInfo(crashInfo);

    // Pass the exception to the next handler
    return EXCEPTION_EXECUTE_HANDLER;
}

int main() {
    // Set the custom unhandled exception filter
    SetUnhandledExceptionFilter(CustomUnhandledExceptionFilter);

    // Code that causes a crash (divide by zero)
    int* ptr = nullptr;
    *ptr = 42;  // This will cause an access violation


    std::cout << "This line will not be executed." << std::endl;

    return 0;
}