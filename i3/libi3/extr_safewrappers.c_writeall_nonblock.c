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
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int write (int,char*,size_t) ; 

ssize_t writeall_nonblock(int fd, const void *buf, size_t count) {
    size_t written = 0;

    while (written < count) {
        const ssize_t n = write(fd, ((char *)buf) + written, count - written);
        if (n == -1) {
            if (errno == EAGAIN) {
                return written;
            } else if (errno == EINTR) {
                continue;
            } else {
                return n;
            }
        }
        written += (size_t)n;
    }
    return written;
}