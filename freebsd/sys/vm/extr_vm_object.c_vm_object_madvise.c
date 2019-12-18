#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_24__ {int /*<<< orphan*/  backing_object_offset; struct TYPE_24__* backing_object; } ;
struct TYPE_23__ {scalar_t__ pindex; int flags; int oflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MADV_WILLNEED ; 
 scalar_t__ OFF_TO_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int PG_FICTITIOUS ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  vm_object_advice_applies (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_object_madvise_freespace (TYPE_2__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  vm_page_advise (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_aflag_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_all_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_busy_sleep (TYPE_1__*,char*,int) ; 
 TYPE_1__* vm_page_find_least (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_lock (TYPE_1__*) ; 
 TYPE_1__* vm_page_lookup (TYPE_2__*,scalar_t__) ; 
 scalar_t__ vm_page_tryxbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unlock (TYPE_1__*) ; 
 scalar_t__ vm_page_wired (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 

void
vm_object_madvise(vm_object_t object, vm_pindex_t pindex, vm_pindex_t end,
    int advice)
{
	vm_pindex_t tpindex;
	vm_object_t backing_object, tobject;
	vm_page_t m, tm;

	if (object == NULL)
		return;

relookup:
	VM_OBJECT_WLOCK(object);
	if (!vm_object_advice_applies(object, advice)) {
		VM_OBJECT_WUNLOCK(object);
		return;
	}
	for (m = vm_page_find_least(object, pindex); pindex < end; pindex++) {
		tobject = object;

		/*
		 * If the next page isn't resident in the top-level object, we
		 * need to search the shadow chain.  When applying MADV_FREE, we
		 * take care to release any swap space used to store
		 * non-resident pages.
		 */
		if (m == NULL || pindex < m->pindex) {
			/*
			 * Optimize a common case: if the top-level object has
			 * no backing object, we can skip over the non-resident
			 * range in constant time.
			 */
			if (object->backing_object == NULL) {
				tpindex = (m != NULL && m->pindex < end) ?
				    m->pindex : end;
				vm_object_madvise_freespace(object, advice,
				    pindex, tpindex - pindex);
				if ((pindex = tpindex) == end)
					break;
				goto next_page;
			}

			tpindex = pindex;
			do {
				vm_object_madvise_freespace(tobject, advice,
				    tpindex, 1);
				/*
				 * Prepare to search the next object in the
				 * chain.
				 */
				backing_object = tobject->backing_object;
				if (backing_object == NULL)
					goto next_pindex;
				VM_OBJECT_WLOCK(backing_object);
				tpindex +=
				    OFF_TO_IDX(tobject->backing_object_offset);
				if (tobject != object)
					VM_OBJECT_WUNLOCK(tobject);
				tobject = backing_object;
				if (!vm_object_advice_applies(tobject, advice))
					goto next_pindex;
			} while ((tm = vm_page_lookup(tobject, tpindex)) ==
			    NULL);
		} else {
next_page:
			tm = m;
			m = TAILQ_NEXT(m, listq);
		}

		/*
		 * If the page is not in a normal state, skip it.  The page
		 * can not be invalidated while the object lock is held.
		 */
		if (!vm_page_all_valid(tm) || vm_page_wired(tm))
			goto next_pindex;
		KASSERT((tm->flags & PG_FICTITIOUS) == 0,
		    ("vm_object_madvise: page %p is fictitious", tm));
		KASSERT((tm->oflags & VPO_UNMANAGED) == 0,
		    ("vm_object_madvise: page %p is not managed", tm));
		if (vm_page_tryxbusy(tm) == 0) {
			if (object != tobject)
				VM_OBJECT_WUNLOCK(object);
			if (advice == MADV_WILLNEED) {
				/*
				 * Reference the page before unlocking and
				 * sleeping so that the page daemon is less
				 * likely to reclaim it.
				 */
				vm_page_aflag_set(tm, PGA_REFERENCED);
			}
			vm_page_busy_sleep(tm, "madvpo", false);
  			goto relookup;
		}
		vm_page_lock(tm);
		vm_page_advise(tm, advice);
		vm_page_unlock(tm);
		vm_page_xunbusy(tm);
		vm_object_madvise_freespace(tobject, advice, tm->pindex, 1);
next_pindex:
		if (tobject != object)
			VM_OBJECT_WUNLOCK(tobject);
	}
	VM_OBJECT_WUNLOCK(object);
}