#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  TYPE_2__* vm_object_t ;
typedef  int boolean_t ;
struct TYPE_17__ {scalar_t__ type; scalar_t__ resident_page_count; scalar_t__ size; int generation; int cleangeneration; } ;
struct TYPE_16__ {scalar_t__ pindex; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int OBJPC_INVAL ; 
 int OBJPC_SYNC ; 
 scalar_t__ OBJT_VNODE ; 
 scalar_t__ OFF_TO_IDX (scalar_t__) ; 
 scalar_t__ PAGE_MASK ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  VM_ALLOC_WAITFAIL ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int VM_PAGER_CLUSTER_OK ; 
 int VM_PAGER_PUT_INVAL ; 
 int VM_PAGER_PUT_SYNC ; 
 int /*<<< orphan*/  VOP_FSYNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  vm_object_mightbedirty (TYPE_2__*) ; 
 int vm_object_page_collect_flush (TYPE_2__*,TYPE_1__*,int,int,int*,int*) ; 
 int /*<<< orphan*/  vm_object_page_remove_write (TYPE_1__*,int,int*) ; 
 scalar_t__ vm_page_busy_acquire (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_page_find_least (TYPE_2__*,scalar_t__) ; 
 scalar_t__ vm_page_none_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 
 int /*<<< orphan*/  vp ; 

boolean_t
vm_object_page_clean(vm_object_t object, vm_ooffset_t start, vm_ooffset_t end,
    int flags)
{
	vm_page_t np, p;
	vm_pindex_t pi, tend, tstart;
	int curgeneration, n, pagerflags;
	boolean_t eio, res, allclean;

	VM_OBJECT_ASSERT_WLOCKED(object);

	if (object->type != OBJT_VNODE || !vm_object_mightbedirty(object) ||
	    object->resident_page_count == 0)
		return (TRUE);

	pagerflags = (flags & (OBJPC_SYNC | OBJPC_INVAL)) != 0 ?
	    VM_PAGER_PUT_SYNC : VM_PAGER_CLUSTER_OK;
	pagerflags |= (flags & OBJPC_INVAL) != 0 ? VM_PAGER_PUT_INVAL : 0;

	tstart = OFF_TO_IDX(start);
	tend = (end == 0) ? object->size : OFF_TO_IDX(end + PAGE_MASK);
	allclean = tstart == 0 && tend >= object->size;
	res = TRUE;

rescan:
	curgeneration = object->generation;

	for (p = vm_page_find_least(object, tstart); p != NULL; p = np) {
		pi = p->pindex;
		if (pi >= tend)
			break;
		np = TAILQ_NEXT(p, listq);
		if (vm_page_none_valid(p))
			continue;
		if (vm_page_busy_acquire(p, VM_ALLOC_WAITFAIL) == 0) {
			if (object->generation != curgeneration &&
			    (flags & OBJPC_SYNC) != 0)
				goto rescan;
			np = vm_page_find_least(object, pi);
			continue;
		}
		if (!vm_object_page_remove_write(p, flags, &allclean)) {
			vm_page_xunbusy(p);
			continue;
		}

		n = vm_object_page_collect_flush(object, p, pagerflags,
		    flags, &allclean, &eio);
		if (eio) {
			res = FALSE;
			allclean = FALSE;
		}
		if (object->generation != curgeneration &&
		    (flags & OBJPC_SYNC) != 0)
			goto rescan;

		/*
		 * If the VOP_PUTPAGES() did a truncated write, so
		 * that even the first page of the run is not fully
		 * written, vm_pageout_flush() returns 0 as the run
		 * length.  Since the condition that caused truncated
		 * write may be permanent, e.g. exhausted free space,
		 * accepting n == 0 would cause an infinite loop.
		 *
		 * Forwarding the iterator leaves the unwritten page
		 * behind, but there is not much we can do there if
		 * filesystem refuses to write it.
		 */
		if (n == 0) {
			n = 1;
			allclean = FALSE;
		}
		np = vm_page_find_least(object, pi + n);
	}
#if 0
	VOP_FSYNC(vp, (pagerflags & VM_PAGER_PUT_SYNC) ? MNT_WAIT : 0);
#endif

	if (allclean)
		object->cleangeneration = curgeneration;
	return (res);
}