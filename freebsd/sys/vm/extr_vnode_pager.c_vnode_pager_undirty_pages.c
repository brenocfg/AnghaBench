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
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int off_t ;
struct TYPE_5__ {scalar_t__ dirty; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_BSIZE ; 
 int OFF_TO_IDX (int) ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int VM_PAGER_AGAIN ; 
 int VM_PAGER_BAD ; 
 int VM_PAGER_OK ; 
 int round_page (int) ; 
 int roundup2 (int,int /*<<< orphan*/ ) ; 
 int trunc_page (int) ; 
 int /*<<< orphan*/  vm_page_clear_dirty (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vm_page_undirty (TYPE_1__*) ; 

void
vnode_pager_undirty_pages(vm_page_t *ma, int *rtvals, int written, off_t eof,
    int lpos)
{
	vm_object_t obj;
	int i, pos, pos_devb;

	if (written == 0 && eof >= lpos)
		return;
	obj = ma[0]->object;
	VM_OBJECT_WLOCK(obj);
	for (i = 0, pos = 0; pos < written; i++, pos += PAGE_SIZE) {
		if (pos < trunc_page(written)) {
			rtvals[i] = VM_PAGER_OK;
			vm_page_undirty(ma[i]);
		} else {
			/* Partially written page. */
			rtvals[i] = VM_PAGER_AGAIN;
			vm_page_clear_dirty(ma[i], 0, written & PAGE_MASK);
		}
	}
	if (eof >= lpos) /* avoid truncation */
		goto done;
	for (pos = eof, i = OFF_TO_IDX(trunc_page(pos)); pos < lpos; i++) {
		if (pos != trunc_page(pos)) {
			/*
			 * The page contains the last valid byte in
			 * the vnode, mark the rest of the page as
			 * clean, potentially making the whole page
			 * clean.
			 */
			pos_devb = roundup2(pos & PAGE_MASK, DEV_BSIZE);
			vm_page_clear_dirty(ma[i], pos_devb, PAGE_SIZE -
			    pos_devb);

			/*
			 * If the page was cleaned, report the pageout
			 * on it as successful.  msync() no longer
			 * needs to write out the page, endlessly
			 * creating write requests and dirty buffers.
			 */
			if (ma[i]->dirty == 0)
				rtvals[i] = VM_PAGER_OK;

			pos = round_page(pos);
		} else {
			/* vm_pageout_flush() clears dirty */
			rtvals[i] = VM_PAGER_BAD;
			pos += PAGE_SIZE;
		}
	}
done:
	VM_OBJECT_WUNLOCK(obj);
}