#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  TYPE_3__* vm_map_entry_t ;
struct TYPE_28__ {int /*<<< orphan*/ * backing_object; } ;
struct TYPE_25__ {TYPE_4__* vm_object; } ;
struct TYPE_27__ {scalar_t__ start; int eflags; scalar_t__ end; scalar_t__ wired_count; TYPE_1__ object; int /*<<< orphan*/  protection; int /*<<< orphan*/  offset; } ;
struct TYPE_26__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MADV_AUTOSYNC 137 
#define  MADV_CORE 136 
#define  MADV_DONTNEED 135 
#define  MADV_FREE 134 
#define  MADV_NOCORE 133 
#define  MADV_NORMAL 132 
#define  MADV_NOSYNC 131 
#define  MADV_RANDOM 130 
#define  MADV_SEQUENTIAL 129 
#define  MADV_WILLNEED 128 
 int /*<<< orphan*/  MAP_ENTRY_BEHAV_NORMAL ; 
 int /*<<< orphan*/  MAP_ENTRY_BEHAV_RANDOM ; 
 int /*<<< orphan*/  MAP_ENTRY_BEHAV_SEQUENTIAL ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int MAP_ENTRY_NOCOREDUMP ; 
 int MAP_ENTRY_NOSYNC ; 
 int /*<<< orphan*/  MAP_PREFAULT_MADVISE ; 
 scalar_t__ OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_RANGE_CHECK (TYPE_2__*,scalar_t__,scalar_t__) ; 
 scalar_t__ atop (scalar_t__) ; 
 int /*<<< orphan*/  pmap_advise (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ptoa (scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_end (TYPE_2__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_start (TYPE_2__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_entry_pred (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_entry_set_behavior (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* vm_map_entry_succ (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_2__*) ; 
 scalar_t__ vm_map_lookup_entry (TYPE_2__*,scalar_t__,TYPE_3__**) ; 
 int /*<<< orphan*/  vm_map_pmap_enter (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_try_merge_entries (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_madvise (TYPE_4__*,scalar_t__,scalar_t__,int) ; 

int
vm_map_madvise(
	vm_map_t map,
	vm_offset_t start,
	vm_offset_t end,
	int behav)
{
	vm_map_entry_t current, entry;
	bool modify_map;

	/*
	 * Some madvise calls directly modify the vm_map_entry, in which case
	 * we need to use an exclusive lock on the map and we need to perform
	 * various clipping operations.  Otherwise we only need a read-lock
	 * on the map.
	 */
	switch(behav) {
	case MADV_NORMAL:
	case MADV_SEQUENTIAL:
	case MADV_RANDOM:
	case MADV_NOSYNC:
	case MADV_AUTOSYNC:
	case MADV_NOCORE:
	case MADV_CORE:
		if (start == end)
			return (0);
		modify_map = true;
		vm_map_lock(map);
		break;
	case MADV_WILLNEED:
	case MADV_DONTNEED:
	case MADV_FREE:
		if (start == end)
			return (0);
		modify_map = false;
		vm_map_lock_read(map);
		break;
	default:
		return (EINVAL);
	}

	/*
	 * Locate starting entry and clip if necessary.
	 */
	VM_MAP_RANGE_CHECK(map, start, end);

	if (vm_map_lookup_entry(map, start, &entry)) {
		if (modify_map)
			vm_map_clip_start(map, entry, start);
	} else {
		entry = vm_map_entry_succ(entry);
	}

	if (modify_map) {
		/*
		 * madvise behaviors that are implemented in the vm_map_entry.
		 *
		 * We clip the vm_map_entry so that behavioral changes are
		 * limited to the specified address range.
		 */
		for (current = entry; current->start < end;
		    current = vm_map_entry_succ(current)) {
			if (current->eflags & MAP_ENTRY_IS_SUB_MAP)
				continue;

			vm_map_clip_end(map, current, end);

			switch (behav) {
			case MADV_NORMAL:
				vm_map_entry_set_behavior(current, MAP_ENTRY_BEHAV_NORMAL);
				break;
			case MADV_SEQUENTIAL:
				vm_map_entry_set_behavior(current, MAP_ENTRY_BEHAV_SEQUENTIAL);
				break;
			case MADV_RANDOM:
				vm_map_entry_set_behavior(current, MAP_ENTRY_BEHAV_RANDOM);
				break;
			case MADV_NOSYNC:
				current->eflags |= MAP_ENTRY_NOSYNC;
				break;
			case MADV_AUTOSYNC:
				current->eflags &= ~MAP_ENTRY_NOSYNC;
				break;
			case MADV_NOCORE:
				current->eflags |= MAP_ENTRY_NOCOREDUMP;
				break;
			case MADV_CORE:
				current->eflags &= ~MAP_ENTRY_NOCOREDUMP;
				break;
			default:
				break;
			}
			vm_map_try_merge_entries(map,
			    vm_map_entry_pred(current), current);
		}
		vm_map_try_merge_entries(map, vm_map_entry_pred(current),
		    current);
		vm_map_unlock(map);
	} else {
		vm_pindex_t pstart, pend;

		/*
		 * madvise behaviors that are implemented in the underlying
		 * vm_object.
		 *
		 * Since we don't clip the vm_map_entry, we have to clip
		 * the vm_object pindex and count.
		 */
		for (current = entry; current->start < end;
		    current = vm_map_entry_succ(current)) {
			vm_offset_t useEnd, useStart;

			if (current->eflags & MAP_ENTRY_IS_SUB_MAP)
				continue;

			/*
			 * MADV_FREE would otherwise rewind time to
			 * the creation of the shadow object.  Because
			 * we hold the VM map read-locked, neither the
			 * entry's object nor the presence of a
			 * backing object can change.
			 */
			if (behav == MADV_FREE &&
			    current->object.vm_object != NULL &&
			    current->object.vm_object->backing_object != NULL)
				continue;

			pstart = OFF_TO_IDX(current->offset);
			pend = pstart + atop(current->end - current->start);
			useStart = current->start;
			useEnd = current->end;

			if (current->start < start) {
				pstart += atop(start - current->start);
				useStart = start;
			}
			if (current->end > end) {
				pend -= atop(current->end - end);
				useEnd = end;
			}

			if (pstart >= pend)
				continue;

			/*
			 * Perform the pmap_advise() before clearing
			 * PGA_REFERENCED in vm_page_advise().  Otherwise, a
			 * concurrent pmap operation, such as pmap_remove(),
			 * could clear a reference in the pmap and set
			 * PGA_REFERENCED on the page before the pmap_advise()
			 * had completed.  Consequently, the page would appear
			 * referenced based upon an old reference that
			 * occurred before this pmap_advise() ran.
			 */
			if (behav == MADV_DONTNEED || behav == MADV_FREE)
				pmap_advise(map->pmap, useStart, useEnd,
				    behav);

			vm_object_madvise(current->object.vm_object, pstart,
			    pend, behav);

			/*
			 * Pre-populate paging structures in the
			 * WILLNEED case.  For wired entries, the
			 * paging structures are already populated.
			 */
			if (behav == MADV_WILLNEED &&
			    current->wired_count == 0) {
				vm_map_pmap_enter(map,
				    useStart,
				    current->protection,
				    current->object.vm_object,
				    pstart,
				    ptoa(pend - pstart),
				    MAP_PREFAULT_MADVISE
				);
			}
		}
		vm_map_unlock_read(map);
	}
	return (0);
}