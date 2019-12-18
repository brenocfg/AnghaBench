#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tgroup {TYPE_1__* tty; int /*<<< orphan*/  sid; int /*<<< orphan*/  session; } ;
struct task {struct tgroup* group; } ;
struct TYPE_4__ {int /*<<< orphan*/  session; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; scalar_t__ session; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove_safe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 TYPE_2__* pid_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_release (TYPE_1__*) ; 
 int /*<<< orphan*/  ttys_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void task_leave_session(struct task *task) {
    struct tgroup *group = task->group;
    list_remove_safe(&group->session);
    if (group->tty) {
        lock(&ttys_lock);
        if (list_empty(&pid_get(group->sid)->session)) {
            lock(&group->tty->lock);
            group->tty->session = 0;
            unlock(&group->tty->lock);
        }
        tty_release(group->tty);
        group->tty = NULL;
        unlock(&ttys_lock);
    }
}