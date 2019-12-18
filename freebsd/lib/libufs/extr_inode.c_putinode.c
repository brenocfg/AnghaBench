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
struct fs {int /*<<< orphan*/  fs_bsize; } ;
struct TYPE_2__ {int /*<<< orphan*/  dp2; } ;
struct uufsd {int d_ufs; struct fs d_fs; int /*<<< orphan*/ * d_inoblock; int /*<<< orphan*/  d_inomin; TYPE_1__ d_dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct uufsd*,char*) ; 
 scalar_t__ bwrite (struct uufsd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs_update_dinode_ckhash (struct fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsbtodb (struct fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_to_fsba (struct fs*,int /*<<< orphan*/ ) ; 

int
putinode(struct uufsd *disk)
{
	struct fs *fs;

	fs = &disk->d_fs;
	if (disk->d_inoblock == NULL) {
		ERROR(disk, "No inode block allocated");
		return (-1);
	}
	if (disk->d_ufs == 2)
		ffs_update_dinode_ckhash(fs, disk->d_dp.dp2);
	if (bwrite(disk, fsbtodb(fs, ino_to_fsba(&disk->d_fs, disk->d_inomin)),
	    disk->d_inoblock, disk->d_fs.fs_bsize) <= 0)
		return (-1);
	return (0);
}