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
struct procdesc {int /*<<< orphan*/ * pd_proc; } ;
struct proc {struct procdesc* p_procdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  procdesc_free (struct procdesc*) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
procdesc_reap(struct proc *p)
{
	struct procdesc *pd;

	sx_assert(&proctree_lock, SA_XLOCKED);
	KASSERT(p->p_procdesc != NULL, ("procdesc_reap: p_procdesc == NULL"));

	pd = p->p_procdesc;
	pd->pd_proc = NULL;
	p->p_procdesc = NULL;
	procdesc_free(pd);
}