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
struct TYPE_15__ {int /*<<< orphan*/  rtree; int /*<<< orphan*/  memq; } ;
struct TYPE_14__ {scalar_t__ pindex; int /*<<< orphan*/  ref_count; TYPE_2__* object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  VPRC_OBJREF ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  vm_page_insert_radixdone (TYPE_1__*,TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ vm_radix_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
vm_page_insert_after(vm_page_t m, vm_object_t object, vm_pindex_t pindex,
    vm_page_t mpred)
{
	vm_page_t msucc;

	VM_OBJECT_ASSERT_WLOCKED(object);
	KASSERT(m->object == NULL,
	    ("vm_page_insert_after: page already inserted"));
	if (mpred != NULL) {
		KASSERT(mpred->object == object,
		    ("vm_page_insert_after: object doesn't contain mpred"));
		KASSERT(mpred->pindex < pindex,
		    ("vm_page_insert_after: mpred doesn't precede pindex"));
		msucc = TAILQ_NEXT(mpred, listq);
	} else
		msucc = TAILQ_FIRST(&object->memq);
	if (msucc != NULL)
		KASSERT(msucc->pindex > pindex,
		    ("vm_page_insert_after: msucc doesn't succeed pindex"));

	/*
	 * Record the object/offset pair in this page.
	 */
	m->object = object;
	m->pindex = pindex;
	m->ref_count |= VPRC_OBJREF;

	/*
	 * Now link into the object's ordered list of backed pages.
	 */
	if (vm_radix_insert(&object->rtree, m)) {
		m->object = NULL;
		m->pindex = 0;
		m->ref_count &= ~VPRC_OBJREF;
		return (1);
	}
	vm_page_insert_radixdone(m, object, mpred);
	return (0);
}