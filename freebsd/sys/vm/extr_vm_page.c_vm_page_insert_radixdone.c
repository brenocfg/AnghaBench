#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_13__ {int resident_page_count; scalar_t__ type; int /*<<< orphan*/  handle; int /*<<< orphan*/  memq; } ;
struct TYPE_12__ {int ref_count; scalar_t__ pindex; TYPE_2__* object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ OBJT_VNODE ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int VPRC_OBJREF ; 
 int /*<<< orphan*/  listq ; 
 scalar_t__ pmap_page_is_write_mapped (TYPE_1__*) ; 
 int /*<<< orphan*/  vhold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_set_writeable_dirty (TYPE_2__*) ; 

__attribute__((used)) static void
vm_page_insert_radixdone(vm_page_t m, vm_object_t object, vm_page_t mpred)
{

	VM_OBJECT_ASSERT_WLOCKED(object);
	KASSERT(object != NULL && m->object == object,
	    ("vm_page_insert_radixdone: page %p has inconsistent object", m));
	KASSERT((m->ref_count & VPRC_OBJREF) != 0,
	    ("vm_page_insert_radixdone: page %p is missing object ref", m));
	if (mpred != NULL) {
		KASSERT(mpred->object == object,
		    ("vm_page_insert_radixdone: object doesn't contain mpred"));
		KASSERT(mpred->pindex < m->pindex,
		    ("vm_page_insert_radixdone: mpred doesn't precede pindex"));
	}

	if (mpred != NULL)
		TAILQ_INSERT_AFTER(&object->memq, mpred, m, listq);
	else
		TAILQ_INSERT_HEAD(&object->memq, m, listq);

	/*
	 * Show that the object has one more resident page.
	 */
	object->resident_page_count++;

	/*
	 * Hold the vnode until the last page is released.
	 */
	if (object->resident_page_count == 1 && object->type == OBJT_VNODE)
		vhold(object->handle);

	/*
	 * Since we are inserting a new and possibly dirty page,
	 * update the object's generation count.
	 */
	if (pmap_page_is_write_mapped(m))
		vm_object_set_writeable_dirty(object);
}