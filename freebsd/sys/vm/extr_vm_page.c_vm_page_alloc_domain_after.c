#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  TYPE_3__* vm_object_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct vm_domain {TYPE_1__* vmd_pgcache; } ;
struct TYPE_27__ {int flags; int /*<<< orphan*/  memattr; } ;
struct TYPE_26__ {int flags; int ref_count; scalar_t__ pindex; void* busy_lock; void* oflags; int /*<<< orphan*/ * object; scalar_t__ act_count; scalar_t__ aflags; } ;
struct TYPE_25__ {int /*<<< orphan*/ * zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int OBJ_FICTITIOUS ; 
 int OBJ_UNMANAGED ; 
 int PG_NODUMP ; 
 int PG_PCPU_CACHE ; 
 int PG_ZERO ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_NODUMP ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_SBUSY ; 
 int VM_ALLOC_WAITFAIL ; 
 int VM_ALLOC_WAITOK ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 struct vm_domain* VM_DOMAIN (int) ; 
 int VM_FREEPOOL_DEFAULT ; 
 int VM_FREEPOOL_DIRECT ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_3__*) ; 
 void* VPB_SHARERS_WORD (int) ; 
 void* VPB_SINGLE_EXCLUSIVER ; 
 void* VPB_UNBUSIED ; 
 void* VPO_UNMANAGED ; 
 int /*<<< orphan*/  pmap_page_set_memattr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* uma_zalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_domain_alloc_fail (struct vm_domain*,TYPE_3__*,int) ; 
 scalar_t__ vm_domain_allocate (struct vm_domain*,int,int) ; 
 int /*<<< orphan*/  vm_domain_free_lock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_free_unlock (struct vm_domain*) ; 
 int /*<<< orphan*/  vm_domain_freecnt_inc (struct vm_domain*,int) ; 
 scalar_t__ vm_object_reserv (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_page_alloc_check (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_dequeue (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_free_toq (TYPE_2__*) ; 
 scalar_t__ vm_page_insert_after (TYPE_2__*,TYPE_3__*,scalar_t__,TYPE_2__*) ; 
 TYPE_2__* vm_phys_alloc_pages (int,int,int /*<<< orphan*/ ) ; 
 int vm_phys_domain (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_radix_wait () ; 
 TYPE_2__* vm_reserv_alloc_page (TYPE_3__*,scalar_t__,int,int,TYPE_2__*) ; 
 scalar_t__ vm_reserv_reclaim_inactive (int) ; 
 int /*<<< orphan*/  vm_wire_add (int) ; 
 int /*<<< orphan*/  vm_wire_sub (int) ; 

vm_page_t
vm_page_alloc_domain_after(vm_object_t object, vm_pindex_t pindex, int domain,
    int req, vm_page_t mpred)
{
	struct vm_domain *vmd;
	vm_page_t m;
	int flags, pool;

	KASSERT((object != NULL) == ((req & VM_ALLOC_NOOBJ) == 0) &&
	    (object != NULL || (req & VM_ALLOC_SBUSY) == 0) &&
	    ((req & (VM_ALLOC_NOBUSY | VM_ALLOC_SBUSY)) !=
	    (VM_ALLOC_NOBUSY | VM_ALLOC_SBUSY)),
	    ("inconsistent object(%p)/req(%x)", object, req));
	KASSERT(object == NULL || (req & VM_ALLOC_WAITOK) == 0,
	    ("Can't sleep and retry object insertion."));
	KASSERT(mpred == NULL || mpred->pindex < pindex,
	    ("mpred %p doesn't precede pindex 0x%jx", mpred,
	    (uintmax_t)pindex));
	if (object != NULL)
		VM_OBJECT_ASSERT_WLOCKED(object);

	flags = 0;
	m = NULL;
	pool = object != NULL ? VM_FREEPOOL_DEFAULT : VM_FREEPOOL_DIRECT;
again:
#if VM_NRESERVLEVEL > 0
	/*
	 * Can we allocate the page from a reservation?
	 */
	if (vm_object_reserv(object) &&
	    (m = vm_reserv_alloc_page(object, pindex, domain, req, mpred)) !=
	    NULL) {
		domain = vm_phys_domain(m);
		vmd = VM_DOMAIN(domain);
		goto found;
	}
#endif
	vmd = VM_DOMAIN(domain);
	if (vmd->vmd_pgcache[pool].zone != NULL) {
		m = uma_zalloc(vmd->vmd_pgcache[pool].zone, M_NOWAIT);
		if (m != NULL) {
			flags |= PG_PCPU_CACHE;
			goto found;
		}
	}
	if (vm_domain_allocate(vmd, req, 1)) {
		/*
		 * If not, allocate it from the free page queues.
		 */
		vm_domain_free_lock(vmd);
		m = vm_phys_alloc_pages(domain, pool, 0);
		vm_domain_free_unlock(vmd);
		if (m == NULL) {
			vm_domain_freecnt_inc(vmd, 1);
#if VM_NRESERVLEVEL > 0
			if (vm_reserv_reclaim_inactive(domain))
				goto again;
#endif
		}
	}
	if (m == NULL) {
		/*
		 * Not allocatable, give up.
		 */
		if (vm_domain_alloc_fail(vmd, object, req))
			goto again;
		return (NULL);
	}

	/*
	 * At this point we had better have found a good page.
	 */
found:
	vm_page_dequeue(m);
	vm_page_alloc_check(m);

	/*
	 * Initialize the page.  Only the PG_ZERO flag is inherited.
	 */
	if ((req & VM_ALLOC_ZERO) != 0)
		flags |= (m->flags & PG_ZERO);
	if ((req & VM_ALLOC_NODUMP) != 0)
		flags |= PG_NODUMP;
	m->flags = flags;
	m->aflags = 0;
	m->oflags = object == NULL || (object->flags & OBJ_UNMANAGED) != 0 ?
	    VPO_UNMANAGED : 0;
	m->busy_lock = VPB_UNBUSIED;
	if ((req & (VM_ALLOC_NOBUSY | VM_ALLOC_NOOBJ | VM_ALLOC_SBUSY)) == 0)
		m->busy_lock = VPB_SINGLE_EXCLUSIVER;
	if ((req & VM_ALLOC_SBUSY) != 0)
		m->busy_lock = VPB_SHARERS_WORD(1);
	if (req & VM_ALLOC_WIRED) {
		/*
		 * The page lock is not required for wiring a page until that
		 * page is inserted into the object.
		 */
		vm_wire_add(1);
		m->ref_count = 1;
	}
	m->act_count = 0;

	if (object != NULL) {
		if (vm_page_insert_after(m, object, pindex, mpred)) {
			if (req & VM_ALLOC_WIRED) {
				vm_wire_sub(1);
				m->ref_count = 0;
			}
			KASSERT(m->object == NULL, ("page %p has object", m));
			m->oflags = VPO_UNMANAGED;
			m->busy_lock = VPB_UNBUSIED;
			/* Don't change PG_ZERO. */
			vm_page_free_toq(m);
			if (req & VM_ALLOC_WAITFAIL) {
				VM_OBJECT_WUNLOCK(object);
				vm_radix_wait();
				VM_OBJECT_WLOCK(object);
			}
			return (NULL);
		}

		/* Ignore device objects; the pager sets "memattr" for them. */
		if (object->memattr != VM_MEMATTR_DEFAULT &&
		    (object->flags & OBJ_FICTITIOUS) == 0)
			pmap_page_set_memattr(m, object->memattr);
	} else
		m->pindex = pindex;

	return (m);
}