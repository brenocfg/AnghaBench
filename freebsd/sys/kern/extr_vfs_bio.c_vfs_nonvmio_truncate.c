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
struct buf {int b_flags; int /*<<< orphan*/  b_kvabase; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int B_MALLOC ; 
 int /*<<< orphan*/  M_BIOBUF ; 
 int /*<<< orphan*/  bufmallocadjust (struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufspace_adjust (struct buf*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_hold_free_pages (struct buf*,int) ; 

__attribute__((used)) static void
vfs_nonvmio_truncate(struct buf *bp, int newbsize)
{

	if (bp->b_flags & B_MALLOC) {
		/*
		 * malloced buffers are not shrunk
		 */
		if (newbsize == 0) {
			bufmallocadjust(bp, 0);
			free(bp->b_data, M_BIOBUF);
			bp->b_data = bp->b_kvabase;
			bp->b_flags &= ~B_MALLOC;
		}
		return;
	}
	vm_hold_free_pages(bp, newbsize);
	bufspace_adjust(bp, newbsize);
}