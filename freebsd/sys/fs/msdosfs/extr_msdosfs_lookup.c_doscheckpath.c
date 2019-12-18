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
struct msdosfsmount {int pm_rootdirblk; int /*<<< orphan*/  pm_bpcluster; int /*<<< orphan*/  pm_devvp; } ;
struct direntry {int deAttributes; int /*<<< orphan*/  deHighClust; int /*<<< orphan*/  deStartCluster; int /*<<< orphan*/  deName; } ;
struct denode {int de_Attributes; int de_StartCluster; struct msdosfsmount* de_pmp; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int daddr_t ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int /*<<< orphan*/  DETOV (struct denode*) ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOTDIR ; 
 scalar_t__ FAT32 (struct msdosfsmount*) ; 
 int MSDOSFSROOT ; 
 int /*<<< orphan*/  NOCRED ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,char*,int) ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  cntobn (struct msdosfsmount*,int) ; 
 int deget (struct msdosfsmount*,int,int /*<<< orphan*/ ,struct denode**) ; 
 int getushort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ ) ; 

int
doscheckpath(struct denode *source, struct denode *target)
{
	daddr_t scn;
	struct msdosfsmount *pmp;
	struct direntry *ep;
	struct denode *dep;
	struct buf *bp = NULL;
	int error = 0;

	dep = target;
	if ((target->de_Attributes & ATTR_DIRECTORY) == 0 ||
	    (source->de_Attributes & ATTR_DIRECTORY) == 0) {
		error = ENOTDIR;
		goto out;
	}
	if (dep->de_StartCluster == source->de_StartCluster) {
		error = EEXIST;
		goto out;
	}
	if (dep->de_StartCluster == MSDOSFSROOT)
		goto out;
	pmp = dep->de_pmp;
#ifdef	DIAGNOSTIC
	if (pmp != source->de_pmp)
		panic("doscheckpath: source and target on different filesystems");
#endif
	if (FAT32(pmp) && dep->de_StartCluster == pmp->pm_rootdirblk)
		goto out;

	for (;;) {
		if ((dep->de_Attributes & ATTR_DIRECTORY) == 0) {
			error = ENOTDIR;
			break;
		}
		scn = dep->de_StartCluster;
		error = bread(pmp->pm_devvp, cntobn(pmp, scn),
			      pmp->pm_bpcluster, NOCRED, &bp);
		if (error)
			break;

		ep = (struct direntry *) bp->b_data + 1;
		if ((ep->deAttributes & ATTR_DIRECTORY) == 0 ||
		    bcmp(ep->deName, "..         ", 11) != 0) {
			error = ENOTDIR;
			break;
		}
		scn = getushort(ep->deStartCluster);
		if (FAT32(pmp))
			scn |= getushort(ep->deHighClust) << 16;

		if (scn == source->de_StartCluster) {
			error = EINVAL;
			break;
		}
		if (scn == MSDOSFSROOT)
			break;
		if (FAT32(pmp) && scn == pmp->pm_rootdirblk) {
			/*
			 * scn should be 0 in this case,
			 * but we silently ignore the error.
			 */
			break;
		}

		vput(DETOV(dep));
		brelse(bp);
		bp = NULL;
		/* NOTE: deget() clears dep on error */
		if ((error = deget(pmp, scn, 0, &dep)) != 0)
			break;
	}
out:;
	if (bp)
		brelse(bp);
#ifdef MSDOSFS_DEBUG
	if (error == ENOTDIR)
		printf("doscheckpath(): .. not a directory?\n");
#endif
	if (dep != NULL)
		vput(DETOV(dep));
	return (error);
}