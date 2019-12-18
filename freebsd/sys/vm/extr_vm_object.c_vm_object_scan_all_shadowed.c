#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_15__ {scalar_t__ type; scalar_t__ size; int /*<<< orphan*/  backing_object_offset; struct TYPE_15__* backing_object; } ;
struct TYPE_14__ {scalar_t__ pindex; } ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ OBJT_DEFAULT ; 
 scalar_t__ OBJT_SWAP ; 
 scalar_t__ OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  listq ; 
 scalar_t__ swap_pager_find_least (TYPE_2__*,scalar_t__) ; 
 TYPE_1__* vm_page_find_least (TYPE_2__*,scalar_t__) ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,scalar_t__) ; 
 scalar_t__ vm_page_none_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pager_has_page (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
vm_object_scan_all_shadowed(vm_object_t object)
{
	vm_object_t backing_object;
	vm_page_t p, pp;
	vm_pindex_t backing_offset_index, new_pindex, pi, ps;

	VM_OBJECT_ASSERT_WLOCKED(object);
	VM_OBJECT_ASSERT_WLOCKED(object->backing_object);

	backing_object = object->backing_object;

	if (backing_object->type != OBJT_DEFAULT &&
	    backing_object->type != OBJT_SWAP)
		return (false);

	pi = backing_offset_index = OFF_TO_IDX(object->backing_object_offset);
	p = vm_page_find_least(backing_object, pi);
	ps = swap_pager_find_least(backing_object, pi);

	/*
	 * Only check pages inside the parent object's range and
	 * inside the parent object's mapping of the backing object.
	 */
	for (;; pi++) {
		if (p != NULL && p->pindex < pi)
			p = TAILQ_NEXT(p, listq);
		if (ps < pi)
			ps = swap_pager_find_least(backing_object, pi);
		if (p == NULL && ps >= backing_object->size)
			break;
		else if (p == NULL)
			pi = ps;
		else
			pi = MIN(p->pindex, ps);

		new_pindex = pi - backing_offset_index;
		if (new_pindex >= object->size)
			break;

		/*
		 * See if the parent has the page or if the parent's object
		 * pager has the page.  If the parent has the page but the page
		 * is not valid, the parent's object pager must have the page.
		 *
		 * If this fails, the parent does not completely shadow the
		 * object and we might as well give up now.
		 */
		pp = vm_page_lookup(object, new_pindex);
		/*
		 * The valid check here is stable due to object lock being
		 * required to clear valid and initiate paging.
		 */
		if ((pp == NULL || vm_page_none_valid(pp)) &&
		    !vm_pager_has_page(object, new_pindex, NULL, NULL))
			return (false);
	}
	return (true);
}