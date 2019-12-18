#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int u_int ;
struct TYPE_26__ {int /*<<< orphan*/  rtree; } ;
struct TYPE_25__ {scalar_t__ pindex; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int PG_ZERO ; 
 TYPE_1__* TAILQ_PREV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VM_ALLOC_COUNT (int) ; 
 int VM_ALLOC_COUNT_SHIFT ; 
 int VM_ALLOC_IGN_SBUSY ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_NOCREAT ; 
 int VM_ALLOC_NOWAIT ; 
 int VM_ALLOC_SBUSY ; 
 int VM_ALLOC_WAITFAIL ; 
 int VM_ALLOC_WAITOK ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  pglist ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_page_alloc_after (TYPE_2__*,scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_busy_sleep (TYPE_1__*,char*,int) ; 
 TYPE_1__* vm_page_next (TYPE_1__*) ; 
 scalar_t__ vm_page_none_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_sunbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_trysbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_tryxbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_wire (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 
 TYPE_1__* vm_radix_lookup_le (int /*<<< orphan*/ *,scalar_t__) ; 

int
vm_page_grab_pages(vm_object_t object, vm_pindex_t pindex, int allocflags,
    vm_page_t *ma, int count)
{
	vm_page_t m, mpred;
	int pflags;
	int i;
	bool sleep;

	VM_OBJECT_ASSERT_WLOCKED(object);
	KASSERT(((u_int)allocflags >> VM_ALLOC_COUNT_SHIFT) == 0,
	    ("vm_page_grap_pages: VM_ALLOC_COUNT() is not allowed"));
	KASSERT((allocflags & VM_ALLOC_NOBUSY) == 0 ||
	    (allocflags & VM_ALLOC_WIRED) != 0,
	    ("vm_page_grab_pages: the pages must be busied or wired"));
	KASSERT((allocflags & VM_ALLOC_SBUSY) == 0 ||
	    (allocflags & VM_ALLOC_IGN_SBUSY) != 0,
	    ("vm_page_grab_pages: VM_ALLOC_SBUSY/IGN_SBUSY mismatch"));
	if (count == 0)
		return (0);
	pflags = allocflags &
	    ~(VM_ALLOC_NOWAIT | VM_ALLOC_WAITOK | VM_ALLOC_WAITFAIL |
	    VM_ALLOC_NOBUSY);
	if ((allocflags & VM_ALLOC_NOWAIT) == 0)
		pflags |= VM_ALLOC_WAITFAIL;
	if ((allocflags & VM_ALLOC_IGN_SBUSY) != 0)
		pflags |= VM_ALLOC_SBUSY;
	i = 0;
retrylookup:
	m = vm_radix_lookup_le(&object->rtree, pindex + i);
	if (m == NULL || m->pindex != pindex + i) {
		mpred = m;
		m = NULL;
	} else
		mpred = TAILQ_PREV(m, pglist, listq);
	for (; i < count; i++) {
		if (m != NULL) {
			if ((allocflags &
			    (VM_ALLOC_SBUSY | VM_ALLOC_IGN_SBUSY)) != 0)
				sleep = !vm_page_trysbusy(m);
			else
				sleep = !vm_page_tryxbusy(m);
			if (sleep) {
				if ((allocflags & VM_ALLOC_NOWAIT) != 0)
					break;
				/*
				 * Reference the page before unlocking and
				 * sleeping so that the page daemon is less
				 * likely to reclaim it.
				 */
				if ((allocflags & VM_ALLOC_NOCREAT) == 0)
					vm_page_aflag_set(m, PGA_REFERENCED);
				vm_page_busy_sleep(m, "grbmaw", (allocflags &
				    VM_ALLOC_IGN_SBUSY) != 0);
				VM_OBJECT_WLOCK(object);
				goto retrylookup;
			}
			if ((allocflags & VM_ALLOC_WIRED) != 0)
				vm_page_wire(m);
		} else {
			if ((allocflags & VM_ALLOC_NOCREAT) != 0)
				break;
			m = vm_page_alloc_after(object, pindex + i,
			    pflags | VM_ALLOC_COUNT(count - i), mpred);
			if (m == NULL) {
				if ((allocflags & VM_ALLOC_NOWAIT) != 0)
					break;
				goto retrylookup;
			}
		}
		if (vm_page_none_valid(m) &&
		    (allocflags & VM_ALLOC_ZERO) != 0) {
			if ((m->flags & PG_ZERO) == 0)
				pmap_zero_page(m);
			vm_page_valid(m);
		}
		if ((allocflags & VM_ALLOC_NOBUSY) != 0) {
			if ((allocflags & VM_ALLOC_IGN_SBUSY) != 0)
				vm_page_sunbusy(m);
			else
				vm_page_xunbusy(m);
		}
		ma[i] = mpred = m;
		m = vm_page_next(m);
	}
	return (i);
}