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
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct indir {long in_lbn; int in_off; } ;
struct ext2mount {int dummy; } ;
typedef  long int64_t ;
typedef  long e2fs_lbn_t ;
typedef  long daddr_t ;

/* Variables and functions */
 int EFBIG ; 
 long EXT2_NDADDR ; 
 long EXT2_NIADDR ; 
 long MNINDIR (struct ext2mount*) ; 
 struct ext2mount* VFSTOEXT2 (int /*<<< orphan*/ ) ; 

int
ext2_getlbns(struct vnode *vp, daddr_t bn, struct indir *ap, int *nump)
{
	long blockcnt;
	e2fs_lbn_t metalbn, realbn;
	struct ext2mount *ump;
	int i, numlevels, off;
	int64_t qblockcnt;

	ump = VFSTOEXT2(vp->v_mount);
	if (nump)
		*nump = 0;
	numlevels = 0;
	realbn = bn;
	if ((long)bn < 0)
		bn = -(long)bn;

	/* The first EXT2_NDADDR blocks are direct blocks. */
	if (bn < EXT2_NDADDR)
		return (0);

	/*
	 * Determine the number of levels of indirection.  After this loop
	 * is done, blockcnt indicates the number of data blocks possible
	 * at the previous level of indirection, and EXT2_NIADDR - i is the
	 * number of levels of indirection needed to locate the requested block.
	 */
	for (blockcnt = 1, i = EXT2_NIADDR, bn -= EXT2_NDADDR; ;
	    i--, bn -= blockcnt) {
		if (i == 0)
			return (EFBIG);
		/*
		 * Use int64_t's here to avoid overflow for triple indirect
		 * blocks when longs have 32 bits and the block size is more
		 * than 4K.
		 */
		qblockcnt = (int64_t)blockcnt * MNINDIR(ump);
		if (bn < qblockcnt)
			break;
		blockcnt = qblockcnt;
	}

	/* Calculate the address of the first meta-block. */
	if (realbn >= 0)
		metalbn = -(realbn - bn + EXT2_NIADDR - i);
	else
		metalbn = -(-realbn - bn + EXT2_NIADDR - i);

	/*
	 * At each iteration, off is the offset into the bap array which is
	 * an array of disk addresses at the current level of indirection.
	 * The logical block number and the offset in that block are stored
	 * into the argument array.
	 */
	ap->in_lbn = metalbn;
	ap->in_off = off = EXT2_NIADDR - i;
	ap++;
	for (++numlevels; i <= EXT2_NIADDR; i++) {
		/* If searching for a meta-data block, quit when found. */
		if (metalbn == realbn)
			break;

		off = (bn / blockcnt) % MNINDIR(ump);

		++numlevels;
		ap->in_lbn = metalbn;
		ap->in_off = off;
		++ap;

		metalbn -= -1 + off * blockcnt;
		blockcnt /= MNINDIR(ump);
	}
	if (nump)
		*nump = numlevels;
	return (0);
}