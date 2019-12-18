#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_page_t ;
struct xen_memory_reservation {unsigned long nr_extents; int /*<<< orphan*/  extent_start; int /*<<< orphan*/  domid; int /*<<< orphan*/  extent_order; int /*<<< orphan*/  address_bits; } ;
struct TYPE_4__ {scalar_t__ current_pages; int /*<<< orphan*/  balloon_low; scalar_t__ driver_pages; scalar_t__ hard_limit; } ;
struct TYPE_3__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 void* HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_memory_reservation*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TAILQ_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XENFEAT_auto_translated_physmap ; 
 int /*<<< orphan*/  XENMEM_decrease_reservation ; 
 int /*<<< orphan*/  XENMEM_populate_physmap ; 
 int /*<<< orphan*/  balloon_mutex ; 
 int /*<<< orphan*/  ballooned_pages ; 
 TYPE_2__ bs ; 
 int* frame_list ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long nitems (int*) ; 
 TYPE_1__ plinks ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ *) ; 
 int xen_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
increase_reservation(unsigned long nr_pages)
{
	unsigned long  i;
	vm_page_t      page;
	long           rc;
	struct xen_memory_reservation reservation = {
		.address_bits = 0,
		.extent_order = 0,
		.domid        = DOMID_SELF
	};

	mtx_assert(&balloon_mutex, MA_OWNED);

	if (nr_pages > nitems(frame_list))
		nr_pages = nitems(frame_list);

	for (page = TAILQ_FIRST(&ballooned_pages), i = 0;
	    i < nr_pages; i++, page = TAILQ_NEXT(page, plinks.q)) {
		KASSERT(page != NULL, ("ballooned_pages list corrupt"));
		frame_list[i] = (VM_PAGE_TO_PHYS(page) >> PAGE_SHIFT);
	}

	set_xen_guest_handle(reservation.extent_start, frame_list);
	reservation.nr_extents   = nr_pages;
	rc = HYPERVISOR_memory_op(
		XENMEM_populate_physmap, &reservation);
	if (rc < nr_pages) {
		if (rc > 0) {
			int ret;

			/* We hit the Xen hard limit: reprobe. */
			reservation.nr_extents = rc;
			ret = HYPERVISOR_memory_op(XENMEM_decrease_reservation,
					&reservation);
			KASSERT(ret == rc, ("HYPERVISOR_memory_op failed"));
		}
		if (rc >= 0)
			bs.hard_limit = (bs.current_pages + rc -
					 bs.driver_pages);
		goto out;
	}

	for (i = 0; i < nr_pages; i++) {
		page = TAILQ_FIRST(&ballooned_pages);
		KASSERT(page != NULL, ("Unable to get ballooned page"));
		TAILQ_REMOVE(&ballooned_pages, page, plinks.q);
		bs.balloon_low--;

		KASSERT(xen_feature(XENFEAT_auto_translated_physmap),
		    ("auto translated physmap but mapping is valid"));

		vm_page_free(page);
	}

	bs.current_pages += nr_pages;

 out:
	return (0);
}