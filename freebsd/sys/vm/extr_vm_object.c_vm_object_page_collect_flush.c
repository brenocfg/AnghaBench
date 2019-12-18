#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/ * TAILQ_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listq ; 
 int /*<<< orphan*/  vm_object_page_remove_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_assert_xbusied (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_lock_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_page_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vm_page_prev (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_page_tryxbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_xunbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pageout_flush (int /*<<< orphan*/ **,int,int,int,int*,int /*<<< orphan*/ *) ; 
 int vm_pageout_page_count ; 

__attribute__((used)) static int
vm_object_page_collect_flush(vm_object_t object, vm_page_t p, int pagerflags,
    int flags, boolean_t *allclean, boolean_t *eio)
{
	vm_page_t ma[vm_pageout_page_count], p_first, tp;
	int count, i, mreq, runlen;

	vm_page_lock_assert(p, MA_NOTOWNED);
	vm_page_assert_xbusied(p);
	VM_OBJECT_ASSERT_WLOCKED(object);

	count = 1;
	mreq = 0;

	for (tp = p; count < vm_pageout_page_count; count++) {
		tp = vm_page_next(tp);
		if (tp == NULL || vm_page_tryxbusy(tp) == 0)
			break;
		if (!vm_object_page_remove_write(tp, flags, allclean)) {
			vm_page_xunbusy(tp);
			break;
		}
	}

	for (p_first = p; count < vm_pageout_page_count; count++) {
		tp = vm_page_prev(p_first);
		if (tp == NULL || vm_page_tryxbusy(tp) == 0)
			break;
		if (!vm_object_page_remove_write(tp, flags, allclean)) {
			vm_page_xunbusy(tp);
			break;
		}
		p_first = tp;
		mreq++;
	}

	for (tp = p_first, i = 0; i < count; tp = TAILQ_NEXT(tp, listq), i++)
		ma[i] = tp;

	vm_pageout_flush(ma, count, pagerflags, mreq, &runlen, eio);
	return (runlen);
}