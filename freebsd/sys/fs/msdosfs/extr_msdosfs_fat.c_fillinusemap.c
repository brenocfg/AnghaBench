#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_long ;
struct TYPE_2__ {int bpbMedia; } ;
struct msdosfsmount {size_t pm_maxcluster; unsigned int* pm_inusemap; size_t pm_fatblocksize; size_t pm_fatmask; TYPE_1__ pm_bpb; int /*<<< orphan*/  pm_devvp; scalar_t__ pm_freeclustercount; } ;
struct buf {scalar_t__ b_data; } ;

/* Variables and functions */
 size_t CLUST_FREE ; 
 int EINVAL ; 
 scalar_t__ FAT12 (struct msdosfsmount*) ; 
 scalar_t__ FAT32 (struct msdosfsmount*) ; 
 size_t FATOFS (struct msdosfsmount*,size_t) ; 
 unsigned int FULL_RUN ; 
 int /*<<< orphan*/  MSDOSFS_ASSERT_MP_LOCKED (struct msdosfsmount*) ; 
 int /*<<< orphan*/  NOCRED ; 
 size_t N_INUSEBITS ; 
 int bread (int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  fatblock (struct msdosfsmount*,size_t,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 size_t getulong (scalar_t__) ; 
 size_t getushort (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  usemap_free (struct msdosfsmount*,size_t) ; 

int
fillinusemap(struct msdosfsmount *pmp)
{
	struct buf *bp;
	u_long bn, bo, bsize, byteoffset, cn, readcn;
	int error;

	MSDOSFS_ASSERT_MP_LOCKED(pmp);
	bp = NULL;

	/*
	 * Mark all clusters in use, we mark the free ones in the FAT scan
	 * loop further down.
	 */
	for (cn = 0; cn < (pmp->pm_maxcluster + N_INUSEBITS) / N_INUSEBITS; cn++)
		pmp->pm_inusemap[cn] = FULL_RUN;

	/*
	 * Figure how many free clusters are in the filesystem by ripping
	 * through the FAT counting the number of entries whose content is
	 * zero.  These represent free clusters.
	 */
	pmp->pm_freeclustercount = 0;
	for (cn = 0; cn <= pmp->pm_maxcluster; cn++) {
		byteoffset = FATOFS(pmp, cn);
		bo = byteoffset % pmp->pm_fatblocksize;
		if (bo == 0) {
			/* Read new FAT block */
			if (bp != NULL)
				brelse(bp);
			fatblock(pmp, byteoffset, &bn, &bsize, NULL);
			error = bread(pmp->pm_devvp, bn, bsize, NOCRED, &bp);
			if (error != 0)
				return (error);
		}
		if (FAT32(pmp))
			readcn = getulong(bp->b_data + bo);
		else
			readcn = getushort(bp->b_data + bo);
		if (FAT12(pmp) && (cn & 1))
			readcn >>= 4;
		readcn &= pmp->pm_fatmask;

		/*
		 * Check if the FAT ID matches the BPB's media descriptor and
		 * all other bits are set to 1.
		 */
		if (cn == 0 && readcn != ((pmp->pm_fatmask & 0xffffff00) |
		    pmp->pm_bpb.bpbMedia)) {
#ifdef MSDOSFS_DEBUG
			printf("mountmsdosfs(): Media descriptor in BPB"
			    "does not match FAT ID\n");
#endif
			brelse(bp);
			return (EINVAL);
		} else if (readcn == CLUST_FREE)
			usemap_free(pmp, cn);
	}
	if (bp != NULL)
		brelse(bp);

	for (cn = pmp->pm_maxcluster + 1; cn < (pmp->pm_maxcluster +
	    N_INUSEBITS) / N_INUSEBITS; cn++)
		pmp->pm_inusemap[cn / N_INUSEBITS] |= 1U << (cn % N_INUSEBITS);

	return (0);
}