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
struct TYPE_2__ {scalar_t__ pid; scalar_t__ cont_signal; scalar_t__ stopped; } ;

/* Variables and functions */
 scalar_t__ SIGTERM ; 
 TYPE_1__ child ; 
 int /*<<< orphan*/  killpg (scalar_t__,scalar_t__) ; 

void kill_child_at_exit(void) {
    if (child.pid > 0) {
        if (child.cont_signal > 0 && child.stopped)
            killpg(child.pid, child.cont_signal);
        killpg(child.pid, SIGTERM);
    }
}