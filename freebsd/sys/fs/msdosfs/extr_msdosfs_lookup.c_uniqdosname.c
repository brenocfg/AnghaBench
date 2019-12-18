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
typedef  int /*<<< orphan*/  u_char ;
struct msdosfsmount {int pm_flags; int /*<<< orphan*/  pm_devvp; } ;
struct direntry {scalar_t__* deName; int deAttributes; } ;
struct denode {struct msdosfsmount* de_pmp; } ;
struct componentname {int /*<<< orphan*/  cn_namelen; scalar_t__ cn_nameptr; } ;
struct buf {char* b_data; } ;
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 int ATTR_VOLUME ; 
 int E2BIG ; 
 int EEXIST ; 
 int EINVAL ; 
 int MSDOSFSMNT_SHORTNAME ; 
 int /*<<< orphan*/  NOCRED ; 
 scalar_t__ SLOT_EMPTY ; 
 int /*<<< orphan*/  bcmp (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int pcbmap (struct denode*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ unix2dosfn (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct msdosfsmount*) ; 

int
uniqdosname(struct denode *dep, struct componentname *cnp, u_char *cp)
{
	struct msdosfsmount *pmp = dep->de_pmp;
	struct direntry *dentp;
	int gen;
	int blsize;
	u_long cn;
	daddr_t bn;
	struct buf *bp;
	int error;

	if (pmp->pm_flags & MSDOSFSMNT_SHORTNAME)
		return (unix2dosfn((const u_char *)cnp->cn_nameptr, cp,
		    cnp->cn_namelen, 0, pmp) ? 0 : EINVAL);

	for (gen = 1;; gen++) {
		/*
		 * Generate DOS name with generation number
		 */
		if (!unix2dosfn((const u_char *)cnp->cn_nameptr, cp,
		    cnp->cn_namelen, gen, pmp))
			return gen == 1 ? EINVAL : EEXIST;

		/*
		 * Now look for a dir entry with this exact name
		 */
		for (cn = error = 0; !error; cn++) {
			if ((error = pcbmap(dep, cn, &bn, 0, &blsize)) != 0) {
				if (error == E2BIG)	/* EOF reached and not found */
					return 0;
				return error;
			}
			error = bread(pmp->pm_devvp, bn, blsize, NOCRED, &bp);
			if (error) {
				return error;
			}
			for (dentp = (struct direntry *)bp->b_data;
			     (char *)dentp < bp->b_data + blsize;
			     dentp++) {
				if (dentp->deName[0] == SLOT_EMPTY) {
					/*
					 * Last used entry and not found
					 */
					brelse(bp);
					return 0;
				}
				/*
				 * Ignore volume labels and Win95 entries
				 */
				if (dentp->deAttributes & ATTR_VOLUME)
					continue;
				if (!bcmp(dentp->deName, cp, 11)) {
					error = EEXIST;
					break;
				}
			}
			brelse(bp);
		}
	}
}