#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_3__* vm_object_t ;
typedef  TYPE_4__* vm_map_entry_t ;
struct faultstate {TYPE_1__* map; TYPE_4__* entry; TYPE_3__* first_object; TYPE_3__* object; } ;
struct TYPE_22__ {scalar_t__ start; int /*<<< orphan*/  offset; } ;
struct TYPE_21__ {int flags; } ;
struct TYPE_20__ {scalar_t__ pindex; } ;
struct TYPE_19__ {int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADV_DONTNEED ; 
 int MAXPAGESIZES ; 
 int OBJ_FICTITIOUS ; 
 int OBJ_UNMANAGED ; 
 scalar_t__ OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_2__* TAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VM_FAULT_DONTNEED_MIN ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_TRYWLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_3__*) ; 
 scalar_t__ atop (scalar_t__) ; 
 int /*<<< orphan*/  listq ; 
 scalar_t__* pagesizes ; 
 int /*<<< orphan*/  pmap_advise (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ptoa (int) ; 
 scalar_t__ rounddown2 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_all_valid (TYPE_2__*) ; 
 scalar_t__ vm_page_busied (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_deactivate (TYPE_2__*) ; 
 TYPE_2__* vm_page_find_least (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_inactive (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_unlock (TYPE_2__*) ; 

__attribute__((used)) static void
vm_fault_dontneed(const struct faultstate *fs, vm_offset_t vaddr, int ahead)
{
	vm_map_entry_t entry;
	vm_object_t first_object, object;
	vm_offset_t end, start;
	vm_page_t m, m_next;
	vm_pindex_t pend, pstart;
	vm_size_t size;

	object = fs->object;
	VM_OBJECT_ASSERT_WLOCKED(object);
	first_object = fs->first_object;
	if (first_object != object) {
		if (!VM_OBJECT_TRYWLOCK(first_object)) {
			VM_OBJECT_WUNLOCK(object);
			VM_OBJECT_WLOCK(first_object);
			VM_OBJECT_WLOCK(object);
		}
	}
	/* Neither fictitious nor unmanaged pages can be reclaimed. */
	if ((first_object->flags & (OBJ_FICTITIOUS | OBJ_UNMANAGED)) == 0) {
		size = VM_FAULT_DONTNEED_MIN;
		if (MAXPAGESIZES > 1 && size < pagesizes[1])
			size = pagesizes[1];
		end = rounddown2(vaddr, size);
		if (vaddr - end >= size - PAGE_SIZE - ptoa(ahead) &&
		    (entry = fs->entry)->start < end) {
			if (end - entry->start < size)
				start = entry->start;
			else
				start = end - size;
			pmap_advise(fs->map->pmap, start, end, MADV_DONTNEED);
			pstart = OFF_TO_IDX(entry->offset) + atop(start -
			    entry->start);
			m_next = vm_page_find_least(first_object, pstart);
			pend = OFF_TO_IDX(entry->offset) + atop(end -
			    entry->start);
			while ((m = m_next) != NULL && m->pindex < pend) {
				m_next = TAILQ_NEXT(m, listq);
				if (!vm_page_all_valid(m) ||
				    vm_page_busied(m))
					continue;

				/*
				 * Don't clear PGA_REFERENCED, since it would
				 * likely represent a reference by a different
				 * process.
				 *
				 * Typically, at this point, prefetched pages
				 * are still in the inactive queue.  Only
				 * pages that triggered page faults are in the
				 * active queue.
				 */
				vm_page_lock(m);
				if (!vm_page_inactive(m))
					vm_page_deactivate(m);
				vm_page_unlock(m);
			}
		}
	}
	if (first_object != object)
		VM_OBJECT_WUNLOCK(first_object);
}