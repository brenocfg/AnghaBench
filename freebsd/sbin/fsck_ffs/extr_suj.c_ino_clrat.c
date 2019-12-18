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
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ufs_lbn_t ;
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct direct {scalar_t__ d_ino; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int blkoff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dblk_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dblk_read (int /*<<< orphan*/ ,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  di_size ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  ino_blkatoff (union dinode*,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 union dinode* ino_read (scalar_t__) ; 
 int /*<<< orphan*/  lblkno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sblksize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ino_clrat(ino_t parent, off_t diroff, ino_t child)
{
	union dinode *dip;
	struct direct *dp;
	ufs2_daddr_t blk;
	uint8_t *block;
	ufs_lbn_t lbn;
	int blksize;
	int frags;
	int doff;

	if (debug)
		printf("Clearing inode %ju from parent %ju at offset %jd\n",
		    (uintmax_t)child, (uintmax_t)parent, diroff);

	lbn = lblkno(fs, diroff);
	doff = blkoff(fs, diroff);
	dip = ino_read(parent);
	blk = ino_blkatoff(dip, parent, lbn, &frags);
	blksize = sblksize(fs, DIP(dip, di_size), lbn);
	block = dblk_read(blk, blksize);
	dp = (struct direct *)&block[doff];
	if (dp->d_ino != child)
		errx(1, "Inode %ju does not exist in %ju at %jd",
		    (uintmax_t)child, (uintmax_t)parent, diroff);
	dp->d_ino = 0;
	dblk_dirty(blk);
	/*
	 * The actual .. reference count will already have been removed
	 * from the parent by the .. remref record.
	 */
}