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
typedef  int /*<<< orphan*/  ufs_lbn_t ;
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct direct {scalar_t__ d_reclen; scalar_t__ d_ino; scalar_t__ d_namlen; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int MAXBSIZE ; 
 int /*<<< orphan*/  SUJ_FILE ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  err_suj (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  fsbtodb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lfragtosize (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ sujino ; 

__attribute__((used)) static void
suj_find(ino_t ino, ufs_lbn_t lbn, ufs2_daddr_t blk, int frags)
{
	char block[MAXBSIZE];
	struct direct *dp;
	int bytes;
	int off;

	if (sujino)
		return;
	bytes = lfragtosize(fs, frags);
	if (bread(&disk, fsbtodb(fs, blk), block, bytes) <= 0)
		err_suj("Failed to read UFS_ROOTINO directory block %jd\n",
		    blk);
	for (off = 0; off < bytes; off += dp->d_reclen) {
		dp = (struct direct *)&block[off];
		if (dp->d_reclen == 0)
			break;
		if (dp->d_ino == 0)
			continue;
		if (dp->d_namlen != strlen(SUJ_FILE))
			continue;
		if (bcmp(dp->d_name, SUJ_FILE, dp->d_namlen) != 0)
			continue;
		sujino = dp->d_ino;
		return;
	}
}