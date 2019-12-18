#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ufs2_daddr_t ;
struct TYPE_7__ {int /*<<< orphan*/  d_error; } ;
struct TYPE_6__ {scalar_t__ fs_bsize; } ;

/* Variables and functions */
 int MAXBSIZE ; 
 int NINDIR (TYPE_1__*) ; 
 int /*<<< orphan*/  blkfree (scalar_t__,scalar_t__) ; 
 int bread (TYPE_3__*,int /*<<< orphan*/ ,void*,size_t) ; 
 TYPE_3__* diskp ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* fs ; 
 int /*<<< orphan*/  fsbtodb (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
freeindir(ufs2_daddr_t blk, int level)
{
	char sblks[MAXBSIZE];
	ufs2_daddr_t *blks;
	int i;

	if (bread(diskp, fsbtodb(fs, blk), (void *)&sblks, (size_t)fs->fs_bsize) == -1)
		err(1, "bread: %s", diskp->d_error);
	blks = (ufs2_daddr_t *)&sblks;
	for (i = 0; i < NINDIR(fs); i++) {
		if (blks[i] == 0)
			break;
		if (level == 0)
			blkfree(blks[i], fs->fs_bsize);
		else
			freeindir(blks[i], level - 1);
	}
	blkfree(blk, fs->fs_bsize);
}