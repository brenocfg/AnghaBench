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
typedef  int u_long ;
struct msdosfsmount {int pm_maxcluster; int pm_fatmask; int pm_fmod; int /*<<< orphan*/  pm_devvp; } ;
struct buf {int b_data; } ;

/* Variables and functions */
 int CLUST_FIRST ; 
 int CLUST_RSRVD ; 
 int EINVAL ; 
 int FAT12 (struct msdosfsmount*) ; 
#define  FAT12_MASK 130 
#define  FAT16_MASK 129 
 scalar_t__ FAT32 (struct msdosfsmount*) ; 
#define  FAT32_MASK 128 
 int FATOFS (struct msdosfsmount*,int) ; 
 int FAT_GET ; 
 int FAT_SET ; 
 int /*<<< orphan*/  NOCRED ; 
 int bread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  fatblock (struct msdosfsmount*,int,int*,int*,int*) ; 
 int getulong (int) ; 
 int getushort (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putulong (int,int) ; 
 int /*<<< orphan*/  putushort (int,int) ; 
 int /*<<< orphan*/  updatefats (struct msdosfsmount*,struct buf*,int) ; 

int
fatentry(int function, struct msdosfsmount *pmp, u_long cn, u_long *oldcontents,
    u_long newcontents)
{
	int error;
	u_long readcn;
	u_long bn, bo, bsize, byteoffset;
	struct buf *bp;

#ifdef	MSDOSFS_DEBUG
	printf("fatentry(func %d, pmp %p, clust %lu, oldcon %p, newcon %lx)\n",
	    function, pmp, cn, oldcontents, newcontents);
#endif

#ifdef DIAGNOSTIC
	/*
	 * Be sure they asked us to do something.
	 */
	if ((function & (FAT_SET | FAT_GET)) == 0) {
#ifdef MSDOSFS_DEBUG
		printf("fatentry(): function code doesn't specify get or set\n");
#endif
		return (EINVAL);
	}

	/*
	 * If they asked us to return a cluster number but didn't tell us
	 * where to put it, give them an error.
	 */
	if ((function & FAT_GET) && oldcontents == NULL) {
#ifdef MSDOSFS_DEBUG
		printf("fatentry(): get function with no place to put result\n");
#endif
		return (EINVAL);
	}
#endif

	/*
	 * Be sure the requested cluster is in the filesystem.
	 */
	if (cn < CLUST_FIRST || cn > pmp->pm_maxcluster)
		return (EINVAL);

	byteoffset = FATOFS(pmp, cn);
	fatblock(pmp, byteoffset, &bn, &bsize, &bo);
	error = bread(pmp->pm_devvp, bn, bsize, NOCRED, &bp);
	if (error) {
		return (error);
	}

	if (function & FAT_GET) {
		if (FAT32(pmp))
			readcn = getulong(bp->b_data + bo);
		else
			readcn = getushort(bp->b_data + bo);
		if (FAT12(pmp) & (cn & 1))
			readcn >>= 4;
		readcn &= pmp->pm_fatmask;
		/* map reserved FAT entries to same values for all FATs */
		if ((readcn | ~pmp->pm_fatmask) >= CLUST_RSRVD)
			readcn |= ~pmp->pm_fatmask;
		*oldcontents = readcn;
	}
	if (function & FAT_SET) {
		switch (pmp->pm_fatmask) {
		case FAT12_MASK:
			readcn = getushort(bp->b_data + bo);
			if (cn & 1) {
				readcn &= 0x000f;
				readcn |= newcontents << 4;
			} else {
				readcn &= 0xf000;
				readcn |= newcontents & 0xfff;
			}
			putushort(bp->b_data + bo, readcn);
			break;
		case FAT16_MASK:
			putushort(bp->b_data + bo, newcontents);
			break;
		case FAT32_MASK:
			/*
			 * According to spec we have to retain the
			 * high order bits of the FAT entry.
			 */
			readcn = getulong(bp->b_data + bo);
			readcn &= ~FAT32_MASK;
			readcn |= newcontents & FAT32_MASK;
			putulong(bp->b_data + bo, readcn);
			break;
		}
		updatefats(pmp, bp, bn);
		bp = NULL;
		pmp->pm_fmod = 1;
	}
	if (bp)
		brelse(bp);
	return (0);
}