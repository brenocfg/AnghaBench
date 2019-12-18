#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_object_t ;
typedef  TYPE_3__* vm_map_entry_t ;
struct TYPE_6__ {TYPE_2__* vm_object; } ;
struct TYPE_8__ {int eflags; int /*<<< orphan*/ * cred; scalar_t__ start; scalar_t__ end; scalar_t__ offset; TYPE_1__ object; } ;
struct TYPE_7__ {scalar_t__ charge; int /*<<< orphan*/ * cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int /*<<< orphan*/  OBJT_DEFAULT ; 
 int /*<<< orphan*/  atop (scalar_t__) ; 
 TYPE_2__* vm_object_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vm_map_entry_back(vm_map_entry_t entry)
{
	vm_object_t object;

	KASSERT(entry->object.vm_object == NULL,
	    ("map entry %p has backing object", entry));
	KASSERT((entry->eflags & MAP_ENTRY_IS_SUB_MAP) == 0,
	    ("map entry %p is a submap", entry));
	object = vm_object_allocate(OBJT_DEFAULT,
	    atop(entry->end - entry->start));
	entry->object.vm_object = object;
	entry->offset = 0;
	if (entry->cred != NULL) {
		object->cred = entry->cred;
		object->charge = entry->end - entry->start;
		entry->cred = NULL;
	}
}