#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__* wakeup_fds; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror (char*) ; 
 TYPE_1__ talk_data ; 
 scalar_t__ write (scalar_t__,char*,int) ; 

__attribute__((used)) static void
wakeup_talk_loop(bool in_signal_handler) {
    if (talk_data.wakeup_fds[1] <= 0) return;
    while(true) {
        ssize_t ret = write(talk_data.wakeup_fds[1], "w", 1);
        if (ret < 0) {
            if (errno == EINTR) continue;
            if (!in_signal_handler) perror("Failed to write to talk wakeup fd with error");
        }
        break;
    }
}