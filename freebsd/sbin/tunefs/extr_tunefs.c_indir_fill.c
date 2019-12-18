#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ufs2_daddr_t ;
typedef  int /*<<< orphan*/  ufs1_daddr_t ;
typedef  int /*<<< orphan*/  indirbuf ;
struct TYPE_4__ {scalar_t__ fs_magic; int /*<<< orphan*/  fs_bsize; } ;

/* Variables and functions */
 scalar_t__ FS_UFS1_MAGIC ; 
 int MAXBSIZE ; 
 int NINDIR (TYPE_1__*) ; 
 scalar_t__ bwrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  disk ; 
 int /*<<< orphan*/  fsbtodb (TYPE_1__*,scalar_t__) ; 
 scalar_t__ journal_balloc () ; 
 TYPE_1__ sblock ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
indir_fill(ufs2_daddr_t blk, int level, int *resid)
{
	char indirbuf[MAXBSIZE];
	ufs1_daddr_t *bap1;
	ufs2_daddr_t *bap2;
	ufs2_daddr_t nblk;
	int ncnt;
	int cnt;
	int i;

	bzero(indirbuf, sizeof(indirbuf));
	bap1 = (ufs1_daddr_t *)indirbuf;
	bap2 = (void *)bap1;
	cnt = 0;
	for (i = 0; i < NINDIR(&sblock) && *resid != 0; i++) {
		nblk = journal_balloc();
		if (nblk <= 0)
			return (-1);
		cnt++;
		if (sblock.fs_magic == FS_UFS1_MAGIC)
			*bap1++ = nblk;
		else
			*bap2++ = nblk;
		if (level != 0) {
			ncnt = indir_fill(nblk, level - 1, resid);
			if (ncnt <= 0)
				return (-1);
			cnt += ncnt;
		} else 
			(*resid)--;
	}
	if (bwrite(&disk, fsbtodb(&sblock, blk), indirbuf,
	    sblock.fs_bsize) <= 0) {
		warn("Failed to write indirect");
		return (-1);
	}
	return (cnt);
}