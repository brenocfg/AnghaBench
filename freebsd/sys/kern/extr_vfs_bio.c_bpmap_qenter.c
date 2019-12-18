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
typedef  int vm_offset_t ;
struct buf {int b_offset; void* b_data; int /*<<< orphan*/  b_npages; int /*<<< orphan*/  b_pages; } ;
typedef  void* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_CHECK_MAPPED (struct buf*) ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  pmap_qenter (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ trunc_page (int) ; 

__attribute__((used)) static void
bpmap_qenter(struct buf *bp)
{

	BUF_CHECK_MAPPED(bp);

	/*
	 * bp->b_data is relative to bp->b_offset, but
	 * bp->b_offset may be offset into the first page.
	 */
	bp->b_data = (caddr_t)trunc_page((vm_offset_t)bp->b_data);
	pmap_qenter((vm_offset_t)bp->b_data, bp->b_pages, bp->b_npages);
	bp->b_data = (caddr_t)((vm_offset_t)bp->b_data |
	    (vm_offset_t)(bp->b_offset & PAGE_MASK));
}