#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* pgo_dealloc ) (TYPE_1__*) ;} ;
struct TYPE_6__ {size_t type; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_1__*) ; 
 TYPE_4__** pagertab ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
vm_pager_deallocate(vm_object_t object)
{

	VM_OBJECT_ASSERT_WLOCKED(object);
	(*pagertab[object->type]->pgo_dealloc) (object);
}