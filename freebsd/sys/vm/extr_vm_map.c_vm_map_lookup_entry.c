#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  int boolean_t ;
struct TYPE_10__ {scalar_t__ start; scalar_t__ end; struct TYPE_10__* right; struct TYPE_10__* left; } ;
struct TYPE_9__ {TYPE_2__ header; int /*<<< orphan*/  lock; TYPE_2__* root; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  VM_MAP_UNLOCK_CONSISTENT (TYPE_1__*) ; 
 int /*<<< orphan*/  sx_downgrade (int /*<<< orphan*/ *) ; 
 scalar_t__ sx_try_upgrade (int /*<<< orphan*/ *) ; 
 int vm_map_locked (TYPE_1__*) ; 
 TYPE_2__* vm_map_splay (TYPE_1__*,scalar_t__) ; 

boolean_t
vm_map_lookup_entry(
	vm_map_t map,
	vm_offset_t address,
	vm_map_entry_t *entry)	/* OUT */
{
	vm_map_entry_t cur, lbound;
	boolean_t locked;

	/*
	 * If the map is empty, then the map entry immediately preceding
	 * "address" is the map's header.
	 */
	cur = map->root;
	if (cur == NULL) {
		*entry = &map->header;
		return (FALSE);
	}
	if (address >= cur->start && cur->end > address) {
		*entry = cur;
		return (TRUE);
	}
	if ((locked = vm_map_locked(map)) ||
	    sx_try_upgrade(&map->lock)) {
		/*
		 * Splay requires a write lock on the map.  However, it only
		 * restructures the binary search tree; it does not otherwise
		 * change the map.  Thus, the map's timestamp need not change
		 * on a temporary upgrade.
		 */
		cur = vm_map_splay(map, address);
		if (!locked) {
			VM_MAP_UNLOCK_CONSISTENT(map);
			sx_downgrade(&map->lock);
		}

		/*
		 * If "address" is contained within a map entry, the new root
		 * is that map entry.  Otherwise, the new root is a map entry
		 * immediately before or after "address".
		 */
		if (address < cur->start) {
			*entry = &map->header;
			return (FALSE);
		}
		*entry = cur;
		return (address < cur->end);
	}
	/*
	 * Since the map is only locked for read access, perform a
	 * standard binary search tree lookup for "address".
	 */
	lbound = &map->header;
	do {
		if (address < cur->start) {
			cur = cur->left;
		} else if (cur->end <= address) {
			lbound = cur;
			cur = cur->right;
		} else {
			*entry = cur;
			return (TRUE);
		}
	} while (cur != NULL);
	*entry = lbound;
	return (FALSE);
}