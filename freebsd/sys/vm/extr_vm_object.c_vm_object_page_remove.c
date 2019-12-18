#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_23__ {int flags; scalar_t__ resident_page_count; scalar_t__ ref_count; } ;
struct TYPE_22__ {scalar_t__ pindex; int flags; scalar_t__ dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int OBJPR_CLEANONLY ; 
 int OBJPR_NOTMAPPED ; 
 int OBJ_UNMANAGED ; 
 int PG_FICTITIOUS ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  pmap_remove_all (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_pip_add (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_object_pip_wakeup (TYPE_2__*) ; 
 TYPE_1__* vm_page_find_least (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_invalid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_none_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_sleep_if_busy (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vm_page_try_remove_all (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_try_remove_write (TYPE_1__*) ; 
 scalar_t__ vm_page_tryxbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_undirty (TYPE_1__*) ; 
 scalar_t__ vm_page_wired (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 

void
vm_object_page_remove(vm_object_t object, vm_pindex_t start, vm_pindex_t end,
    int options)
{
	vm_page_t p, next;

	VM_OBJECT_ASSERT_WLOCKED(object);
	KASSERT((object->flags & OBJ_UNMANAGED) == 0 ||
	    (options & (OBJPR_CLEANONLY | OBJPR_NOTMAPPED)) == OBJPR_NOTMAPPED,
	    ("vm_object_page_remove: illegal options for object %p", object));
	if (object->resident_page_count == 0)
		return;
	vm_object_pip_add(object, 1);
again:
	p = vm_page_find_least(object, start);

	/*
	 * Here, the variable "p" is either (1) the page with the least pindex
	 * greater than or equal to the parameter "start" or (2) NULL. 
	 */
	for (; p != NULL && (p->pindex < end || end == 0); p = next) {
		next = TAILQ_NEXT(p, listq);

		/*
		 * If the page is wired for any reason besides the existence
		 * of managed, wired mappings, then it cannot be freed.  For
		 * example, fictitious pages, which represent device memory,
		 * are inherently wired and cannot be freed.  They can,
		 * however, be invalidated if the option OBJPR_CLEANONLY is
		 * not specified.
		 */
		if (vm_page_tryxbusy(p) == 0) {
			vm_page_sleep_if_busy(p, "vmopar");
			goto again;
		}
		if (vm_page_wired(p)) {
wired:
			if ((options & OBJPR_NOTMAPPED) == 0 &&
			    object->ref_count != 0)
				pmap_remove_all(p);
			if ((options & OBJPR_CLEANONLY) == 0) {
				vm_page_invalid(p);
				vm_page_undirty(p);
			}
			vm_page_xunbusy(p);
			continue;
		}
		KASSERT((p->flags & PG_FICTITIOUS) == 0,
		    ("vm_object_page_remove: page %p is fictitious", p));
		if ((options & OBJPR_CLEANONLY) != 0 &&
		    !vm_page_none_valid(p)) {
			if ((options & OBJPR_NOTMAPPED) == 0 &&
			    object->ref_count != 0 &&
			    !vm_page_try_remove_write(p))
				goto wired;
			if (p->dirty != 0) {
				vm_page_xunbusy(p);
				continue;
			}
		}
		if ((options & OBJPR_NOTMAPPED) == 0 &&
		    object->ref_count != 0 && !vm_page_try_remove_all(p))
			goto wired;
		vm_page_free(p);
	}
	vm_object_pip_wakeup(object);
}