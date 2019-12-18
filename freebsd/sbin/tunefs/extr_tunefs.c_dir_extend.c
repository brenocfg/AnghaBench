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
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_3__ {int /*<<< orphan*/  fs_bsize; int /*<<< orphan*/  fs_fsize; } ;

/* Variables and functions */
 int MAXBSIZE ; 
 scalar_t__ bread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ bwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_clear_block (char*,int /*<<< orphan*/ ) ; 
 int dir_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  fsbtodb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ sblock ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
dir_extend(ufs2_daddr_t blk, ufs2_daddr_t nblk, off_t size, ino_t ino)
{
	char block[MAXBSIZE];

	if (bread(&disk, fsbtodb(&sblock, blk), block,
	    roundup(size, sblock.fs_fsize)) <= 0) {
		warn("Failed to read dir block");
		return (-1);
	}
	dir_clear_block(block, size);
	if (bwrite(&disk, fsbtodb(&sblock, nblk), block, sblock.fs_bsize)
	    <= 0) {
		warn("Failed to write dir block");
		return (-1);
	}

	return (dir_insert(nblk, size, ino));
}