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
typedef  scalar_t__ u_long ;
struct inode {int /*<<< orphan*/  i_fs; } ;
struct indir {int in_lbn; int in_off; } ;
typedef  int int64_t ;
typedef  int daddr_t ;

/* Variables and functions */
 int EFBIG ; 
 int NINDIR (int /*<<< orphan*/ ) ; 
 int UFS_NDADDR ; 
 int UFS_NIADDR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ffs (int) ; 

int
ufs_getlbns(struct inode *ip, daddr_t bn, struct indir *ap, int *nump)
{
	daddr_t metalbn, realbn;
	int64_t blockcnt;
	int lbc;
	int i, numlevels, off;
	u_long lognindir;

	lognindir = ffs(NINDIR(ip->i_fs)) - 1;
	if (nump)
		*nump = 0;
	numlevels = 0;
	realbn = bn;
	if ((long)bn < 0)
		bn = -(long)bn;

	assert (bn >= UFS_NDADDR);

	/* 
	 * Determine the number of levels of indirection.  After this loop
	 * is done, blockcnt indicates the number of data blocks possible
	 * at the given level of indirection, and UFS_NIADDR - i is the number
	 * of levels of indirection needed to locate the requested block.
	 */

	bn -= UFS_NDADDR;
	for (lbc = 0, i = UFS_NIADDR;; i--, bn -= blockcnt) {
		if (i == 0)
			return (EFBIG);

		lbc += lognindir;
		blockcnt = (int64_t)1 << lbc;

		if (bn < blockcnt)
			break;
	}

	/* Calculate the address of the first meta-block. */
	if (realbn >= 0)
		metalbn = -(realbn - bn + UFS_NIADDR - i);
	else
		metalbn = -(-realbn - bn + UFS_NIADDR - i);

	/* 
	 * At each iteration, off is the offset into the bap array which is
	 * an array of disk addresses at the current level of indirection.
	 * The logical block number and the offset in that block are stored
	 * into the argument array.
	 */
	ap->in_lbn = metalbn;
	ap->in_off = off = UFS_NIADDR - i;
	ap++;
	for (++numlevels; i <= UFS_NIADDR; i++) {
		/* If searching for a meta-data block, quit when found. */
		if (metalbn == realbn)
			break;

		lbc -= lognindir;
		blockcnt = (int64_t)1 << lbc;
		off = (bn >> lbc) & (NINDIR(ip->i_fs) - 1);

		++numlevels;
		ap->in_lbn = metalbn;
		ap->in_off = off;
		++ap;

		metalbn -= -1 + (off << lbc);
	}
	if (nump)
		*nump = numlevels;
	return (0);
}