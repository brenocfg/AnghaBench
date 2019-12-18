#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_2__* td_ucred; TYPE_1__* td_proc; } ;
struct reap_kill_tracker_head {int dummy; } ;
struct reap_kill_tracker {struct proc* parent; } ;
struct procctl_reaper_kill {scalar_t__ rk_sig; int rk_flags; int rk_fpid; scalar_t__ rk_subtree; scalar_t__ rk_killed; } ;
struct proc {int p_treeflag; scalar_t__ p_reapsubtree; int /*<<< orphan*/  p_reaplist; int /*<<< orphan*/  p_children; struct proc* p_reaper; } ;
struct TYPE_8__ {scalar_t__ ksi_signo; int /*<<< orphan*/  ksi_uid; int /*<<< orphan*/  ksi_pid; int /*<<< orphan*/  ksi_code; } ;
typedef  TYPE_3__ ksiginfo_t ;
struct TYPE_7__ {int /*<<< orphan*/  cr_ruid; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int ECAPMODE ; 
 int EINVAL ; 
 int ESRCH ; 
 scalar_t__ IN_CAPABILITY_MODE (struct thread*) ; 
 struct proc* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct proc* LIST_NEXT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_TREE_REAPER ; 
 int REAPER_KILL_CHILDREN ; 
 int REAPER_KILL_SUBTREE ; 
 int /*<<< orphan*/  SI_USER ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 struct reap_kill_tracker* TAILQ_FIRST (struct reap_kill_tracker_head*) ; 
 int /*<<< orphan*/  TAILQ_INIT (struct reap_kill_tracker_head*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct reap_kill_tracker_head*,struct reap_kill_tracker*,int /*<<< orphan*/ ) ; 
 scalar_t__ _SIG_MAXSIG ; 
 int /*<<< orphan*/  free (struct reap_kill_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_3__*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  p_reapsibling ; 
 int /*<<< orphan*/  p_sibling ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  reap_kill_proc (struct thread*,struct proc*,TYPE_3__*,struct procctl_reaper_kill*,int*) ; 
 int /*<<< orphan*/  reap_kill_sched (struct reap_kill_tracker_head*,struct proc*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reap_kill(struct thread *td, struct proc *p, struct procctl_reaper_kill *rk)
{
	struct proc *reap, *p2;
	ksiginfo_t ksi;
	struct reap_kill_tracker_head tracker;
	struct reap_kill_tracker *t;
	int error;

	sx_assert(&proctree_lock, SX_LOCKED);
	if (IN_CAPABILITY_MODE(td))
		return (ECAPMODE);
	if (rk->rk_sig <= 0 || rk->rk_sig > _SIG_MAXSIG ||
	    (rk->rk_flags & ~(REAPER_KILL_CHILDREN |
	    REAPER_KILL_SUBTREE)) != 0 || (rk->rk_flags &
	    (REAPER_KILL_CHILDREN | REAPER_KILL_SUBTREE)) ==
	    (REAPER_KILL_CHILDREN | REAPER_KILL_SUBTREE))
		return (EINVAL);
	PROC_UNLOCK(p);
	reap = (p->p_treeflag & P_TREE_REAPER) == 0 ? p->p_reaper : p;
	ksiginfo_init(&ksi);
	ksi.ksi_signo = rk->rk_sig;
	ksi.ksi_code = SI_USER;
	ksi.ksi_pid = td->td_proc->p_pid;
	ksi.ksi_uid = td->td_ucred->cr_ruid;
	error = ESRCH;
	rk->rk_killed = 0;
	rk->rk_fpid = -1;
	if ((rk->rk_flags & REAPER_KILL_CHILDREN) != 0) {
		for (p2 = LIST_FIRST(&reap->p_children); p2 != NULL;
		    p2 = LIST_NEXT(p2, p_sibling)) {
			reap_kill_proc(td, p2, &ksi, rk, &error);
			/*
			 * Do not end the loop on error, signal
			 * everything we can.
			 */
		}
	} else {
		TAILQ_INIT(&tracker);
		reap_kill_sched(&tracker, reap);
		while ((t = TAILQ_FIRST(&tracker)) != NULL) {
			MPASS((t->parent->p_treeflag & P_TREE_REAPER) != 0);
			TAILQ_REMOVE(&tracker, t, link);
			for (p2 = LIST_FIRST(&t->parent->p_reaplist); p2 != NULL;
			    p2 = LIST_NEXT(p2, p_reapsibling)) {
				if (t->parent == reap &&
				    (rk->rk_flags & REAPER_KILL_SUBTREE) != 0 &&
				    p2->p_reapsubtree != rk->rk_subtree)
					continue;
				if ((p2->p_treeflag & P_TREE_REAPER) != 0)
					reap_kill_sched(&tracker, p2);
				reap_kill_proc(td, p2, &ksi, rk, &error);
			}
			free(t, M_TEMP);
		}
	}
	PROC_LOCK(p);
	return (error);
}