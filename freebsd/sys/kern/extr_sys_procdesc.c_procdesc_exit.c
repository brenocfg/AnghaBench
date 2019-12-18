#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct procdesc {int pd_flags; TYPE_1__ pd_selinfo; int /*<<< orphan*/ * pd_proc; int /*<<< orphan*/  pd_xstat; } ;
struct proc {scalar_t__ p_pptr; scalar_t__ p_reaper; struct procdesc* p_procdesc; int /*<<< orphan*/  p_xsig; int /*<<< orphan*/  p_xexit; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KW_EXITCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NOTE_EXIT ; 
 int PDF_CLOSED ; 
 int PDF_EXITED ; 
 int PDF_SELECTED ; 
 int /*<<< orphan*/  PROCDESC_LOCK (struct procdesc*) ; 
 int /*<<< orphan*/  PROCDESC_UNLOCK (struct procdesc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  procdesc_free (struct procdesc*) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
procdesc_exit(struct proc *p)
{
	struct procdesc *pd;

	sx_assert(&proctree_lock, SA_XLOCKED);
	PROC_LOCK_ASSERT(p, MA_OWNED);
	KASSERT(p->p_procdesc != NULL, ("procdesc_exit: p_procdesc NULL"));

	pd = p->p_procdesc;

	PROCDESC_LOCK(pd);
	KASSERT((pd->pd_flags & PDF_CLOSED) == 0 || p->p_pptr == p->p_reaper,
	    ("procdesc_exit: closed && parent not reaper"));

	pd->pd_flags |= PDF_EXITED;
	pd->pd_xstat = KW_EXITCODE(p->p_xexit, p->p_xsig);

	/*
	 * If the process descriptor has been closed, then we have nothing
	 * to do; return 1 so that init will get SIGCHLD and do the reaping.
	 * Clean up the procdesc now rather than letting it happen during
	 * that reap.
	 */
	if (pd->pd_flags & PDF_CLOSED) {
		PROCDESC_UNLOCK(pd);
		pd->pd_proc = NULL;
		p->p_procdesc = NULL;
		procdesc_free(pd);
		return (1);
	}
	if (pd->pd_flags & PDF_SELECTED) {
		pd->pd_flags &= ~PDF_SELECTED;
		selwakeup(&pd->pd_selinfo);
	}
	KNOTE_LOCKED(&pd->pd_selinfo.si_note, NOTE_EXIT);
	PROCDESC_UNLOCK(pd);
	return (0);
}