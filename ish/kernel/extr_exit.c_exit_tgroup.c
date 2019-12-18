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
struct tgroup {int /*<<< orphan*/  pgroup; scalar_t__ timer; int /*<<< orphan*/  threads; } ;
struct task {int /*<<< orphan*/  group_links; struct tgroup* group; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_leave_session (struct task*) ; 
 int /*<<< orphan*/  timer_free (scalar_t__) ; 

__attribute__((used)) static bool exit_tgroup(struct task *task) {
    struct tgroup *group = task->group;
    list_remove(&task->group_links);
    bool group_dead = list_empty(&group->threads);
    if (group_dead) {
        // don't need to lock the group since the only pointers it come from:
        // - other threads current->group, but the other threads have accessed it
        // - locking pids_lock first, which do_exit did
        if (group->timer)
            timer_free(group->timer);
        task_leave_session(task);
        list_remove(&group->pgroup);
    }
    return group_dead;
}