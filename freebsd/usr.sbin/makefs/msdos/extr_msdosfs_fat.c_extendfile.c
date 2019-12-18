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
typedef  scalar_t__ u_long ;
struct msdosfsmount {int /*<<< orphan*/  pm_bpcluster; int /*<<< orphan*/  pm_devvp; } ;
struct denode {scalar_t__ de_StartCluster; int de_Attributes; TYPE_1__* de_fc; struct msdosfsmount* de_pmp; } ;
struct buf {int dummy; } ;
struct TYPE_2__ {scalar_t__ fc_frcn; scalar_t__ fc_fsrcn; } ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int /*<<< orphan*/  CLUST_EOFE ; 
 int DE_CLEAR ; 
 int E2BIG ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FAT_SET ; 
 scalar_t__ FCE_EMPTY ; 
 size_t FC_LASTFC ; 
 size_t FC_NEXTTOLASTFC ; 
 scalar_t__ MSDOSFSROOT ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int /*<<< orphan*/  clrbuf (struct buf*) ; 
 int clusteralloc (struct msdosfsmount*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  clusterfree (struct msdosfsmount*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cntobn (struct msdosfsmount*,int /*<<< orphan*/ ) ; 
 int fatentry (int /*<<< orphan*/ ,struct msdosfsmount*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fc_setcache (struct denode*,size_t,scalar_t__,scalar_t__) ; 
 struct buf* getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcbmap (struct denode*,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
extendfile(struct denode *dep, u_long count, struct buf **bpp, u_long *ncp,
    int flags)
{
	int error;
	u_long frcn;
	u_long cn, got;
	struct msdosfsmount *pmp = dep->de_pmp;
	struct buf *bp;

	/*
	 * Don't try to extend the root directory
	 */
	if (dep->de_StartCluster == MSDOSFSROOT
	    && (dep->de_Attributes & ATTR_DIRECTORY)) {
#ifdef MSDOSFS_DEBUG
		printf("extendfile(): attempt to extend root directory\n");
#endif
		return (ENOSPC);
	}

	/*
	 * If the "file's last cluster" cache entry is empty, and the file
	 * is not empty, then fill the cache entry by calling pcbmap().
	 */
	if (dep->de_fc[FC_LASTFC].fc_frcn == FCE_EMPTY &&
	    dep->de_StartCluster != 0) {
		error = pcbmap(dep, 0xffff, 0, &cn, 0);
		/* we expect it to return E2BIG */
		if (error != E2BIG)
			return (error);
	}

	dep->de_fc[FC_NEXTTOLASTFC].fc_frcn =
	    dep->de_fc[FC_LASTFC].fc_frcn;
	dep->de_fc[FC_NEXTTOLASTFC].fc_fsrcn =
	    dep->de_fc[FC_LASTFC].fc_fsrcn;
	while (count > 0) {
		/*
		 * Allocate a new cluster chain and cat onto the end of the
		 * file.  If the file is empty we make de_StartCluster point
		 * to the new block.  Note that de_StartCluster being 0 is
		 * sufficient to be sure the file is empty since we exclude
		 * attempts to extend the root directory above, and the root
		 * dir is the only file with a startcluster of 0 that has
		 * blocks allocated (sort of).
		 */
		if (dep->de_StartCluster == 0)
			cn = 0;
		else
			cn = dep->de_fc[FC_LASTFC].fc_fsrcn + 1;
		error = clusteralloc(pmp, cn, count, CLUST_EOFE, &cn, &got);
		if (error)
			return (error);

		count -= got;

		/*
		 * Give them the filesystem relative cluster number if they want
		 * it.
		 */
		if (ncp) {
			*ncp = cn;
			ncp = NULL;
		}

		if (dep->de_StartCluster == 0) {
			dep->de_StartCluster = cn;
			frcn = 0;
		} else {
			error = fatentry(FAT_SET, pmp,
					 dep->de_fc[FC_LASTFC].fc_fsrcn,
					 0, cn);
			if (error) {
				clusterfree(pmp, cn, NULL);
				return (error);
			}
			frcn = dep->de_fc[FC_LASTFC].fc_frcn + 1;
		}

		/*
		 * Update the "last cluster of the file" entry in the
		 * denode's FAT cache.
		 */
		fc_setcache(dep, FC_LASTFC, frcn + got - 1, cn + got - 1);

		if ((flags & DE_CLEAR) &&
		    (dep->de_Attributes & ATTR_DIRECTORY)) {
			while (got-- > 0) {
				bp = getblk(pmp->pm_devvp,
				    cntobn(pmp, cn++),
				    pmp->pm_bpcluster, 0, 0, 0);
				clrbuf(bp);
				if (bpp) {
					*bpp = bp;
					bpp = NULL;
				} else {
					bdwrite(bp);
				}
			}
		}
	}

	return (0);
}