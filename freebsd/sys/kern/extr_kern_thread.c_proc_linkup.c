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
struct thread {int dummy; } ;
struct proc {scalar_t__ p_numthreads; int /*<<< orphan*/  p_mqnotifier; TYPE_1__* p_ksi; int /*<<< orphan*/  p_sigqueue; } ;
struct TYPE_2__ {int ksi_flags; } ;

/* Variables and functions */
 int KSI_EXT ; 
 int KSI_INS ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* ksiginfo_alloc (int) ; 
 int /*<<< orphan*/  sigqueue_init (int /*<<< orphan*/ *,struct proc*) ; 
 int /*<<< orphan*/  thread_link (struct thread*,struct proc*) ; 

void
proc_linkup(struct proc *p, struct thread *td)
{

	sigqueue_init(&p->p_sigqueue, p);
	p->p_ksi = ksiginfo_alloc(1);
	if (p->p_ksi != NULL) {
		/* XXX p_ksi may be null if ksiginfo zone is not ready */
		p->p_ksi->ksi_flags = KSI_EXT | KSI_INS;
	}
	LIST_INIT(&p->p_mqnotifier);
	p->p_numthreads = 0;
	thread_link(td, p);
}