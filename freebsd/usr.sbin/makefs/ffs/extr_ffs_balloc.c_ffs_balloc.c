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
struct inode {TYPE_1__* i_fs; } ;
struct buf {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {scalar_t__ fs_magic; } ;

/* Variables and functions */
 scalar_t__ FS_UFS2_MAGIC ; 
 int ffs_balloc_ufs1 (struct inode*,int /*<<< orphan*/ ,int,struct buf**) ; 
 int ffs_balloc_ufs2 (struct inode*,int /*<<< orphan*/ ,int,struct buf**) ; 

int
ffs_balloc(struct inode *ip, off_t offset, int bufsize, struct buf **bpp)
{
	if (ip->i_fs->fs_magic == FS_UFS2_MAGIC)
		return ffs_balloc_ufs2(ip, offset, bufsize, bpp);
	else
		return ffs_balloc_ufs1(ip, offset, bufsize, bpp);
}