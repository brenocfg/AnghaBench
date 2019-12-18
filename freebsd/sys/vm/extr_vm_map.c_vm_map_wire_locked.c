#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ u_int ;
struct TYPE_31__ {scalar_t__ start; int eflags; int protection; scalar_t__ end; int wired_count; int /*<<< orphan*/ * wiring_thread; } ;
struct TYPE_30__ {scalar_t__ timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KERN_INVALID_ADDRESS ; 
 int KERN_RESOURCE_SHORTAGE ; 
 int KERN_SUCCESS ; 
 int MAP_ENTRY_IN_TRANSITION ; 
 int MAP_ENTRY_NEEDS_WAKEUP ; 
 int MAP_ENTRY_USER_WIRED ; 
 int MAP_ENTRY_WIRE_SKIPPED ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_FAULT_WIRE ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_MAP_RANGE_CHECK (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int VM_MAP_WIRE_HOLESOK ; 
 int VM_MAP_WIRE_USER ; 
 int VM_MAP_WIRE_WRITE ; 
 int VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  atop (scalar_t__) ; 
 int /*<<< orphan*/ * curthread ; 
 int vm_fault (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_clip_end (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_start (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 TYPE_2__* vm_map_entry_in_transition (TYPE_1__*,scalar_t__,scalar_t__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_entry_pred (TYPE_2__*) ; 
 TYPE_2__* vm_map_entry_succ (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_entry_unwire (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_1__*,scalar_t__,TYPE_2__**) ; 
 int /*<<< orphan*/  vm_map_try_merge_entries (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_unbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_wakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_wire_entry_failure (TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_wire_user_count_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_wire_user_count_sub (int /*<<< orphan*/ ) ; 

int
vm_map_wire_locked(vm_map_t map, vm_offset_t start, vm_offset_t end, int flags)
{
	vm_map_entry_t entry, first_entry, tmp_entry;
	vm_offset_t faddr, saved_end, saved_start;
	u_long npages;
	u_int last_timestamp;
	int rv;
	bool first_iteration, holes_ok, need_wakeup, user_wire;
	vm_prot_t prot;

	VM_MAP_ASSERT_LOCKED(map);

	if (start == end)
		return (KERN_SUCCESS);
	prot = 0;
	if (flags & VM_MAP_WIRE_WRITE)
		prot |= VM_PROT_WRITE;
	holes_ok = (flags & VM_MAP_WIRE_HOLESOK) != 0;
	user_wire = (flags & VM_MAP_WIRE_USER) != 0;
	VM_MAP_RANGE_CHECK(map, start, end);
	if (!vm_map_lookup_entry(map, start, &first_entry)) {
		if (holes_ok)
			first_entry = vm_map_entry_succ(first_entry);
		else
			return (KERN_INVALID_ADDRESS);
	}
	first_iteration = true;
	entry = first_entry;
	while (entry->start < end) {
		if (entry->eflags & MAP_ENTRY_IN_TRANSITION) {
			/*
			 * We have not yet clipped the entry.
			 */
			entry = vm_map_entry_in_transition(map, start, &end,
			    holes_ok, entry);
			if (entry == NULL) {
				if (first_iteration)
					return (KERN_INVALID_ADDRESS);
				rv = KERN_INVALID_ADDRESS;
				goto done;
			}
			first_entry = first_iteration ? entry : NULL;
			continue;
		}
		first_iteration = false;
		vm_map_clip_start(map, entry, start);
		vm_map_clip_end(map, entry, end);
		/*
		 * Mark the entry in case the map lock is released.  (See
		 * above.)
		 */
		KASSERT((entry->eflags & MAP_ENTRY_IN_TRANSITION) == 0 &&
		    entry->wiring_thread == NULL,
		    ("owned map entry %p", entry));
		entry->eflags |= MAP_ENTRY_IN_TRANSITION;
		entry->wiring_thread = curthread;
		if ((entry->protection & (VM_PROT_READ | VM_PROT_EXECUTE)) == 0
		    || (entry->protection & prot) != prot) {
			entry->eflags |= MAP_ENTRY_WIRE_SKIPPED;
			if (!holes_ok) {
				end = entry->end;
				rv = KERN_INVALID_ADDRESS;
				goto done;
			}
		} else if (entry->wired_count == 0) {
			entry->wired_count++;

			npages = atop(entry->end - entry->start);
			if (user_wire && !vm_map_wire_user_count_add(npages)) {
				vm_map_wire_entry_failure(map, entry,
				    entry->start);
				end = entry->end;
				rv = KERN_RESOURCE_SHORTAGE;
				goto done;
			}

			/*
			 * Release the map lock, relying on the in-transition
			 * mark.  Mark the map busy for fork.
			 */
			saved_start = entry->start;
			saved_end = entry->end;
			last_timestamp = map->timestamp;
			vm_map_busy(map);
			vm_map_unlock(map);

			faddr = saved_start;
			do {
				/*
				 * Simulate a fault to get the page and enter
				 * it into the physical map.
				 */
				if ((rv = vm_fault(map, faddr,
				    VM_PROT_NONE, VM_FAULT_WIRE, NULL)) !=
				    KERN_SUCCESS)
					break;
			} while ((faddr += PAGE_SIZE) < saved_end);
			vm_map_lock(map);
			vm_map_unbusy(map);
			if (last_timestamp + 1 != map->timestamp) {
				/*
				 * Look again for the entry because the map was
				 * modified while it was unlocked.  The entry
				 * may have been clipped, but NOT merged or
				 * deleted.
				 */
				if (!vm_map_lookup_entry(map, saved_start,
				    &tmp_entry))
					KASSERT(false,
					    ("vm_map_wire: lookup failed"));
				if (entry == first_entry)
					first_entry = tmp_entry;
				else
					first_entry = NULL;
				entry = tmp_entry;
				while (entry->end < saved_end) {
					/*
					 * In case of failure, handle entries
					 * that were not fully wired here;
					 * fully wired entries are handled
					 * later.
					 */
					if (rv != KERN_SUCCESS &&
					    faddr < entry->end)
						vm_map_wire_entry_failure(map,
						    entry, faddr);
					entry = vm_map_entry_succ(entry);
				}
			}
			if (rv != KERN_SUCCESS) {
				vm_map_wire_entry_failure(map, entry, faddr);
				if (user_wire)
					vm_map_wire_user_count_sub(npages);
				end = entry->end;
				goto done;
			}
		} else if (!user_wire ||
			   (entry->eflags & MAP_ENTRY_USER_WIRED) == 0) {
			entry->wired_count++;
		}
		/*
		 * Check the map for holes in the specified region.
		 * If holes_ok was specified, skip this check.
		 */
		if (!holes_ok &&
		    entry->end < end &&
		    vm_map_entry_succ(entry)->start > entry->end) {
			end = entry->end;
			rv = KERN_INVALID_ADDRESS;
			goto done;
		}
		entry = vm_map_entry_succ(entry);
	}
	rv = KERN_SUCCESS;
done:
	need_wakeup = false;
	if (first_entry == NULL &&
	    !vm_map_lookup_entry(map, start, &first_entry)) {
		KASSERT(holes_ok, ("vm_map_wire: lookup failed"));
		first_entry = vm_map_entry_succ(first_entry);
	}
	for (entry = first_entry; entry->start < end;
	    entry = vm_map_entry_succ(entry)) {
		/*
		 * If holes_ok was specified, an empty
		 * space in the unwired region could have been mapped
		 * while the map lock was dropped for faulting in the
		 * pages or draining MAP_ENTRY_IN_TRANSITION.
		 * Moreover, another thread could be simultaneously
		 * wiring this new mapping entry.  Detect these cases
		 * and skip any entries marked as in transition not by us.
		 */
		if ((entry->eflags & MAP_ENTRY_IN_TRANSITION) == 0 ||
		    entry->wiring_thread != curthread) {
			KASSERT(holes_ok,
			    ("vm_map_wire: !HOLESOK and new/changed entry"));
			continue;
		}

		if ((entry->eflags & MAP_ENTRY_WIRE_SKIPPED) != 0) {
			/* do nothing */
		} else if (rv == KERN_SUCCESS) {
			if (user_wire)
				entry->eflags |= MAP_ENTRY_USER_WIRED;
		} else if (entry->wired_count == -1) {
			/*
			 * Wiring failed on this entry.  Thus, unwiring is
			 * unnecessary.
			 */
			entry->wired_count = 0;
		} else if (!user_wire ||
		    (entry->eflags & MAP_ENTRY_USER_WIRED) == 0) {
			/*
			 * Undo the wiring.  Wiring succeeded on this entry
			 * but failed on a later entry.  
			 */
			if (entry->wired_count == 1) {
				vm_map_entry_unwire(map, entry);
				if (user_wire)
					vm_map_wire_user_count_sub(
					    atop(entry->end - entry->start));
			} else
				entry->wired_count--;
		}
		KASSERT((entry->eflags & MAP_ENTRY_IN_TRANSITION) != 0,
		    ("vm_map_wire: in-transition flag missing %p", entry));
		KASSERT(entry->wiring_thread == curthread,
		    ("vm_map_wire: alien wire %p", entry));
		entry->eflags &= ~(MAP_ENTRY_IN_TRANSITION |
		    MAP_ENTRY_WIRE_SKIPPED);
		entry->wiring_thread = NULL;
		if (entry->eflags & MAP_ENTRY_NEEDS_WAKEUP) {
			entry->eflags &= ~MAP_ENTRY_NEEDS_WAKEUP;
			need_wakeup = true;
		}
		vm_map_try_merge_entries(map, vm_map_entry_pred(entry), entry);
	}
	vm_map_try_merge_entries(map, vm_map_entry_pred(entry), entry);
	if (need_wakeup)
		vm_map_wakeup(map);
	return (rv);
}