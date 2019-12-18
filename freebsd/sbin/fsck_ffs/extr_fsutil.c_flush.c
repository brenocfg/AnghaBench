#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  b_buf; int /*<<< orphan*/  b_cg; int /*<<< orphan*/  b_fs; } ;
struct bufarea {int b_errs; int b_size; int b_type; scalar_t__ b_bno; TYPE_1__ b_un; scalar_t__ b_dirty; } ;

/* Variables and functions */
#define  BT_CYLGRP 129 
#define  BT_SUPERBLK 128 
 int /*<<< orphan*/  blwrite (int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  cgput (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dev_bsize ; 
 int /*<<< orphan*/  disk ; 
 int fsmodified ; 
 scalar_t__ fswritefd ; 
 int /*<<< orphan*/  pfatal (char*,...) ; 
 struct bufarea sblk ; 
 int /*<<< orphan*/  sbput (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
flush(int fd, struct bufarea *bp)
{

	if (!bp->b_dirty)
		return;
	bp->b_dirty = 0;
	if (fswritefd < 0) {
		pfatal("WRITING IN READ_ONLY MODE.\n");
		return;
	}
	if (bp->b_errs != 0)
		pfatal("WRITING %sZERO'ED BLOCK %lld TO DISK\n",
		    (bp->b_errs == bp->b_size / dev_bsize) ? "" : "PARTIALLY ",
		    (long long)bp->b_bno);
	bp->b_errs = 0;
	/*
	 * Write using the appropriate function.
	 */
	switch (bp->b_type) {
	case BT_SUPERBLK:
		if (bp != &sblk)
			pfatal("BUFFER %p DOES NOT MATCH SBLK %p\n",
			    bp, &sblk);
		if (sbput(fd, bp->b_un.b_fs, 0) == 0)
			fsmodified = 1;
		break;
	case BT_CYLGRP:
		if (cgput(&disk, bp->b_un.b_cg) == 0)
			fsmodified = 1;
		break;
	default:
		blwrite(fd, bp->b_un.b_buf, bp->b_bno, bp->b_size);
		break;
	}
}