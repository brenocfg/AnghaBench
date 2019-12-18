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
typedef  int vm_offset_t ;
struct buf {int b_npages; int /*<<< orphan*/ ** b_pages; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_CHECK_MAPPED (struct buf*) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  pmap_qremove (int,int) ; 
 int round_page (int) ; 
 int trunc_page (int) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vm_hold_free_pages(struct buf *bp, int newbsize)
{
	vm_offset_t from;
	vm_page_t p;
	int index, newnpages;

	BUF_CHECK_MAPPED(bp);

	from = round_page((vm_offset_t)bp->b_data + newbsize);
	newnpages = (from - trunc_page((vm_offset_t)bp->b_data)) >> PAGE_SHIFT;
	if (bp->b_npages > newnpages)
		pmap_qremove(from, bp->b_npages - newnpages);
	for (index = newnpages; index < bp->b_npages; index++) {
		p = bp->b_pages[index];
		bp->b_pages[index] = NULL;
		vm_page_unwire_noq(p);
		vm_page_free(p);
	}
	bp->b_npages = newnpages;
}