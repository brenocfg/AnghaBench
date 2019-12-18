#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_9__ {int /*<<< orphan*/  rtree; int /*<<< orphan*/  memq; } ;
struct TYPE_8__ {scalar_t__ pindex; } ;

/* Variables and functions */
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (TYPE_2__*) ; 
 TYPE_1__* vm_radix_lookup_ge (int /*<<< orphan*/ *,scalar_t__) ; 

vm_page_t
vm_page_find_least(vm_object_t object, vm_pindex_t pindex)
{
	vm_page_t m;

	VM_OBJECT_ASSERT_LOCKED(object);
	if ((m = TAILQ_FIRST(&object->memq)) != NULL && m->pindex < pindex)
		m = vm_radix_lookup_ge(&object->rtree, pindex);
	return (m);
}