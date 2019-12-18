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
struct direct {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_namlen; int /*<<< orphan*/  d_type; scalar_t__ d_reclen; int /*<<< orphan*/  d_ino; } ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_3__ {scalar_t__ fs_bsize; } ;

/* Variables and functions */
 scalar_t__ DIRBLKSIZ ; 
 int /*<<< orphan*/  DT_REG ; 
 int MAXBSIZE ; 
 int /*<<< orphan*/  SUJ_FILE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ bwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  bzero (char*,scalar_t__) ; 
 int /*<<< orphan*/  dir_clear_block (char*,scalar_t__) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  fsbtodb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ sblock ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
dir_insert(ufs2_daddr_t blk, off_t off, ino_t ino)
{
	struct direct *dp;
	char block[MAXBSIZE];

	if (bread(&disk, fsbtodb(&sblock, blk), block, sblock.fs_bsize) <= 0) {
		warn("Failed to read dir block");
		return (-1);
	}
	bzero(&block[off], sblock.fs_bsize - off);
	dp = (struct direct *)&block[off];
	dp->d_ino = ino;
	dp->d_reclen = DIRBLKSIZ;
	dp->d_type = DT_REG;
	dp->d_namlen = strlen(SUJ_FILE);
	bcopy(SUJ_FILE, &dp->d_name, strlen(SUJ_FILE));
	dir_clear_block(block, off + DIRBLKSIZ);
	if (bwrite(&disk, fsbtodb(&sblock, blk), block, sblock.fs_bsize) <= 0) {
		warn("Failed to write dir block");
		return (-1);
	}
	return (0);
}