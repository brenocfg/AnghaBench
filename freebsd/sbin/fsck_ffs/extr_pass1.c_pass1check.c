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
typedef  scalar_t__ ufs2_daddr_t ;
typedef  int /*<<< orphan*/  u_long ;
struct inodesc {scalar_t__ id_blkno; scalar_t__ id_type; scalar_t__ id_number; scalar_t__ id_lbn; int id_numfrags; scalar_t__ id_level; scalar_t__ id_lballoc; scalar_t__ id_entryno; } ;
struct dups {scalar_t__ dup; struct dups* next; } ;

/* Variables and functions */
 scalar_t__ BLK_NOCOPY ; 
 scalar_t__ BLK_SNAP ; 
 int /*<<< orphan*/  EEXIT ; 
 int KEEPON ; 
 scalar_t__ MAXBAD ; 
 scalar_t__ MAXDUP ; 
 scalar_t__ Malloc (int) ; 
 int SKIP ; 
 scalar_t__ SNAP ; 
 int STOP ; 
 int /*<<< orphan*/  badblk ; 
 int /*<<< orphan*/  blkerror (scalar_t__,char*,scalar_t__) ; 
 scalar_t__ blkstofrags (int /*<<< orphan*/ *,scalar_t__) ; 
 int chkrange (scalar_t__,int) ; 
 int /*<<< orphan*/  ckfini (int /*<<< orphan*/ ) ; 
 scalar_t__ cursnapshot ; 
 int /*<<< orphan*/  dupblk ; 
 struct dups* duplist ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 struct dups* muldup ; 
 int /*<<< orphan*/  n_blks ; 
 int /*<<< orphan*/  pfatal (char*) ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pwarn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ reply (char*) ; 
 int rerun ; 
 int /*<<< orphan*/  sblock ; 
 int /*<<< orphan*/  setbmap (scalar_t__) ; 
 int /*<<< orphan*/  testbmap (scalar_t__) ; 

int
pass1check(struct inodesc *idesc)
{
	int res = KEEPON;
	int anyout, nfrags;
	ufs2_daddr_t blkno = idesc->id_blkno;
	struct dups *dlp;
	struct dups *new;

	if (idesc->id_type == SNAP) {
		if (blkno == BLK_NOCOPY)
			return (KEEPON);
		if (idesc->id_number == cursnapshot) {
			if (blkno == blkstofrags(&sblock, idesc->id_lbn))
				return (KEEPON);
			if (blkno == BLK_SNAP) {
				blkno = blkstofrags(&sblock, idesc->id_lbn);
				idesc->id_entryno -= idesc->id_numfrags;
			}
		} else {
			if (blkno == BLK_SNAP)
				return (KEEPON);
		}
	}
	if ((anyout = chkrange(blkno, idesc->id_numfrags)) != 0) {
		blkerror(idesc->id_number, "BAD", blkno);
		if (badblk++ >= MAXBAD) {
			pwarn("EXCESSIVE BAD BLKS I=%lu",
			    (u_long)idesc->id_number);
			if (preen)
				printf(" (SKIPPING)\n");
			else if (reply("CONTINUE") == 0) {
				ckfini(0);
				exit(EEXIT);
			}
			rerun = 1;
			return (STOP);
		}
	}
	for (nfrags = idesc->id_numfrags; nfrags > 0; blkno++, nfrags--) {
		if (anyout && chkrange(blkno, 1)) {
			res = SKIP;
		} else if (!testbmap(blkno)) {
			n_blks++;
			setbmap(blkno);
		} else {
			blkerror(idesc->id_number, "DUP", blkno);
			if (dupblk++ >= MAXDUP) {
				pwarn("EXCESSIVE DUP BLKS I=%lu",
					(u_long)idesc->id_number);
				if (preen)
					printf(" (SKIPPING)\n");
				else if (reply("CONTINUE") == 0) {
					ckfini(0);
					exit(EEXIT);
				}
				rerun = 1;
				return (STOP);
			}
			new = (struct dups *)Malloc(sizeof(struct dups));
			if (new == NULL) {
				pfatal("DUP TABLE OVERFLOW.");
				if (reply("CONTINUE") == 0) {
					ckfini(0);
					exit(EEXIT);
				}
				rerun = 1;
				return (STOP);
			}
			new->dup = blkno;
			if (muldup == NULL) {
				duplist = muldup = new;
				new->next = NULL;
			} else {
				new->next = muldup->next;
				muldup->next = new;
			}
			for (dlp = duplist; dlp != muldup; dlp = dlp->next)
				if (dlp->dup == blkno)
					break;
			if (dlp == muldup && dlp->dup != blkno)
				muldup = new;
		}
		/*
		 * count the number of blocks found in id_entryno
		 */
		idesc->id_entryno++;
	}
	if (idesc->id_level == 0 && idesc->id_lballoc < idesc->id_lbn)
		idesc->id_lballoc = idesc->id_lbn;
	return (res);
}