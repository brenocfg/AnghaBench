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
typedef  scalar_t__ uint64_t ;
struct suj_ino {scalar_t__ si_ino; } ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 scalar_t__ DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ UFS_NDADDR ; 
 int VISIT_EXT ; 
 int VISIT_INDIR ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  di_blocks ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_size ; 
 int /*<<< orphan*/  fs ; 
 scalar_t__ fsbtodb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ino_dirty (scalar_t__) ; 
 union dinode* ino_read (scalar_t__) ; 
 int /*<<< orphan*/  ino_trunc (scalar_t__,scalar_t__) ; 
 scalar_t__ ino_visit (union dinode*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lblktosize (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  null_visit ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ visitlbn ; 

__attribute__((used)) static void
ino_adjblks(struct suj_ino *sino)
{
	union dinode *ip;
	uint64_t blocks;
	uint64_t frags;
	off_t isize;
	off_t size;
	ino_t ino;

	ino = sino->si_ino;
	ip = ino_read(ino);
	/* No need to adjust zero'd inodes. */
	if (DIP(ip, di_mode) == 0)
		return;
	/*
	 * Visit all blocks and count them as well as recording the last
	 * valid lbn in the file.  If the file size doesn't agree with the
	 * last lbn we need to truncate to fix it.  Otherwise just adjust
	 * the blocks count.
	 */
	visitlbn = 0;
	frags = ino_visit(ip, ino, null_visit, VISIT_INDIR | VISIT_EXT);
	blocks = fsbtodb(fs, frags);
	/*
	 * We assume the size and direct block list is kept coherent by
	 * softdep.  For files that have extended into indirects we truncate
	 * to the size in the inode or the maximum size permitted by
	 * populated indirects.
	 */
	if (visitlbn >= UFS_NDADDR) {
		isize = DIP(ip, di_size);
		size = lblktosize(fs, visitlbn + 1);
		if (isize > size)
			isize = size;
		/* Always truncate to free any unpopulated indirects. */
		ino_trunc(sino->si_ino, isize);
		return;
	}
	if (blocks == DIP(ip, di_blocks))
		return;
	if (debug)
		printf("ino %ju adjusting block count from %jd to %jd\n",
		    (uintmax_t)ino, DIP(ip, di_blocks), blocks);
	DIP_SET(ip, di_blocks, blocks);
	ino_dirty(ino);
}