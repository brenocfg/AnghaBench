#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_map_entry_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  vm_object; } ;
struct TYPE_6__ {int eflags; TYPE_1__ object; } ;

/* Variables and functions */
 int MAP_ENTRY_IS_SUB_MAP ; 
 int /*<<< orphan*/  kmapentzone ; 
 int /*<<< orphan*/  mapentzone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_map_entry_deallocate(vm_map_entry_t entry, boolean_t system_map)
{

	if ((entry->eflags & MAP_ENTRY_IS_SUB_MAP) == 0)
		vm_object_deallocate(entry->object.vm_object);
	uma_zfree(system_map ? kmapentzone : mapentzone, entry);
}