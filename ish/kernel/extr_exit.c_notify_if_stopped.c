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
struct task {TYPE_1__* group; } ;
typedef  scalar_t__ dword_t ;
typedef  scalar_t__ addr_t ;
struct TYPE_2__ {scalar_t__ group_exit_code; int /*<<< orphan*/  stopped; } ;

/* Variables and functions */
 int _EFAULT ; 
 scalar_t__ user_put (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool notify_if_stopped(struct task *task, addr_t status_addr) {
    // FIXME the check of task->group->stopped needs locking I think
    if (!task->group->stopped || task->group->group_exit_code == 0)
        return false;
    dword_t exit_code = task->group->group_exit_code;
    task->group->group_exit_code = 0;
    if (status_addr != 0)
        if (user_put(status_addr, exit_code))
            return _EFAULT;
    return true;
}