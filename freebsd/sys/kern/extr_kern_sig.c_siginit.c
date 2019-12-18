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
struct sigacts {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_sigignore; } ;
struct proc {struct sigacts* p_sigacts; } ;

/* Variables and functions */
 int NSIG ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SIGADDSET (int /*<<< orphan*/ ,int) ; 
 int SIGCONT ; 
 int SIGPROP_IGNORE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int sigprop (int) ; 

void
siginit(struct proc *p)
{
	int i;
	struct sigacts *ps;

	PROC_LOCK(p);
	ps = p->p_sigacts;
	mtx_lock(&ps->ps_mtx);
	for (i = 1; i <= NSIG; i++) {
		if (sigprop(i) & SIGPROP_IGNORE && i != SIGCONT) {
			SIGADDSET(ps->ps_sigignore, i);
		}
	}
	mtx_unlock(&ps->ps_mtx);
	PROC_UNLOCK(p);
}