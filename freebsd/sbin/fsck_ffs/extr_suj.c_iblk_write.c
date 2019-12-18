#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ino_blk {scalar_t__ ib_dirty; int /*<<< orphan*/  ib_blk; int /*<<< orphan*/  ib_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  fs_bsize; } ;

/* Variables and functions */
 int bwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  err_suj (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* fs ; 
 int /*<<< orphan*/  fsbtodb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iblk_write(struct ino_blk *iblk)
{

	if (iblk->ib_dirty == 0)
		return;
	if (bwrite(&disk, fsbtodb(fs, iblk->ib_blk), iblk->ib_buf,
	    fs->fs_bsize) == -1)
		err_suj("Failed to write inode block %jd\n", iblk->ib_blk);
}