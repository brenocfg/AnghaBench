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
struct winsize {int dummy; } ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ EINTR ; 
 scalar_t__ ENOTTY ; 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 scalar_t__ errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  log_error (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static inline bool
pty_resize(int fd, struct winsize *dim) {
    while(true) {
        if (ioctl(fd, TIOCSWINSZ, dim) == -1) {
            if (errno == EINTR) continue;
            if (errno != EBADF && errno != ENOTTY) {
                log_error("Failed to resize tty associated with fd: %d with error: %s", fd, strerror(errno));
                return false;
            }
        }
        break;
    }
    return true;
}