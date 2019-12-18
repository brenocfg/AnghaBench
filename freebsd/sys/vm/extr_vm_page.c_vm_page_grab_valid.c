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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  TRUE ; 
 int VM_ALLOC_IGN_SBUSY ; 
 int VM_ALLOC_NOBUSY ; 
 int VM_ALLOC_NOCREAT ; 
 int VM_ALLOC_NOWAIT ; 
 int VM_ALLOC_SBUSY ; 
 int VM_ALLOC_WAITFAIL ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int VM_PAGER_FAIL ; 
 int VM_PAGER_OK ; 
 int /*<<< orphan*/  vm_page_aflag_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vm_page_all_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_page_assert_xbusied (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_busy_downgrade (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_busy_sleep (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_sunbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_trysbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_tryxbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_wire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_xunbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_zero_invalid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vm_pager_get_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vm_pager_has_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
vm_page_grab_valid(vm_page_t *mp, vm_object_t object, vm_pindex_t pindex, int allocflags)
{
	vm_page_t m;
	bool sleep, xbusy;
	int pflags;
	int rv;

	KASSERT((allocflags & VM_ALLOC_SBUSY) == 0 ||
	    (allocflags & VM_ALLOC_IGN_SBUSY) != 0,
	    ("vm_page_grab_valid: VM_ALLOC_SBUSY/VM_ALLOC_IGN_SBUSY mismatch"));
	KASSERT((allocflags &
	    (VM_ALLOC_NOWAIT | VM_ALLOC_WAITFAIL | VM_ALLOC_ZERO)) == 0,
	    ("vm_page_grab_valid: Invalid flags 0x%X", allocflags));
	VM_OBJECT_ASSERT_WLOCKED(object);
	pflags = allocflags & ~(VM_ALLOC_NOBUSY | VM_ALLOC_SBUSY);
	pflags |= VM_ALLOC_WAITFAIL;

retrylookup:
	xbusy = false;
	if ((m = vm_page_lookup(object, pindex)) != NULL) {
		/*
		 * If the page is fully valid it can only become invalid
		 * with the object lock held.  If it is not valid it can
		 * become valid with the busy lock held.  Therefore, we
		 * may unnecessarily lock the exclusive busy here if we
		 * race with I/O completion not using the object lock.
		 * However, we will not end up with an invalid page and a
		 * shared lock.
		 */
		if (!vm_page_all_valid(m) ||
		    (allocflags & (VM_ALLOC_IGN_SBUSY | VM_ALLOC_SBUSY)) == 0) {
			sleep = !vm_page_tryxbusy(m);
			xbusy = true;
		} else
			sleep = !vm_page_trysbusy(m);
		if (sleep) {
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
			goto retrylookup;
		}
		if ((allocflags & VM_ALLOC_NOCREAT) != 0 &&
		   !vm_page_all_valid(m)) {
			if (xbusy)
				vm_page_xunbusy(m);
			else
				vm_page_sunbusy(m);
			*mp = NULL;
			return (VM_PAGER_FAIL);
		}
		if ((allocflags & VM_ALLOC_WIRED) != 0)
			vm_page_wire(m);
		if (vm_page_all_valid(m))
			goto out;
	} else if ((allocflags & VM_ALLOC_NOCREAT) != 0) {
		*mp = NULL;
		return (VM_PAGER_FAIL);
	} else if ((m = vm_page_alloc(object, pindex, pflags)) != NULL) {
		xbusy = true;
	} else {
		goto retrylookup;
	}

	vm_page_assert_xbusied(m);
	MPASS(xbusy);
	if (vm_pager_has_page(object, pindex, NULL, NULL)) {
		rv = vm_pager_get_pages(object, &m, 1, NULL, NULL);
		if (rv != VM_PAGER_OK) {
			if (allocflags & VM_ALLOC_WIRED)
				vm_page_unwire_noq(m);
			vm_page_free(m);
			*mp = NULL;
			return (rv);
		}
		MPASS(vm_page_all_valid(m));
	} else {
		vm_page_zero_invalid(m, TRUE);
	}
out:
	if ((allocflags & VM_ALLOC_NOBUSY) != 0) {
		if (xbusy)
			vm_page_xunbusy(m);
		else
			vm_page_sunbusy(m);
	}
	if ((allocflags & VM_ALLOC_SBUSY) != 0 && xbusy)
		vm_page_busy_downgrade(m);
	*mp = m;
	return (VM_PAGER_OK);
}