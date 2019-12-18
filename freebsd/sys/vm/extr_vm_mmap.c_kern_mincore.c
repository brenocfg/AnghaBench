#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_3__* vm_page_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_4__* vm_object_t ;
typedef  TYPE_5__* vm_map_t ;
typedef  TYPE_6__* vm_map_entry_t ;
struct thread {TYPE_1__* td_proc; } ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_31__ {unsigned int timestamp; } ;
struct TYPE_33__ {TYPE_5__ vm_map; } ;
struct TYPE_28__ {TYPE_4__* vm_object; } ;
struct TYPE_32__ {scalar_t__ start; scalar_t__ end; int eflags; scalar_t__ offset; TYPE_2__ object; } ;
struct TYPE_30__ {scalar_t__ type; } ;
struct TYPE_29__ {scalar_t__ dirty; int aflags; TYPE_4__* object; } ;
struct TYPE_27__ {TYPE_7__* p_vmspace; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int MINCORE_INCORE ; 
 int MINCORE_MODIFIED_OTHER ; 
 int MINCORE_REFERENCED_OTHER ; 
 scalar_t__ OBJT_DEFAULT ; 
 scalar_t__ OBJT_SWAP ; 
 scalar_t__ OBJT_VNODE ; 
 int /*<<< orphan*/  OFF_TO_IDX (scalar_t__) ; 
 scalar_t__ PAGE_SIZE ; 
 int PGA_REFERENCED ; 
 TYPE_3__* PHYS_TO_VM_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_4__*) ; 
 scalar_t__ atomic_load_ptr (TYPE_4__**) ; 
 int atop (scalar_t__) ; 
 scalar_t__ mincore_mapped ; 
 scalar_t__ pmap_extract (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pmap_is_modified (TYPE_3__*) ; 
 scalar_t__ pmap_is_referenced (TYPE_3__*) ; 
 int pmap_mincore (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 
 scalar_t__ round_page (uintptr_t) ; 
 int subyte (char*,int) ; 
 scalar_t__ trunc_page (uintptr_t) ; 
 TYPE_6__* vm_map_entry_succ (TYPE_6__*) ; 
 int /*<<< orphan*/  vm_map_lock_read (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_5__*,scalar_t__,TYPE_6__**) ; 
 scalar_t__ vm_map_max (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_map_unlock_read (TYPE_5__*) ; 
 int /*<<< orphan*/  vm_page_all_valid (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_3__*) ; 
 TYPE_3__* vm_page_lookup (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_none_valid (TYPE_3__*) ; 
 int /*<<< orphan*/  vmspace_pmap (TYPE_7__*) ; 

int
kern_mincore(struct thread *td, uintptr_t addr0, size_t len, char *vec)
{
	pmap_t pmap;
	vm_map_t map;
	vm_map_entry_t current, entry;
	vm_object_t object;
	vm_offset_t addr, cend, end, first_addr;
	vm_paddr_t pa;
	vm_page_t m;
	vm_pindex_t pindex;
	int error, lastvecindex, mincoreinfo, vecindex;
	unsigned int timestamp;

	/*
	 * Make sure that the addresses presented are valid for user
	 * mode.
	 */
	first_addr = addr = trunc_page(addr0);
	end = round_page(addr0 + len);
	map = &td->td_proc->p_vmspace->vm_map;
	if (end > vm_map_max(map) || end < addr)
		return (ENOMEM);

	pmap = vmspace_pmap(td->td_proc->p_vmspace);

	vm_map_lock_read(map);
RestartScan:
	timestamp = map->timestamp;

	if (!vm_map_lookup_entry(map, addr, &entry)) {
		vm_map_unlock_read(map);
		return (ENOMEM);
	}

	/*
	 * Do this on a map entry basis so that if the pages are not
	 * in the current processes address space, we can easily look
	 * up the pages elsewhere.
	 */
	lastvecindex = -1;
	while (entry->start < end) {

		/*
		 * check for contiguity
		 */
		current = entry;
		entry = vm_map_entry_succ(current);
		if (current->end < end &&
		    entry->start > current->end) {
			vm_map_unlock_read(map);
			return (ENOMEM);
		}

		/*
		 * ignore submaps (for now) or null objects
		 */
		if ((current->eflags & MAP_ENTRY_IS_SUB_MAP) ||
		    current->object.vm_object == NULL)
			continue;

		/*
		 * limit this scan to the current map entry and the
		 * limits for the mincore call
		 */
		if (addr < current->start)
			addr = current->start;
		cend = current->end;
		if (cend > end)
			cend = end;

		for (; addr < cend; addr += PAGE_SIZE) {
			/*
			 * Check pmap first, it is likely faster, also
			 * it can provide info as to whether we are the
			 * one referencing or modifying the page.
			 */
			m = NULL;
			object = NULL;
retry:
			pa = 0;
			mincoreinfo = pmap_mincore(pmap, addr, &pa);
			if (mincore_mapped) {
				/*
				 * We only care about this pmap's
				 * mapping of the page, if any.
				 */
				;
			} else if (pa != 0) {
				/*
				 * The page is mapped by this process but not
				 * both accessed and modified.  It is also
				 * managed.  Acquire the object lock so that
				 * other mappings might be examined.  The page's
				 * identity may change at any point before its
				 * object lock is acquired, so re-validate if
				 * necessary.
				 */
				m = PHYS_TO_VM_PAGE(pa);
				while (object == NULL || m->object != object) {
					if (object != NULL)
						VM_OBJECT_WUNLOCK(object);
					object = (vm_object_t)atomic_load_ptr(
					    &m->object);
					if (object == NULL)
						goto retry;
					VM_OBJECT_WLOCK(object);
				}
				if (pa != pmap_extract(pmap, addr))
					goto retry;
				KASSERT(vm_page_all_valid(m),
				    ("mincore: page %p is mapped but invalid",
				    m));
			} else if (mincoreinfo == 0) {
				/*
				 * The page is not mapped by this process.  If
				 * the object implements managed pages, then
				 * determine if the page is resident so that
				 * the mappings might be examined.
				 */
				if (current->object.vm_object != object) {
					if (object != NULL)
						VM_OBJECT_WUNLOCK(object);
					object = current->object.vm_object;
					VM_OBJECT_WLOCK(object);
				}
				if (object->type == OBJT_DEFAULT ||
				    object->type == OBJT_SWAP ||
				    object->type == OBJT_VNODE) {
					pindex = OFF_TO_IDX(current->offset +
					    (addr - current->start));
					m = vm_page_lookup(object, pindex);
					if (m != NULL && vm_page_none_valid(m))
						m = NULL;
					if (m != NULL)
						mincoreinfo = MINCORE_INCORE;
				}
			}
			if (m != NULL) {
				VM_OBJECT_ASSERT_WLOCKED(m->object);

				/* Examine other mappings of the page. */
				if (m->dirty == 0 && pmap_is_modified(m))
					vm_page_dirty(m);
				if (m->dirty != 0)
					mincoreinfo |= MINCORE_MODIFIED_OTHER;

				/*
				 * The first test for PGA_REFERENCED is an
				 * optimization.  The second test is
				 * required because a concurrent pmap
				 * operation could clear the last reference
				 * and set PGA_REFERENCED before the call to
				 * pmap_is_referenced(). 
				 */
				if ((m->aflags & PGA_REFERENCED) != 0 ||
				    pmap_is_referenced(m) ||
				    (m->aflags & PGA_REFERENCED) != 0)
					mincoreinfo |= MINCORE_REFERENCED_OTHER;
			}
			if (object != NULL)
				VM_OBJECT_WUNLOCK(object);

			/*
			 * subyte may page fault.  In case it needs to modify
			 * the map, we release the lock.
			 */
			vm_map_unlock_read(map);

			/*
			 * calculate index into user supplied byte vector
			 */
			vecindex = atop(addr - first_addr);

			/*
			 * If we have skipped map entries, we need to make sure that
			 * the byte vector is zeroed for those skipped entries.
			 */
			while ((lastvecindex + 1) < vecindex) {
				++lastvecindex;
				error = subyte(vec + lastvecindex, 0);
				if (error) {
					error = EFAULT;
					goto done2;
				}
			}

			/*
			 * Pass the page information to the user
			 */
			error = subyte(vec + vecindex, mincoreinfo);
			if (error) {
				error = EFAULT;
				goto done2;
			}

			/*
			 * If the map has changed, due to the subyte, the previous
			 * output may be invalid.
			 */
			vm_map_lock_read(map);
			if (timestamp != map->timestamp)
				goto RestartScan;

			lastvecindex = vecindex;
		}
	}

	/*
	 * subyte may page fault.  In case it needs to modify
	 * the map, we release the lock.
	 */
	vm_map_unlock_read(map);

	/*
	 * Zero the last entries in the byte vector.
	 */
	vecindex = atop(end - first_addr);
	while ((lastvecindex + 1) < vecindex) {
		++lastvecindex;
		error = subyte(vec + lastvecindex, 0);
		if (error) {
			error = EFAULT;
			goto done2;
		}
	}

	/*
	 * If the map has changed, due to the subyte, the previous
	 * output may be invalid.
	 */
	vm_map_lock_read(map);
	if (timestamp != map->timestamp)
		goto RestartScan;
	vm_map_unlock_read(map);
done2:
	return (error);
}