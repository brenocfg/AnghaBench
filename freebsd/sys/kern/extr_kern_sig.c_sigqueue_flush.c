#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct proc {int /*<<< orphan*/  p_pendingcnt; } ;
struct TYPE_7__ {int sq_flags; int /*<<< orphan*/  sq_ptrace; int /*<<< orphan*/  sq_kill; int /*<<< orphan*/  sq_signals; int /*<<< orphan*/  sq_list; struct proc* sq_proc; } ;
typedef  TYPE_1__ sigqueue_t ;
struct TYPE_8__ {int /*<<< orphan*/ * ksi_sigq; } ;
typedef  TYPE_2__ ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGEMPTYSET (int /*<<< orphan*/ ) ; 
 int SQ_INIT ; 
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksi_link ; 
 scalar_t__ ksiginfo_tryfree (TYPE_2__*) ; 

void
sigqueue_flush(sigqueue_t *sq)
{
	struct proc *p = sq->sq_proc;
	ksiginfo_t *ksi;

	KASSERT(sq->sq_flags & SQ_INIT, ("sigqueue not inited"));

	if (p != NULL)
		PROC_LOCK_ASSERT(p, MA_OWNED);

	while ((ksi = TAILQ_FIRST(&sq->sq_list)) != NULL) {
		TAILQ_REMOVE(&sq->sq_list, ksi, ksi_link);
		ksi->ksi_sigq = NULL;
		if (ksiginfo_tryfree(ksi) && p != NULL)
			p->p_pendingcnt--;
	}

	SIGEMPTYSET(sq->sq_signals);
	SIGEMPTYSET(sq->sq_kill);
	SIGEMPTYSET(sq->sq_ptrace);
}