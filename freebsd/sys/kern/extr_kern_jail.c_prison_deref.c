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
struct prison {scalar_t__ pr_uref; int pr_ref; scalar_t__ pr_vnet; int /*<<< orphan*/  pr_mtx; int /*<<< orphan*/ * pr_cpuset; struct prison* pr_ip6; struct prison* pr_ip4; int /*<<< orphan*/ * pr_root; int /*<<< orphan*/  pr_childcount; struct prison* pr_parent; int /*<<< orphan*/  pr_id; } ;
struct TYPE_2__ {scalar_t__ pr_uref; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct prison*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PRISON ; 
 int PD_DEREF ; 
 int PD_DEUREF ; 
 int PD_LIST_SLOCKED ; 
 int PD_LIST_XLOCKED ; 
 int PD_LOCKED ; 
 int /*<<< orphan*/  PR_METHOD_REMOVE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct prison*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allprison ; 
 int /*<<< orphan*/  allprison_lock ; 
 int /*<<< orphan*/  cpuset_rel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct prison*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd_jail_call (struct prison*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd_jail_exit (struct prison*) ; 
 int /*<<< orphan*/  pr_list ; 
 int /*<<< orphan*/  pr_sibling ; 
 TYPE_1__ prison0 ; 
 int /*<<< orphan*/  prison_racct_detach (struct prison*) ; 
 scalar_t__ racct_enable ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_try_upgrade (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnet_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
prison_deref(struct prison *pr, int flags)
{
	struct prison *ppr, *tpr;
	int ref, lasturef;

	if (!(flags & PD_LOCKED))
		mtx_lock(&pr->pr_mtx);
	for (;;) {
		if (flags & PD_DEUREF) {
			KASSERT(pr->pr_uref > 0,
			    ("prison_deref PD_DEUREF on a dead prison (jid=%d)",
			     pr->pr_id));
			pr->pr_uref--;
			lasturef = pr->pr_uref == 0;
			if (lasturef)
				pr->pr_ref++;
			KASSERT(prison0.pr_uref != 0, ("prison0 pr_uref=0"));
		} else
			lasturef = 0;
		if (flags & PD_DEREF) {
			KASSERT(pr->pr_ref > 0,
			    ("prison_deref PD_DEREF on a dead prison (jid=%d)",
			     pr->pr_id));
			pr->pr_ref--;
		}
		ref = pr->pr_ref;
		mtx_unlock(&pr->pr_mtx);

		/*
		 * Tell the modules if the last user reference was removed
		 * (even it sticks around in dying state).
		 */
		if (lasturef) {
			if (!(flags & (PD_LIST_SLOCKED | PD_LIST_XLOCKED))) {
				sx_xlock(&allprison_lock);
				flags |= PD_LIST_XLOCKED;
			}
			(void)osd_jail_call(pr, PR_METHOD_REMOVE, NULL);
			mtx_lock(&pr->pr_mtx);
			ref = --pr->pr_ref;
			mtx_unlock(&pr->pr_mtx);
		}

		/* If the prison still has references, nothing else to do. */
		if (ref > 0) {
			if (flags & PD_LIST_SLOCKED)
				sx_sunlock(&allprison_lock);
			else if (flags & PD_LIST_XLOCKED)
				sx_xunlock(&allprison_lock);
			return;
		}

		if (flags & PD_LIST_SLOCKED) {
			if (!sx_try_upgrade(&allprison_lock)) {
				sx_sunlock(&allprison_lock);
				sx_xlock(&allprison_lock);
			}
		} else if (!(flags & PD_LIST_XLOCKED))
			sx_xlock(&allprison_lock);

		TAILQ_REMOVE(&allprison, pr, pr_list);
		LIST_REMOVE(pr, pr_sibling);
		ppr = pr->pr_parent;
		for (tpr = ppr; tpr != NULL; tpr = tpr->pr_parent)
			tpr->pr_childcount--;
		sx_xunlock(&allprison_lock);

#ifdef VIMAGE
		if (pr->pr_vnet != ppr->pr_vnet)
			vnet_destroy(pr->pr_vnet);
#endif
		if (pr->pr_root != NULL)
			vrele(pr->pr_root);
		mtx_destroy(&pr->pr_mtx);
#ifdef INET
		free(pr->pr_ip4, M_PRISON);
#endif
#ifdef INET6
		free(pr->pr_ip6, M_PRISON);
#endif
		if (pr->pr_cpuset != NULL)
			cpuset_rel(pr->pr_cpuset);
		osd_jail_exit(pr);
#ifdef RACCT
		if (racct_enable)
			prison_racct_detach(pr);
#endif
		free(pr, M_PRISON);

		/* Removing a prison frees a reference on its parent. */
		pr = ppr;
		mtx_lock(&pr->pr_mtx);
		flags = PD_DEREF | PD_DEUREF;
	}
}