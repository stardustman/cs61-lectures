#ifndef HELPERS_HH
#define HELPERS_HH
#include <unistd.h>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <csignal>
#include <ctime>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sched.h>
#include <errno.h>

// tstamp()
//    Return the current time as a double.

inline double tstamp() {
    struct timespec tv;
    clock_gettime(CLOCK_REALTIME, &tv);
    return tv.tv_sec + tv.tv_nsec * 1.0e-9;
}


// set_signal_handler(signo, handler)
//    Install `handler` as the signal handler for `signo`.
//    The `handler` is automatically re-installed after signal delivery.
//    Has the same interface as `signal()` (`man 2 signal`), but is portable.

inline int set_signal_handler(int signo, void (*handler)(int)) {
    struct sigaction sa;
    sa.sa_handler = handler;    // call `handler` on signal
    sigemptyset(&sa.sa_mask);   // don't block other signals in handler
    sa.sa_flags = 0;            // don't restart system calls
    return sigaction(signo, &sa, nullptr);
}

#endif
