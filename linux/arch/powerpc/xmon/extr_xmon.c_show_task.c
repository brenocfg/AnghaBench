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
struct TYPE_3__ {int /*<<< orphan*/  ksp; } ;
struct task_struct {char state; int exit_state; int /*<<< orphan*/  comm; int /*<<< orphan*/  parent; int /*<<< orphan*/  pid; TYPE_1__ thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EXIT_DEAD ; 
 int EXIT_ZOMBIE ; 
 char TASK_INTERRUPTIBLE ; 
 char TASK_STOPPED ; 
 char TASK_TRACED ; 
 char TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  printf (char*,struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_cpu (struct task_struct*) ; 

__attribute__((used)) static void show_task(struct task_struct *tsk)
{
	char state;

	/*
	 * Cloned from kdb_task_state_char(), which is not entirely
	 * appropriate for calling from xmon. This could be moved
	 * to a common, generic, routine used by both.
	 */
	state = (tsk->state == 0) ? 'R' :
		(tsk->state < 0) ? 'U' :
		(tsk->state & TASK_UNINTERRUPTIBLE) ? 'D' :
		(tsk->state & TASK_STOPPED) ? 'T' :
		(tsk->state & TASK_TRACED) ? 'C' :
		(tsk->exit_state & EXIT_ZOMBIE) ? 'Z' :
		(tsk->exit_state & EXIT_DEAD) ? 'E' :
		(tsk->state & TASK_INTERRUPTIBLE) ? 'S' : '?';

	printf("%px %016lx %6d %6d %c %2d %s\n", tsk,
		tsk->thread.ksp,
		tsk->pid, rcu_dereference(tsk->parent)->pid,
		state, task_cpu(tsk),
		tsk->comm);
}