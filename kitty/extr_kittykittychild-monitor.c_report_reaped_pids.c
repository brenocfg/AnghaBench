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
struct TYPE_2__ {int /*<<< orphan*/  status; scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_boss (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  children_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  on_monitored_pid_death ; 
 TYPE_1__* reaped_pids ; 
 size_t reaped_pids_count ; 
 int /*<<< orphan*/  unlock ; 

__attribute__((used)) static inline void
report_reaped_pids() {
    children_mutex(lock);
    if (reaped_pids_count) {
        for (size_t i = 0; i < reaped_pids_count; i++) {
            call_boss(on_monitored_pid_death, "ii", (int)reaped_pids[i].pid, reaped_pids[i].status);
        }
        reaped_pids_count = 0;
    }
    children_mutex(unlock);
}