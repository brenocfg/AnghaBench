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
struct task {int dummy; } ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int WUNTRACED_ ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ notify_if_stopped (struct task*,int /*<<< orphan*/ ) ; 
 scalar_t__ reap_if_zombie (struct task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_is_leader (struct task*) ; 

__attribute__((used)) static bool reap_if_needed(struct task *task, int_t options, addr_t status_addr, addr_t rusage_addr) {
    assert(task_is_leader(task));
    if (options & WUNTRACED_ && notify_if_stopped(task, status_addr))
        return true;
    if (reap_if_zombie(task, status_addr, rusage_addr))
        return true;
    return false;
}