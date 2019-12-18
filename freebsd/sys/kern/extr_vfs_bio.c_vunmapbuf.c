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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct buf {int b_npages; scalar_t__ b_data; int /*<<< orphan*/  b_pages; } ;

/* Variables and functions */
 scalar_t__ buf_mapped (struct buf*) ; 
 int /*<<< orphan*/  pmap_qremove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trunc_page (int /*<<< orphan*/ ) ; 
 scalar_t__ unmapped_buf ; 
 int /*<<< orphan*/  vm_page_unhold_pages (int /*<<< orphan*/ ,int) ; 

void
vunmapbuf(struct buf *bp)
{
	int npages;

	npages = bp->b_npages;
	if (buf_mapped(bp))
		pmap_qremove(trunc_page((vm_offset_t)bp->b_data), npages);
	vm_page_unhold_pages(bp->b_pages, npages);

	bp->b_data = unmapped_buf;
}