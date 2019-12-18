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
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  u_long ;
struct inodesc {scalar_t__ id_type; int (* id_func ) (struct inodesc*) ;int id_level; scalar_t__ id_number; scalar_t__ id_lbn; scalar_t__ id_blkno; int /*<<< orphan*/  id_numfrags; } ;
struct bufarea {int /*<<< orphan*/  b_flags; } ;
typedef  scalar_t__ off_t ;
struct TYPE_3__ {scalar_t__ fs_bsize; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  B_INUSE ; 
 scalar_t__ DATA ; 
 scalar_t__ DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IBLK (struct bufarea*,int) ; 
 int /*<<< orphan*/  IBLK_SET (struct bufarea*,int,int /*<<< orphan*/ ) ; 
 int KEEPON ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int NINDIR (TYPE_1__*) ; 
 int SKIP ; 
 int STOP ; 
 scalar_t__ chkrange (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  di_size ; 
 int dirscan (struct inodesc*) ; 
 int /*<<< orphan*/  dirty (struct bufarea*) ; 
 scalar_t__ dofix (struct inodesc*,char*) ; 
 int /*<<< orphan*/  flush (int /*<<< orphan*/ ,struct bufarea*) ; 
 int /*<<< orphan*/  fswritefd ; 
 struct bufarea* getdatablk (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  getpathname (char*,scalar_t__,scalar_t__) ; 
 union dinode* ginode (scalar_t__) ; 
 int howmany (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 
 int pass1check (struct inodesc*) ; 
 int /*<<< orphan*/  pfatal (char*,char*) ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*) ; 
 int reply (char*) ; 
 int rerun ; 
 TYPE_1__ sblock ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int stub1 (struct inodesc*) ; 
 int stub2 (struct inodesc*) ; 

__attribute__((used)) static int
iblock(struct inodesc *idesc, off_t isize, int type)
{
	struct bufarea *bp;
	int i, n, (*func)(struct inodesc *), nif;
	off_t sizepb;
	char buf[BUFSIZ];
	char pathbuf[MAXPATHLEN + 1];
	union dinode *dp;

	if (idesc->id_type != DATA) {
		func = idesc->id_func;
		if (((n = (*func)(idesc)) & KEEPON) == 0)
			return (n);
	} else
		func = dirscan;
	if (chkrange(idesc->id_blkno, idesc->id_numfrags))
		return (SKIP);
	bp = getdatablk(idesc->id_blkno, sblock.fs_bsize, type);
	idesc->id_level--;
	for (sizepb = sblock.fs_bsize, i = 0; i < idesc->id_level; i++)
		sizepb *= NINDIR(&sblock);
	if (howmany(isize, sizepb) > NINDIR(&sblock))
		nif = NINDIR(&sblock);
	else
		nif = howmany(isize, sizepb);
	if (idesc->id_func == pass1check && nif < NINDIR(&sblock)) {
		for (i = nif; i < NINDIR(&sblock); i++) {
			if (IBLK(bp, i) == 0)
				continue;
			(void)sprintf(buf, "PARTIALLY TRUNCATED INODE I=%lu",
			    (u_long)idesc->id_number);
			if (preen) {
				pfatal("%s", buf);
			} else if (dofix(idesc, buf)) {
				IBLK_SET(bp, i, 0);
				dirty(bp);
			}
		}
		flush(fswritefd, bp);
	}
	for (i = 0; i < nif; i++) {
		if (IBLK(bp, i)) {
			idesc->id_blkno = IBLK(bp, i);
			if (idesc->id_level == 0) {
				idesc->id_lbn++;
				n = (*func)(idesc);
			} else {
				n = iblock(idesc, isize, type);
				idesc->id_level++;
			}
			if (n & STOP) {
				bp->b_flags &= ~B_INUSE;
				return (n);
			}
		} else {
			idesc->id_lbn += sizepb / sblock.fs_bsize;
			if (idesc->id_type == DATA && isize > 0) {
				/* An empty block in a directory XXX */
				getpathname(pathbuf, idesc->id_number,
						idesc->id_number);
				pfatal("DIRECTORY %s: CONTAINS EMPTY BLOCKS",
					pathbuf);
				if (reply("ADJUST LENGTH") == 1) {
					dp = ginode(idesc->id_number);
					DIP_SET(dp, di_size,
					    DIP(dp, di_size) - isize);
					isize = 0;
					printf(
					    "YOU MUST RERUN FSCK AFTERWARDS\n");
					rerun = 1;
					inodirty(dp);
					bp->b_flags &= ~B_INUSE;
					return(STOP);
				}
			}
		}
		isize -= sizepb;
	}
	bp->b_flags &= ~B_INUSE;
	return (KEEPON);
}