#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 scalar_t__ pipe2 (int*,int) ; 

__attribute__((used)) static inline bool
self_pipe(int fds[2]) {
#ifdef __APPLE__
    int flags;
    flags = pipe(fds);
    if (flags != 0) return false;
    for (int i = 0; i < 2; i++) {
        flags = fcntl(fds[i], F_GETFD);
        if (flags == -1) {  return false; }
        if (fcntl(fds[i], F_SETFD, flags | FD_CLOEXEC) == -1) { return false; }
        flags = fcntl(fds[i], F_GETFL);
        if (flags == -1) { return false; }
        if (fcntl(fds[i], F_SETFL, flags | O_NONBLOCK) == -1) { return false; }
    }
    return true;
#else
    return pipe2(fds, O_CLOEXEC | O_NONBLOCK) == 0;
#endif
}