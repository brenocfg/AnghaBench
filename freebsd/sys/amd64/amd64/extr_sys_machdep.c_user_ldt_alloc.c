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
typedef  int vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
struct user_segment_descriptor {int dummy; } ;
struct soft_segment_descriptor {int ssd_limit; int ssd_p; scalar_t__ ssd_gran; scalar_t__ ssd_def32; scalar_t__ ssd_long; int /*<<< orphan*/  ssd_dpl; int /*<<< orphan*/  ssd_type; scalar_t__ ssd_base; } ;
struct proc_ldt {int ldt_refcnt; scalar_t__ ldt_base; } ;
struct mdproc {struct proc_ldt* md_ldt; int /*<<< orphan*/  md_ldt_sd; } ;
struct proc {int /*<<< orphan*/  p_vmspace; struct mdproc p_md; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_SUBPROC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SDT_SYSLDT ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  atomic_thread_fence_rel () ; 
 int /*<<< orphan*/  bcopy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  dt_lock ; 
 int /*<<< orphan*/  free (struct proc_ldt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (scalar_t__,int) ; 
 scalar_t__ kmem_malloc (int,int) ; 
 struct proc_ldt* malloc (int,int /*<<< orphan*/ ,int) ; 
 int max_ldt_segment ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_pti_add_kva (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  pmap_pti_remove_kva (scalar_t__,scalar_t__) ; 
 scalar_t__ set_user_ldt_rv ; 
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ *,void (*) (void*),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssdtosyssd (struct soft_segment_descriptor*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_ldt_derefl (struct proc_ldt*) ; 

struct proc_ldt *
user_ldt_alloc(struct proc *p, int force)
{
	struct proc_ldt *pldt, *new_ldt;
	struct mdproc *mdp;
	struct soft_segment_descriptor sldt;
	vm_offset_t sva;
	vm_size_t sz;

	mtx_assert(&dt_lock, MA_OWNED);
	mdp = &p->p_md;
	if (!force && mdp->md_ldt != NULL)
		return (mdp->md_ldt);
	mtx_unlock(&dt_lock);
	new_ldt = malloc(sizeof(struct proc_ldt), M_SUBPROC, M_WAITOK);
	sz = max_ldt_segment * sizeof(struct user_segment_descriptor);
	sva = kmem_malloc(sz, M_WAITOK | M_ZERO);
	new_ldt->ldt_base = (caddr_t)sva;
	pmap_pti_add_kva(sva, sva + sz, false);
	new_ldt->ldt_refcnt = 1;
	sldt.ssd_base = sva;
	sldt.ssd_limit = sz - 1;
	sldt.ssd_type = SDT_SYSLDT;
	sldt.ssd_dpl = SEL_KPL;
	sldt.ssd_p = 1;
	sldt.ssd_long = 0;
	sldt.ssd_def32 = 0;
	sldt.ssd_gran = 0;
	mtx_lock(&dt_lock);
	pldt = mdp->md_ldt;
	if (pldt != NULL && !force) {
		pmap_pti_remove_kva(sva, sva + sz);
		kmem_free(sva, sz);
		free(new_ldt, M_SUBPROC);
		return (pldt);
	}

	if (pldt != NULL) {
		bcopy(pldt->ldt_base, new_ldt->ldt_base, max_ldt_segment *
		    sizeof(struct user_segment_descriptor));
		user_ldt_derefl(pldt);
	}
	critical_enter();
	ssdtosyssd(&sldt, &p->p_md.md_ldt_sd);
	atomic_thread_fence_rel();
	mdp->md_ldt = new_ldt;
	critical_exit();
	smp_rendezvous(NULL, (void (*)(void *))set_user_ldt_rv, NULL,
	    p->p_vmspace);

	return (mdp->md_ldt);
}