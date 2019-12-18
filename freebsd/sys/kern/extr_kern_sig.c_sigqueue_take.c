#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct proc {int /*<<< orphan*/  p_pendingcnt; } ;
struct ksiginfo {int /*<<< orphan*/  ksi_signo; } ;
struct TYPE_5__ {int /*<<< orphan*/  sq_signals; int /*<<< orphan*/  sq_ptrace; int /*<<< orphan*/  sq_kill; int /*<<< orphan*/  sq_list; struct proc* sq_proc; } ;
typedef  TYPE_1__ sigqueue_t ;
struct TYPE_6__ {int ksi_flags; int /*<<< orphan*/  ksi_signo; TYPE_1__* ksi_sigq; } ;
typedef  TYPE_2__ ksiginfo_t ;

/* Variables and functions */
 int KSI_EXT ; 
 int /*<<< orphan*/  SIGDELSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGISMEMBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ksiginfo* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct ksiginfo* TAILQ_NEXT (struct ksiginfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksi_link ; 

void
sigqueue_take(ksiginfo_t *ksi)
{
	struct ksiginfo *kp;
	struct proc	*p;
	sigqueue_t	*sq;

	if (ksi == NULL || (sq = ksi->ksi_sigq) == NULL)
		return;

	p = sq->sq_proc;
	TAILQ_REMOVE(&sq->sq_list, ksi, ksi_link);
	ksi->ksi_sigq = NULL;
	if (!(ksi->ksi_flags & KSI_EXT) && p != NULL)
		p->p_pendingcnt--;

	for (kp = TAILQ_FIRST(&sq->sq_list); kp != NULL;
	     kp = TAILQ_NEXT(kp, ksi_link)) {
		if (kp->ksi_signo == ksi->ksi_signo)
			break;
	}
	if (kp == NULL && !SIGISMEMBER(sq->sq_kill, ksi->ksi_signo) &&
	    !SIGISMEMBER(sq->sq_ptrace, ksi->ksi_signo))
		SIGDELSET(sq->sq_signals, ksi->ksi_signo);
}