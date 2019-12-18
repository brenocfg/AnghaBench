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
struct proc_entry {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 struct task* pid_get_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pids_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct task *proc_get_task(struct proc_entry *entry) {
    lock(&pids_lock);
    struct task *task = pid_get_task(entry->pid);
    if (task == NULL)
        unlock(&pids_lock);
    return task;
}