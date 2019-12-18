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
typedef  int uint8_t ;
typedef  scalar_t__ u_long ;
struct msdosfsmount {int pm_flags; scalar_t__ pm_fatblk; int pm_FATs; scalar_t__ pm_FATsecs; int /*<<< orphan*/  pm_devvp; } ;
struct buf {scalar_t__ b_data; int /*<<< orphan*/  b_bcount; } ;

/* Variables and functions */
 scalar_t__ FAT12 (struct msdosfsmount*) ; 
 scalar_t__ FAT16 (struct msdosfsmount*) ; 
 int MSDOSFS_FATMIRROR ; 
 scalar_t__ SYNCHRONOUS_WRITES (struct msdosfsmount*) ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int /*<<< orphan*/  bwrite (struct buf*) ; 
 struct buf* getblk (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,struct msdosfsmount*,struct buf*,scalar_t__) ; 

__attribute__((used)) static void
updatefats(struct msdosfsmount *pmp, struct buf *bp, u_long fatbn)
{
	struct buf *bpn;
	int cleanfat, i;

#ifdef MSDOSFS_DEBUG
	printf("updatefats(pmp %p, bp %p, fatbn %lu)\n", pmp, bp, fatbn);
#endif

	if (pmp->pm_flags & MSDOSFS_FATMIRROR) {
		/*
		 * Now copy the block(s) of the modified FAT to the other copies of
		 * the FAT and write them out.  This is faster than reading in the
		 * other FATs and then writing them back out.  This could tie up
		 * the FAT for quite a while. Preventing others from accessing it.
		 * To prevent us from going after the FAT quite so much we use
		 * delayed writes, unless they specified "synchronous" when the
		 * filesystem was mounted.  If synch is asked for then use
		 * bwrite()'s and really slow things down.
		 */
		if (fatbn != pmp->pm_fatblk || FAT12(pmp))
			cleanfat = 0;
		else if (FAT16(pmp))
			cleanfat = 16;
		else
			cleanfat = 32;
		for (i = 1; i < pmp->pm_FATs; i++) {
			fatbn += pmp->pm_FATsecs;
			/* getblk() never fails */
			bpn = getblk(pmp->pm_devvp, fatbn, bp->b_bcount,
			    0, 0, 0);
			memcpy(bpn->b_data, bp->b_data, bp->b_bcount);
			/* Force the clean bit on in the other copies. */
			if (cleanfat == 16)
				((uint8_t *)bpn->b_data)[3] |= 0x80;
			else if (cleanfat == 32)
				((uint8_t *)bpn->b_data)[7] |= 0x08;
			if (SYNCHRONOUS_WRITES(pmp))
				bwrite(bpn);
			else
				bdwrite(bpn);
		}
	}

	/*
	 * Write out the first (or current) FAT last.
	 */
	if (SYNCHRONOUS_WRITES(pmp))
		bwrite(bp);
	else
		bdwrite(bp);
}