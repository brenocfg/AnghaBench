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
struct task_struct {int /*<<< orphan*/  pid; } ;
struct proc {int p_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_WEXIT ; 
 struct proc* pfind (int /*<<< orphan*/ ) ; 

bool
linux_task_exiting(struct task_struct *task)
{
	struct proc *p;
	bool ret;

	ret = false;
	p = pfind(task->pid);
	if (p != NULL) {
		if ((p->p_flag & P_WEXIT) != 0)
			ret = true;
		PROC_UNLOCK(p);
	}
	return (ret);
}