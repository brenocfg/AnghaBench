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
struct thread {int dummy; } ;
struct procctl_reaper_kill {int /*<<< orphan*/  rk_fpid; int /*<<< orphan*/  rk_killed; int /*<<< orphan*/  rk_sig; } ;
struct proc {int /*<<< orphan*/  p_pid; } ;
typedef  int /*<<< orphan*/  ksiginfo_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int p_cansignal (struct thread*,struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pksignal (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
reap_kill_proc(struct thread *td, struct proc *p2, ksiginfo_t *ksi,
    struct procctl_reaper_kill *rk, int *error)
{
	int error1;

	PROC_LOCK(p2);
	error1 = p_cansignal(td, p2, rk->rk_sig);
	if (error1 == 0) {
		pksignal(p2, rk->rk_sig, ksi);
		rk->rk_killed++;
		*error = error1;
	} else if (*error == ESRCH) {
		rk->rk_fpid = p2->p_pid;
		*error = error1;
	}
	PROC_UNLOCK(p2);
}