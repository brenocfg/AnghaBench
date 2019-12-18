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
struct tgroup {scalar_t__ pgid; scalar_t__ sid; int /*<<< orphan*/  pgroup; int /*<<< orphan*/  session; TYPE_1__* leader; } ;
struct task {int /*<<< orphan*/  pid; struct tgroup* group; } ;
struct pid {int /*<<< orphan*/  pgroup; int /*<<< orphan*/  session; } ;
typedef  scalar_t__ pid_t_ ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 scalar_t__ _EPERM ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove_safe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 struct pid* pid_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pids_lock ; 
 int /*<<< orphan*/  task_leave_session (struct task*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

pid_t_ task_setsid(struct task *task) {
    lock(&pids_lock);
    struct tgroup *group = task->group;
    pid_t_ new_sid = group->leader->pid;
    if (group->pgid == new_sid || group->sid == new_sid) {
        unlock(&pids_lock);
        return _EPERM;
    }

    task_leave_session(task);
    struct pid *pid = pid_get(task->pid);
    list_add(&pid->session, &group->session);
    group->sid = new_sid;

    list_remove_safe(&group->pgroup);
    list_add(&pid->pgroup, &group->pgroup);
    group->pgid = new_sid;

    unlock(&pids_lock);
    return new_sid;
}