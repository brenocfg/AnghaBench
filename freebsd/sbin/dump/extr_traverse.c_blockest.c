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
typedef  union dinode {int dummy; } dinode ;
struct TYPE_2__ {long fs_bsize; } ;

/* Variables and functions */
 long DIP (union dinode*,int /*<<< orphan*/ ) ; 
 long SF_SNAPSHOT ; 
 long TP_BSIZE ; 
 long TP_NINDIR ; 
 long UFS_NDADDR ; 
 long dbtob (long) ; 
 int /*<<< orphan*/  di_blocks ; 
 int /*<<< orphan*/  di_flags ; 
 int /*<<< orphan*/  di_size ; 
 long howmany (long,long) ; 
 TYPE_1__* sblock ; 

__attribute__((used)) static long
blockest(union dinode *dp)
{
	long blkest, sizeest;

	/*
	 * dp->di_size is the size of the file in bytes.
	 * dp->di_blocks stores the number of sectors actually in the file.
	 * If there are more sectors than the size would indicate, this just
	 *	means that there are indirect blocks in the file or unused
	 *	sectors in the last file block; we can safely ignore these
	 *	(blkest = sizeest below).
	 * If the file is bigger than the number of sectors would indicate,
	 *	then the file has holes in it.	In this case we must use the
	 *	block count to estimate the number of data blocks used, but
	 *	we use the actual size for estimating the number of indirect
	 *	dump blocks (sizeest vs. blkest in the indirect block
	 *	calculation).
	 */
	if ((DIP(dp, di_flags) & SF_SNAPSHOT) != 0)
		return (1);
	blkest = howmany(dbtob(DIP(dp, di_blocks)), TP_BSIZE);
	sizeest = howmany(DIP(dp, di_size), TP_BSIZE);
	if (blkest > sizeest)
		blkest = sizeest;
	if (DIP(dp, di_size) > sblock->fs_bsize * UFS_NDADDR) {
		/* calculate the number of indirect blocks on the dump tape */
		blkest += howmany(sizeest -
		    UFS_NDADDR * sblock->fs_bsize / TP_BSIZE, TP_NINDIR);
	}
	return (blkest + 1);
}