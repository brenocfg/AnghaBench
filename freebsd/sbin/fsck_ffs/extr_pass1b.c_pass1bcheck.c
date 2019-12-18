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
struct inodesc {scalar_t__ id_blkno; int id_numfrags; int /*<<< orphan*/  id_number; } ;
struct dups {scalar_t__ dup; struct dups* next; } ;

/* Variables and functions */
 int KEEPON ; 
 int SKIP ; 
 int STOP ; 
 int /*<<< orphan*/  blkerror (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ chkrange (scalar_t__,int) ; 
 struct dups* duphead ; 
 struct dups* muldup ; 
 int rerun ; 

__attribute__((used)) static int
pass1bcheck(struct inodesc *idesc)
{
	struct dups *dlp;
	int nfrags, res = KEEPON;
	ufs2_daddr_t blkno = idesc->id_blkno;

	for (nfrags = idesc->id_numfrags; nfrags > 0; blkno++, nfrags--) {
		if (chkrange(blkno, 1))
			res = SKIP;
		for (dlp = duphead; dlp; dlp = dlp->next) {
			if (dlp->dup == blkno) {
				blkerror(idesc->id_number, "DUP", blkno);
				dlp->dup = duphead->dup;
				duphead->dup = blkno;
				duphead = duphead->next;
			}
			if (dlp == muldup)
				break;
		}
		if (muldup == NULL || duphead == muldup->next) {
			rerun = 1;
			return (STOP);
		}
	}
	return (res);
}