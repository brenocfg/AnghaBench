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
struct procdesc {int /*<<< orphan*/  pd_refcount; int /*<<< orphan*/  pd_lock; TYPE_1__ pd_selinfo; int /*<<< orphan*/  pd_flags; int /*<<< orphan*/  pd_pid; struct proc* pd_proc; } ;
struct proc {struct procdesc* p_procdesc; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PDF_DAEMON ; 
 int PD_DAEMON ; 
 int /*<<< orphan*/  PROCDESC_LOCK_INIT (struct procdesc*) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procdesc_zone ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 struct procdesc* uma_zalloc (int /*<<< orphan*/ ,int) ; 

void
procdesc_new(struct proc *p, int flags)
{
	struct procdesc *pd;

	pd = uma_zalloc(procdesc_zone, M_WAITOK | M_ZERO);
	pd->pd_proc = p;
	pd->pd_pid = p->p_pid;
	p->p_procdesc = pd;
	pd->pd_flags = 0;
	if (flags & PD_DAEMON)
		pd->pd_flags |= PDF_DAEMON;
	PROCDESC_LOCK_INIT(pd);
	knlist_init_mtx(&pd->pd_selinfo.si_note, &pd->pd_lock);

	/*
	 * Process descriptors start out with two references: one from their
	 * struct file, and the other from their struct proc.
	 */
	refcount_init(&pd->pd_refcount, 2);
}