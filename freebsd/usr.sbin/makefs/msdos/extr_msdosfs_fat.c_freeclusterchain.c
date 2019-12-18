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
typedef  scalar_t__ u_long ;
struct msdosfsmount {scalar_t__ pm_maxcluster; int pm_fatmask; int /*<<< orphan*/  pm_devvp; } ;
struct buf {scalar_t__ b_data; } ;

/* Variables and functions */
 scalar_t__ CLUST_FIRST ; 
 scalar_t__ CLUST_RSRVD ; 
#define  FAT12_MASK 130 
#define  FAT16_MASK 129 
#define  FAT32_MASK 128 
 scalar_t__ FATOFS (struct msdosfsmount*,scalar_t__) ; 
 int MSDOSFSFREE ; 
 int /*<<< orphan*/  NOCRED ; 
 int bread (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  fatblock (struct msdosfsmount*,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ getulong (scalar_t__) ; 
 scalar_t__ getushort (scalar_t__) ; 
 int /*<<< orphan*/  putulong (scalar_t__,int) ; 
 int /*<<< orphan*/  putushort (scalar_t__,int) ; 
 int /*<<< orphan*/  updatefats (struct msdosfsmount*,struct buf*,scalar_t__) ; 
 int /*<<< orphan*/  usemap_free (struct msdosfsmount*,scalar_t__) ; 

int
freeclusterchain(struct msdosfsmount *pmp, u_long cluster)
{
	int error;
	struct buf *bp = NULL;
	u_long bn, bo, bsize, byteoffset;
	u_long readcn, lbn = -1;

	while (cluster >= CLUST_FIRST && cluster <= pmp->pm_maxcluster) {
		byteoffset = FATOFS(pmp, cluster);
		fatblock(pmp, byteoffset, &bn, &bsize, &bo);
		if (lbn != bn) {
			if (bp)
				updatefats(pmp, bp, lbn);
			error = bread(pmp->pm_devvp, bn, bsize, NOCRED, &bp);
			if (error) {
				brelse(bp);
				return (error);
			}
			lbn = bn;
		}
		usemap_free(pmp, cluster);
		switch (pmp->pm_fatmask) {
		case FAT12_MASK:
			readcn = getushort(bp->b_data + bo);
			if (cluster & 1) {
				cluster = readcn >> 4;
				readcn &= 0x000f;
				readcn |= MSDOSFSFREE << 4;
			} else {
				cluster = readcn;
				readcn &= 0xf000;
				readcn |= MSDOSFSFREE & 0xfff;
			}
			putushort(bp->b_data + bo, readcn);
			break;
		case FAT16_MASK:
			cluster = getushort(bp->b_data + bo);
			putushort(bp->b_data + bo, MSDOSFSFREE);
			break;
		case FAT32_MASK:
			cluster = getulong(bp->b_data + bo);
			putulong(bp->b_data + bo,
				 (MSDOSFSFREE & FAT32_MASK) | (cluster & ~FAT32_MASK));
			break;
		}
		cluster &= pmp->pm_fatmask;
		if ((cluster | ~pmp->pm_fatmask) >= CLUST_RSRVD)
			cluster |= pmp->pm_fatmask;
	}
	if (bp)
		updatefats(pmp, bp, bn);
	return (0);
}