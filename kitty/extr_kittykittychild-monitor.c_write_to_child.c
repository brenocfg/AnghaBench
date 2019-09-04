#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {size_t write_buf_used; scalar_t__ write_buf; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  screen_mutex (int /*<<< orphan*/ ,scalar_t__ (*) (int,scalar_t__,size_t)) ; 
 int /*<<< orphan*/  unlock ; 
 scalar_t__ write (int,scalar_t__,size_t) ; 

__attribute__((used)) static inline void
write_to_child(int fd, Screen *screen) {
    size_t written = 0;
    ssize_t ret = 0;
    screen_mutex(lock, write);
    while (written < screen->write_buf_used) {
        ret = write(fd, screen->write_buf + written, screen->write_buf_used - written);
        if (ret > 0) { written += ret; }
        else if (ret == 0) {
            // could mean anything, ignore
            break;
        } else {
            if (errno == EINTR) continue;
            if (errno == EWOULDBLOCK || errno == EAGAIN) break;
            perror("Call to write() to child fd failed, discarding data.");
            written = screen->write_buf_used;
        }
    }
    if (written) {
        screen->write_buf_used -= written;
        if (screen->write_buf_used) {
            memmove(screen->write_buf, screen->write_buf + written, screen->write_buf_used);
        }
    }
    screen_mutex(unlock, write);
}