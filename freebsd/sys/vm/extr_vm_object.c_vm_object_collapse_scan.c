#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_29__ {scalar_t__ size; scalar_t__ type; int /*<<< orphan*/  memq; int /*<<< orphan*/  backing_object_offset; struct TYPE_29__* backing_object; } ;
struct TYPE_28__ {scalar_t__ pindex; TYPE_2__* object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ OBJT_SWAP ; 
 int /*<<< orphan*/  OBJ_DEAD ; 
 int OBSC_COLLAPSE_WAIT ; 
 scalar_t__ OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  pmap_page_is_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  swap_pager_freespace (TYPE_2__*,scalar_t__,int) ; 
 TYPE_1__* vm_object_collapse_scan_wait (TYPE_2__*,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_object_set_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_none_valid (TYPE_1__*) ; 
 scalar_t__ vm_page_remove (TYPE_1__*) ; 
 scalar_t__ vm_page_rename (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 scalar_t__ vm_page_tryxbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 
 scalar_t__ vm_pager_has_page (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_reserv_rename (TYPE_1__*,TYPE_2__*,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static bool
vm_object_collapse_scan(vm_object_t object, int op)
{
	vm_object_t backing_object;
	vm_page_t next, p, pp;
	vm_pindex_t backing_offset_index, new_pindex;

	VM_OBJECT_ASSERT_WLOCKED(object);
	VM_OBJECT_ASSERT_WLOCKED(object->backing_object);

	backing_object = object->backing_object;
	backing_offset_index = OFF_TO_IDX(object->backing_object_offset);

	/*
	 * Initial conditions
	 */
	if ((op & OBSC_COLLAPSE_WAIT) != 0)
		vm_object_set_flag(backing_object, OBJ_DEAD);

	/*
	 * Our scan
	 */
	for (p = TAILQ_FIRST(&backing_object->memq); p != NULL; p = next) {
		next = TAILQ_NEXT(p, listq);
		new_pindex = p->pindex - backing_offset_index;

		/*
		 * Check for busy page
		 */
		if (vm_page_tryxbusy(p) == 0) {
			next = vm_object_collapse_scan_wait(object, p, next, op);
			continue;
		}

		KASSERT(p->object == backing_object,
		    ("vm_object_collapse_scan: object mismatch"));

		if (p->pindex < backing_offset_index ||
		    new_pindex >= object->size) {
			if (backing_object->type == OBJT_SWAP)
				swap_pager_freespace(backing_object, p->pindex,
				    1);

			KASSERT(!pmap_page_is_mapped(p),
			    ("freeing mapped page %p", p));
			if (vm_page_remove(p))
				vm_page_free(p);
			else
				vm_page_xunbusy(p);
			continue;
		}

		pp = vm_page_lookup(object, new_pindex);
		if (pp != NULL && vm_page_tryxbusy(pp) == 0) {
			vm_page_xunbusy(p);
			/*
			 * The page in the parent is busy and possibly not
			 * (yet) valid.  Until its state is finalized by the
			 * busy bit owner, we can't tell whether it shadows the
			 * original page.  Therefore, we must either skip it
			 * and the original (backing_object) page or wait for
			 * its state to be finalized.
			 *
			 * This is due to a race with vm_fault() where we must
			 * unbusy the original (backing_obj) page before we can
			 * (re)lock the parent.  Hence we can get here.
			 */
			next = vm_object_collapse_scan_wait(object, pp, next,
			    op);
			continue;
		}

		KASSERT(pp == NULL || !vm_page_none_valid(pp),
		    ("unbusy invalid page %p", pp));

		if (pp != NULL || vm_pager_has_page(object, new_pindex, NULL,
			NULL)) {
			/*
			 * The page already exists in the parent OR swap exists
			 * for this location in the parent.  Leave the parent's
			 * page alone.  Destroy the original page from the
			 * backing object.
			 */
			if (backing_object->type == OBJT_SWAP)
				swap_pager_freespace(backing_object, p->pindex,
				    1);
			KASSERT(!pmap_page_is_mapped(p),
			    ("freeing mapped page %p", p));
			if (vm_page_remove(p))
				vm_page_free(p);
			else
				vm_page_xunbusy(p);
			if (pp != NULL)
				vm_page_xunbusy(pp);
			continue;
		}

		/*
		 * Page does not exist in parent, rename the page from the
		 * backing object to the main object.
		 *
		 * If the page was mapped to a process, it can remain mapped
		 * through the rename.  vm_page_rename() will dirty the page.
		 */
		if (vm_page_rename(p, object, new_pindex)) {
			vm_page_xunbusy(p);
			if (pp != NULL)
				vm_page_xunbusy(pp);
			next = vm_object_collapse_scan_wait(object, NULL, next,
			    op);
			continue;
		}

		/* Use the old pindex to free the right page. */
		if (backing_object->type == OBJT_SWAP)
			swap_pager_freespace(backing_object,
			    new_pindex + backing_offset_index, 1);

#if VM_NRESERVLEVEL > 0
		/*
		 * Rename the reservation.
		 */
		vm_reserv_rename(p, object, backing_object,
		    backing_offset_index);
#endif
		vm_page_xunbusy(p);
	}
	return (true);
}