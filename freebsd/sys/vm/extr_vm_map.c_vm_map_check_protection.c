#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {scalar_t__ start; int protection; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* vm_map_entry_succ (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (int /*<<< orphan*/ ,scalar_t__,TYPE_1__**) ; 

boolean_t
vm_map_check_protection(vm_map_t map, vm_offset_t start, vm_offset_t end,
			vm_prot_t protection)
{
	vm_map_entry_t entry;
	vm_map_entry_t tmp_entry;

	if (!vm_map_lookup_entry(map, start, &tmp_entry))
		return (FALSE);
	entry = tmp_entry;

	while (start < end) {
		/*
		 * No holes allowed!
		 */
		if (start < entry->start)
			return (FALSE);
		/*
		 * Check protection associated with entry.
		 */
		if ((entry->protection & protection) != protection)
			return (FALSE);
		/* go to next entry */
		start = entry->end;
		entry = vm_map_entry_succ(entry);
	}
	return (TRUE);
}