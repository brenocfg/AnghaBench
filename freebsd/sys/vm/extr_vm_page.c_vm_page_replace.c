#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_16__ {int /*<<< orphan*/  memq; int /*<<< orphan*/  rtree; } ;
struct TYPE_15__ {int ref_count; scalar_t__ queue; TYPE_2__* object; int /*<<< orphan*/  pindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PQ_NONE ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int VPRC_OBJREF ; 
 int /*<<< orphan*/  atomic_clear_int (int*,int) ; 
 int /*<<< orphan*/  atomic_set_int (int*,int) ; 
 int /*<<< orphan*/  listq ; 
 scalar_t__ pmap_page_is_write_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_set_writeable_dirty (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 
 TYPE_1__* vm_radix_replace (int /*<<< orphan*/ *,TYPE_1__*) ; 

vm_page_t
vm_page_replace(vm_page_t mnew, vm_object_t object, vm_pindex_t pindex)
{
	vm_page_t mold;

	VM_OBJECT_ASSERT_WLOCKED(object);
	KASSERT(mnew->object == NULL && (mnew->ref_count & VPRC_OBJREF) == 0,
	    ("vm_page_replace: page %p already in object", mnew));

	/*
	 * This function mostly follows vm_page_insert() and
	 * vm_page_remove() without the radix, object count and vnode
	 * dance.  Double check such functions for more comments.
	 */

	mnew->object = object;
	mnew->pindex = pindex;
	atomic_set_int(&mnew->ref_count, VPRC_OBJREF);
	mold = vm_radix_replace(&object->rtree, mnew);
	KASSERT(mold->queue == PQ_NONE,
	    ("vm_page_replace: old page %p is on a paging queue", mold));

	/* Keep the resident page list in sorted order. */
	TAILQ_INSERT_AFTER(&object->memq, mold, mnew, listq);
	TAILQ_REMOVE(&object->memq, mold, listq);

	mold->object = NULL;
	atomic_clear_int(&mold->ref_count, VPRC_OBJREF);
	vm_page_xunbusy(mold);

	/*
	 * The object's resident_page_count does not change because we have
	 * swapped one page for another, but the generation count should
	 * change if the page is dirty.
	 */
	if (pmap_page_is_write_mapped(mnew))
		vm_object_set_writeable_dirty(object);
	return (mold);
}