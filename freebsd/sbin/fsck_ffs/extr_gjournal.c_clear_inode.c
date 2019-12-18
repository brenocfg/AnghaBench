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
typedef  scalar_t__ ufs2_daddr_t ;
struct ufs2_dinode {scalar_t__ di_extsize; int di_blocks; scalar_t__* di_extb; scalar_t__* di_ib; scalar_t__* di_db; } ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {scalar_t__ fs_magic; } ;

/* Variables and functions */
 scalar_t__ FS_UFS2_MAGIC ; 
 int SINGLE ; 
 int TRIPLE ; 
 int UFS_NDADDR ; 
 int UFS_NXADDR ; 
 int /*<<< orphan*/  blkfree (scalar_t__,long) ; 
 int btodb (int /*<<< orphan*/ ) ; 
 long dblksize (TYPE_1__*,struct ufs2_dinode*,int) ; 
 int /*<<< orphan*/  fragroundup (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  freeindir (scalar_t__,int) ; 
 TYPE_1__* fs ; 
 long sblksize (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static void
clear_inode(struct ufs2_dinode *dino)
{
	ufs2_daddr_t bn;
	int extblocks, i, level;
	off_t osize;
	long bsize;

	extblocks = 0;
	if (fs->fs_magic == FS_UFS2_MAGIC && dino->di_extsize > 0)
		extblocks = btodb(fragroundup(fs, dino->di_extsize));
	/* deallocate external attributes blocks */
	if (extblocks > 0) {
		osize = dino->di_extsize;
		dino->di_blocks -= extblocks;
		dino->di_extsize = 0;
		for (i = 0; i < UFS_NXADDR; i++) {
			if (dino->di_extb[i] == 0)
				continue;
			blkfree(dino->di_extb[i], sblksize(fs, osize, i));
		}
	}
#define	SINGLE	0	/* index of single indirect block */
#define	DOUBLE	1	/* index of double indirect block */
#define	TRIPLE	2	/* index of triple indirect block */
	/* deallocate indirect blocks */
	for (level = SINGLE; level <= TRIPLE; level++) {
		if (dino->di_ib[level] == 0)
			break;
		freeindir(dino->di_ib[level], level);
	}
	/* deallocate direct blocks and fragments */
	for (i = 0; i < UFS_NDADDR; i++) {
		bn = dino->di_db[i];
		if (bn == 0)
			continue;
		bsize = dblksize(fs, dino, i);
		blkfree(bn, bsize);
	}
}