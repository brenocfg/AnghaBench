#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct xen_memory_reservation {unsigned long nr_extents; int /*<<< orphan*/  extent_start; int /*<<< orphan*/  domid; int /*<<< orphan*/  extent_order; int /*<<< orphan*/  address_bits; } ;
struct TYPE_10__ {unsigned long current_pages; int /*<<< orphan*/  balloon_low; } ;
struct TYPE_9__ {int /*<<< orphan*/  q; } ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int HYPERVISOR_memory_op (int /*<<< orphan*/ ,struct xen_memory_reservation*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PAGE_SHIFT ; 
 int PG_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_ZERO ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int /*<<< orphan*/  XENMEM_decrease_reservation ; 
 int /*<<< orphan*/  balloon_mutex ; 
 int /*<<< orphan*/  ballooned_pages ; 
 TYPE_5__ bs ; 
 int* frame_list ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long nitems (int*) ; 
 TYPE_4__ plinks ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
decrease_reservation(unsigned long nr_pages)
{
	unsigned long  i;
	vm_page_t      page;
	int            need_sleep = 0;
	int ret;
	struct xen_memory_reservation reservation = {
		.address_bits = 0,
		.extent_order = 0,
		.domid        = DOMID_SELF
	};

	mtx_assert(&balloon_mutex, MA_OWNED);

	if (nr_pages > nitems(frame_list))
		nr_pages = nitems(frame_list);

	for (i = 0; i < nr_pages; i++) {
		if ((page = vm_page_alloc(NULL, 0, 
			    VM_ALLOC_NORMAL | VM_ALLOC_NOOBJ | 
			    VM_ALLOC_ZERO)) == NULL) {
			nr_pages = i;
			need_sleep = 1;
			break;
		}

		if ((page->flags & PG_ZERO) == 0) {
			/*
			 * Zero the page, or else we might be leaking
			 * important data to other domains on the same
			 * host. Xen doesn't scrub ballooned out memory
			 * pages, the guest is in charge of making
			 * sure that no information is leaked.
			 */
			pmap_zero_page(page);
		}

		frame_list[i] = (VM_PAGE_TO_PHYS(page) >> PAGE_SHIFT);

		TAILQ_INSERT_HEAD(&ballooned_pages, page, plinks.q);
		bs.balloon_low++;
	}

	set_xen_guest_handle(reservation.extent_start, frame_list);
	reservation.nr_extents   = nr_pages;
	ret = HYPERVISOR_memory_op(XENMEM_decrease_reservation, &reservation);
	KASSERT(ret == nr_pages, ("HYPERVISOR_memory_op failed"));

	bs.current_pages -= nr_pages;

	return (need_sleep);
}