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
 int EINVAL ; 
#define  FAT12_MASK 130 
#define  FAT16_MASK 129 
#define  FAT32_MASK 128 
 int FATOFS (struct msdosfsmount*,int) ; 
 int /*<<< orphan*/  NOCRED ; 
 int bread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  fatblock (struct msdosfsmount*,int,int*,int*,int*) ; 
 int getulong (int) ; 
 int getushort (int) ; 
 int /*<<< orphan*/  printf (char*,struct msdosfsmount*,int,int,int) ; 
 int /*<<< orphan*/  putulong (int,int) ; 
 int /*<<< orphan*/  putushort (int,int) ; 
 int /*<<< orphan*/  updatefats (struct msdosfsmount*,struct buf*,int) ; 

__attribute__((used)) static int
fatchain(struct msdosfsmount *pmp, u_long start, u_long count, u_long fillwith)
{
	int error;
	u_long bn, bo, bsize, byteoffset, readcn, newc;
	struct buf *bp;

#ifdef MSDOSFS_DEBUG
	printf("fatchain(pmp %p, start %lu, count %lu, fillwith %lx)\n",
	    pmp, start, count, fillwith);
#endif
	/*
	 * Be sure the clusters are in the filesystem.
	 */
	if (start < CLUST_FIRST || start + count - 1 > pmp->pm_maxcluster)
		return (EINVAL);

	while (count > 0) {
		byteoffset = FATOFS(pmp, start);
		fatblock(pmp, byteoffset, &bn, &bsize, &bo);
		error = bread(pmp->pm_devvp, bn, bsize, NOCRED, &bp);
		if (error) {
			brelse(bp);
			return (error);
		}
		while (count > 0) {
			start++;
			newc = --count > 0 ? start : fillwith;
			switch (pmp->pm_fatmask) {
			case FAT12_MASK:
				readcn = getushort(bp->b_data + bo);
				if (start & 1) {
					readcn &= 0xf000;
					readcn |= newc & 0xfff;
				} else {
					readcn &= 0x000f;
					readcn |= newc << 4;
				}
				putushort(bp->b_data + bo, readcn);
				bo++;
				if (!(start & 1))
					bo++;
				break;
			case FAT16_MASK:
				putushort(bp->b_data + bo, newc);
				bo += 2;
				break;
			case FAT32_MASK:
				readcn = getulong(bp->b_data + bo);
				readcn &= ~pmp->pm_fatmask;
				readcn |= newc & pmp->pm_fatmask;
				putulong(bp->b_data + bo, readcn);
				bo += 4;
				break;
			}
			if (bo >= bsize)
				break;
		}
		updatefats(pmp, bp, bn);
	}
	pmp->pm_fmod = 1;
	return (0);
}