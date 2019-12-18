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
typedef  int ufs_lbn_t ;
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_3__ {scalar_t__ fs_magic; int /*<<< orphan*/  fs_bsize; } ;

/* Variables and functions */
 scalar_t__ FS_UFS1_MAGIC ; 
 int NINDIR (TYPE_1__*) ; 
 scalar_t__ dblk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_suj (char*,int,...) ; 
 TYPE_1__* fs ; 
 int lbn_level (int) ; 

__attribute__((used)) static ufs2_daddr_t
indir_blkatoff(ufs2_daddr_t blk, ino_t ino, ufs_lbn_t cur, ufs_lbn_t lbn)
{
	ufs2_daddr_t *bap2;
	ufs2_daddr_t *bap1;
	ufs_lbn_t lbnadd;
	ufs_lbn_t base;
	int level;
	int i;

	if (blk == 0)
		return (0);
	level = lbn_level(cur);
	if (level == -1)
		err_suj("Invalid indir lbn %jd\n", lbn);
	if (level == 0 && lbn < 0)
		err_suj("Invalid lbn %jd\n", lbn);
	bap2 = (void *)dblk_read(blk, fs->fs_bsize);
	bap1 = (void *)bap2;
	lbnadd = 1;
	base = -(cur + level);
	for (i = level; i > 0; i--)
		lbnadd *= NINDIR(fs);
	if (lbn > 0)
		i = (lbn - base) / lbnadd;
	else
		i = (-lbn - base) / lbnadd;
	if (i < 0 || i >= NINDIR(fs))
		err_suj("Invalid indirect index %d produced by lbn %jd\n",
		    i, lbn);
	if (level == 0)
		cur = base + (i * lbnadd);
	else
		cur = -(base + (i * lbnadd)) - (level - 1);
	if (fs->fs_magic == FS_UFS1_MAGIC)
		blk = bap1[i];
	else
		blk = bap2[i];
	if (cur == lbn)
		return (blk);
	if (level == 0)
		err_suj("Invalid lbn %jd at level 0\n", lbn);
	return indir_blkatoff(blk, ino, cur, lbn);
}