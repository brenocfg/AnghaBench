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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EINTR ; 
 int errno ; 
 int /*<<< orphan*/ * signal_fds ; 
 scalar_t__ write (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void
handle_signal(int sig_num) {
    int save_err = errno;
    unsigned char byte = (unsigned char)sig_num;
    while(true) {
        ssize_t ret = write(signal_fds[1], &byte, 1);
        if (ret < 0 && errno == EINTR) continue;
        break;
    }
    errno = save_err;
}