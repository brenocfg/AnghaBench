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
struct msdosfsmount {scalar_t__ pm_fsinfo; int pm_flags; int /*<<< orphan*/  pm_nxtfree; int /*<<< orphan*/  pm_freeclustercount; int /*<<< orphan*/  pm_BytesPerSec; int /*<<< orphan*/  pm_devvp; } ;
struct fsinfo {int /*<<< orphan*/  fsinxtfree; int /*<<< orphan*/  fsinfree; } ;
struct buf {scalar_t__ b_data; } ;

/* Variables and functions */
 int MNT_WAIT ; 
 int MSDOSFS_FSIMOD ; 
 int /*<<< orphan*/  MSDOSFS_LOCK_MP (struct msdosfsmount*) ; 
 int /*<<< orphan*/  MSDOSFS_UNLOCK_MP (struct msdosfsmount*) ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  bawrite (struct buf*) ; 
 int bread (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buf**) ; 
 int bwrite (struct buf*) ; 
 int /*<<< orphan*/  putulong (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msdosfs_fsiflush(struct msdosfsmount *pmp, int waitfor)
{
	struct fsinfo *fp;
	struct buf *bp;
	int error;

	MSDOSFS_LOCK_MP(pmp);
	if (pmp->pm_fsinfo == 0 || (pmp->pm_flags & MSDOSFS_FSIMOD) == 0) {
		error = 0;
		goto unlock;
	}
	error = bread(pmp->pm_devvp, pmp->pm_fsinfo, pmp->pm_BytesPerSec,
	    NOCRED, &bp);
	if (error != 0) {
		goto unlock;
	}
	fp = (struct fsinfo *)bp->b_data;
	putulong(fp->fsinfree, pmp->pm_freeclustercount);
	putulong(fp->fsinxtfree, pmp->pm_nxtfree);
	pmp->pm_flags &= ~MSDOSFS_FSIMOD;
	if (waitfor == MNT_WAIT)
		error = bwrite(bp);
	else
		bawrite(bp);
unlock:
	MSDOSFS_UNLOCK_MP(pmp);
	return (error);
}