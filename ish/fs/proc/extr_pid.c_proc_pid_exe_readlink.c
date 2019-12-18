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
struct task {TYPE_1__* mm; } ;
struct proc_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  exefile; } ;

/* Variables and functions */
 int _ESRCH ; 
 int generic_getpath (int /*<<< orphan*/ ,char*) ; 
 struct task* proc_get_task (struct proc_entry*) ; 
 int /*<<< orphan*/  proc_put_task (struct task*) ; 

__attribute__((used)) static int proc_pid_exe_readlink(struct proc_entry *entry, char *buf) {
    struct task *task = proc_get_task(entry);
    if (task == NULL)
        return _ESRCH;
    int err = generic_getpath(task->mm->exefile, buf);
    proc_put_task(task);
    return err;
}