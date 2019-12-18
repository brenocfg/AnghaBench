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
struct proc {int /*<<< orphan*/  p_lock; } ;

/* Variables and functions */
 struct proc* curproc ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psignal (struct proc*,int) ; 

void
rumptest_localsig(int signo)
{
	struct proc *p = curproc;

	mutex_enter(p->p_lock);
	psignal(p, signo);
	mutex_exit(p->p_lock);
}