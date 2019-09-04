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
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * wakeup_fds ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int) ; 

void
wakeup_io_loop(bool in_signal_handler) {
    while(true) {
        ssize_t ret = write(wakeup_fds[1], "w", 1);
        if (ret < 0) {
            if (errno == EINTR) continue;
            if (!in_signal_handler) perror("Failed to write to wakeup fd with error");
        }
        break;
    }
}