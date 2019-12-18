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
struct buf {int b_npages; int /*<<< orphan*/ * b_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_page_sunbusy (int /*<<< orphan*/ ) ; 

void
vfs_busy_pages_release(struct buf *bp)
{
	int i;

	for (i = 0; i < bp->b_npages; i++)
		vm_page_sunbusy(bp->b_pages[i]);
}