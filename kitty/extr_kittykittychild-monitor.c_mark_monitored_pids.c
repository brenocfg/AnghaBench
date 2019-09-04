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
typedef  size_t ssize_t ;
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {int status; scalar_t__ pid; } ;

/* Variables and functions */
 size_t arraysz (TYPE_1__*) ; 
 int /*<<< orphan*/  children_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 scalar_t__* monitored_pids ; 
 size_t monitored_pids_count ; 
 TYPE_1__* reaped_pids ; 
 size_t reaped_pids_count ; 
 int /*<<< orphan*/  remove_i_from_array (scalar_t__*,size_t,size_t) ; 
 int /*<<< orphan*/  unlock ; 

__attribute__((used)) static inline void
mark_monitored_pids(pid_t pid, int status) {
    children_mutex(lock);
    for (ssize_t i = monitored_pids_count - 1; i >= 0; i--) {
        if (pid == monitored_pids[i]) {
            if (reaped_pids_count < arraysz(reaped_pids)) {
                reaped_pids[reaped_pids_count].status = status;
                reaped_pids[reaped_pids_count++].pid = pid;
            }
            remove_i_from_array(monitored_pids, (size_t)i, monitored_pids_count);
        }
    }
    children_mutex(unlock);
}