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
struct TYPE_3__ {size_t read_buf_sz; scalar_t__ new_input_at; scalar_t__ read_buf; } ;
typedef  TYPE_1__ Screen ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EIO ; 
 size_t READ_BUF_SZ ; 
 scalar_t__ UNLIKELY (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ monotonic () ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ read (int,scalar_t__,size_t) ; 
 int /*<<< orphan*/  screen_mutex (int /*<<< orphan*/ ,scalar_t__ (*) (int,scalar_t__,size_t)) ; 
 int /*<<< orphan*/  unlock ; 

__attribute__((used)) static bool
read_bytes(int fd, Screen *screen) {
    ssize_t len;
    size_t available_buffer_space, orig_sz;

    screen_mutex(lock, read);
    orig_sz = screen->read_buf_sz;
    if (orig_sz >= READ_BUF_SZ) { screen_mutex(unlock, read); return true; }  // screen read buffer is full
    available_buffer_space = READ_BUF_SZ - orig_sz;
    screen_mutex(unlock, read);

    while(true) {
        len = read(fd, screen->read_buf + orig_sz, available_buffer_space);
        if (len < 0) {
            if (errno == EINTR || errno == EAGAIN) continue;
            if (errno != EIO) perror("Call to read() from child fd failed");
            return false;
        }
        break;
    }
    if (UNLIKELY(len == 0)) return false;

    screen_mutex(lock, read);
    if (screen->new_input_at == 0) screen->new_input_at = monotonic();
    if (orig_sz != screen->read_buf_sz) {
        // The other thread consumed some of the screen read buffer
        memmove(screen->read_buf + screen->read_buf_sz, screen->read_buf + orig_sz, len);
    }
    screen->read_buf_sz += len;
    screen_mutex(unlock, read);
    return true;
}