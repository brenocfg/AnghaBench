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
struct m_ext2fs {TYPE_1__* e2fs; } ;
struct inode {scalar_t__ i_next_alloc_block; scalar_t__ i_next_alloc_goal; int i_block_group; int /*<<< orphan*/  i_ump; struct m_ext2fs* i_e2fs; } ;
typedef  scalar_t__ e4fs_daddr_t ;
typedef  scalar_t__ e2fs_lbn_t ;
typedef  scalar_t__ e2fs_daddr_t ;
struct TYPE_2__ {scalar_t__ e2fs_first_dblock; } ;

/* Variables and functions */
 int EXT2_BLOCKS_PER_GROUP (struct m_ext2fs*) ; 
 int /*<<< orphan*/  EXT2_MTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

e4fs_daddr_t
ext2_blkpref(struct inode *ip, e2fs_lbn_t lbn, int indx, e2fs_daddr_t *bap,
    e2fs_daddr_t blocknr)
{
	struct m_ext2fs *fs;
	int tmp;

	fs = ip->i_e2fs;

	mtx_assert(EXT2_MTX(ip->i_ump), MA_OWNED);

	/*
	 * If the next block is actually what we thought it is, then set the
	 * goal to what we thought it should be.
	 */
	if (ip->i_next_alloc_block == lbn && ip->i_next_alloc_goal != 0)
		return ip->i_next_alloc_goal;

	/*
	 * Now check whether we were provided with an array that basically
	 * tells us previous blocks to which we want to stay close.
	 */
	if (bap)
		for (tmp = indx - 1; tmp >= 0; tmp--)
			if (bap[tmp])
				return bap[tmp];

	/*
	 * Else lets fall back to the blocknr or, if there is none, follow
	 * the rule that a block should be allocated near its inode.
	 */
	return (blocknr ? blocknr :
	    (e2fs_daddr_t)(ip->i_block_group *
	    EXT2_BLOCKS_PER_GROUP(fs)) + fs->e2fs->e2fs_first_dblock);
}