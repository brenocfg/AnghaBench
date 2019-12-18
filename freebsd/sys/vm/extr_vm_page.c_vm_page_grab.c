#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
struct TYPE_13__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int PG_ZERO ; 
 int VM_ALLOC_IGN_SBUSY ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_NOCREAT ; 
 int VM_ALLOC_NOWAIT ; 
 int VM_ALLOC_SBUSY ; 
 int VM_ALLOC_WAITFAIL ; 
 int VM_ALLOC_WAITOK ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_page_busy_sleep (TYPE_1__*,char*,int) ; 
 TYPE_1__* vm_page_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_sunbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_trysbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_tryxbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_wire (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 

vm_page_t
vm_page_grab(vm_object_t object, vm_pindex_t pindex, int allocflags)
{
	vm_page_t m;
	int sleep;
	int pflags;

	VM_OBJECT_ASSERT_WLOCKED(object);
	KASSERT((allocflags & VM_ALLOC_SBUSY) == 0 ||
	    (allocflags & VM_ALLOC_IGN_SBUSY) != 0,
	    ("vm_page_grab: VM_ALLOC_SBUSY/VM_ALLOC_IGN_SBUSY mismatch"));
	pflags = allocflags &
	    ~(VM_ALLOC_NOWAIT | VM_ALLOC_WAITOK | VM_ALLOC_WAITFAIL |
	    VM_ALLOC_NOBUSY);
	if ((allocflags & VM_ALLOC_NOWAIT) == 0)
		pflags |= VM_ALLOC_WAITFAIL;
	if ((allocflags & VM_ALLOC_IGN_SBUSY) != 0)
		pflags |= VM_ALLOC_SBUSY;
retrylookup:
	if ((m = vm_page_lookup(object, pindex)) != NULL) {
		if ((allocflags & (VM_ALLOC_IGN_SBUSY | VM_ALLOC_SBUSY)) != 0)
			sleep = !vm_page_trysbusy(m);
		else
			sleep = !vm_page_tryxbusy(m);
		if (sleep) {
			if ((allocflags & VM_ALLOC_NOWAIT) != 0)
				return (NULL);
			/*
			 * Reference the page before unlocking and
			 * sleeping so that the page daemon is less
			 * likely to reclaim it.
			 */
			if ((allocflags & VM_ALLOC_NOCREAT) == 0)
				vm_page_aflag_set(m, PGA_REFERENCED);
			vm_page_busy_sleep(m, "pgrbwt", (allocflags &
			    VM_ALLOC_IGN_SBUSY) != 0);
			VM_OBJECT_WLOCK(object);
			if ((allocflags & VM_ALLOC_WAITFAIL) != 0)
				return (NULL);
			goto retrylookup;
		} else {
			if ((allocflags & VM_ALLOC_WIRED) != 0)
				vm_page_wire(m);
			goto out;
		}
	}
	if ((allocflags & VM_ALLOC_NOCREAT) != 0)
		return (NULL);
	m = vm_page_alloc(object, pindex, pflags);
	if (m == NULL) {
		if ((allocflags & VM_ALLOC_NOWAIT) != 0)
			return (NULL);
		goto retrylookup;
	}
	if (allocflags & VM_ALLOC_ZERO && (m->flags & PG_ZERO) == 0)
		pmap_zero_page(m);

out:
	if ((allocflags & VM_ALLOC_NOBUSY) != 0) {
		if ((allocflags & VM_ALLOC_IGN_SBUSY) != 0)
			vm_page_sunbusy(m);
		else
			vm_page_xunbusy(m);
	}
	return (m);
}