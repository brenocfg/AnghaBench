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
struct task {int /*<<< orphan*/  queue; scalar_t__ waiting; scalar_t__ pending; scalar_t__ blocked; int /*<<< orphan*/ * vfork; scalar_t__ clear_tid; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task*) ; 
 int PTR_ERR (struct task*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct task* construct_task (struct task*) ; 
 struct task* current ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 struct task* pid_get_task (int) ; 

int become_new_init_child() {
    // locking? who needs locking?!
    struct task *init = pid_get_task(1);
    assert(init != NULL);

    struct task *task = construct_task(init);
    if (IS_ERR(task))
        return PTR_ERR(task);

    // these are things we definitely don't want to inherit
    task->clear_tid = 0;
    task->vfork = NULL;
    task->blocked = task->pending = task->waiting = 0;
    list_init(&task->queue);
    // TODO: think about whether it would be a good idea to inherit fs_info

    current = task;
    return 0;
}