#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct ucred {int dummy; } ;
struct msdosfsmount {int pm_crbomask; scalar_t__ pm_bpcluster; TYPE_1__* pm_devvp; } ;
struct denode {int de_Attributes; char* de_Name; int de_FileSize; int de_StartCluster; int de_flag; int /*<<< orphan*/  de_diroffset; int /*<<< orphan*/  de_dirclust; struct msdosfsmount* de_pmp; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  daddr_t ;
struct TYPE_6__ {int v_vflag; } ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int /*<<< orphan*/  CLUST_EOFE ; 
 TYPE_1__* DETOV (struct denode*) ; 
 int DE_MODIFIED ; 
 int DE_UPDATE ; 
 int /*<<< orphan*/  DOINGASYNC (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FAT32 (struct msdosfsmount*) ; 
 int /*<<< orphan*/  FAT_GET_AND_SET ; 
 int /*<<< orphan*/  FC_LASTFC ; 
 int IO_SYNC ; 
 int /*<<< orphan*/  MSDOSFSEOF (struct msdosfsmount*,int) ; 
 struct ucred* NOCRED ; 
 int VV_ROOT ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int bread (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,struct ucred*,struct buf**) ; 
 int /*<<< orphan*/  bwrite (struct buf*) ; 
 int /*<<< orphan*/  cntobn (struct msdosfsmount*,int) ; 
 scalar_t__ de_clcount (struct msdosfsmount*,int) ; 
 int /*<<< orphan*/  de_cluster (struct msdosfsmount*,int) ; 
 int deextend (struct denode*,int,struct ucred*) ; 
 int deupdat (struct denode*,int) ; 
 int fatentry (int /*<<< orphan*/ ,struct msdosfsmount*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_purge (struct denode*,scalar_t__) ; 
 int /*<<< orphan*/  fc_setcache (struct denode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  freeclusterchain (struct msdosfsmount*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int pcbmap (struct denode*,scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vnode_pager_setsize (TYPE_1__*,int) ; 
 int vtruncbuf (TYPE_1__*,int,scalar_t__) ; 

int
detrunc(struct denode *dep, u_long length, int flags, struct ucred *cred)
{
	int error;
	int allerror;
	u_long eofentry;
	u_long chaintofree;
	daddr_t bn;
	int boff;
	int isadir = dep->de_Attributes & ATTR_DIRECTORY;
	struct buf *bp;
	struct msdosfsmount *pmp = dep->de_pmp;

#ifdef MSDOSFS_DEBUG
	printf("detrunc(): file %s, length %lu, flags %x\n", dep->de_Name, length, flags);
#endif

	/*
	 * Disallow attempts to truncate the root directory since it is of
	 * fixed size.  That's just the way dos filesystems are.  We use
	 * the VROOT bit in the vnode because checking for the directory
	 * bit and a startcluster of 0 in the denode is not adequate to
	 * recognize the root directory at this point in a file or
	 * directory's life.
	 */
	if ((DETOV(dep)->v_vflag & VV_ROOT) && !FAT32(pmp)) {
#ifdef MSDOSFS_DEBUG
		printf("detrunc(): can't truncate root directory, clust %ld, offset %ld\n",
		    dep->de_dirclust, dep->de_diroffset);
#endif
		return (EINVAL);
	}

	if (dep->de_FileSize < length) {
		vnode_pager_setsize(DETOV(dep), length);
		return deextend(dep, length, cred);
	}

	/*
	 * If the desired length is 0 then remember the starting cluster of
	 * the file and set the StartCluster field in the directory entry
	 * to 0.  If the desired length is not zero, then get the number of
	 * the last cluster in the shortened file.  Then get the number of
	 * the first cluster in the part of the file that is to be freed.
	 * Then set the next cluster pointer in the last cluster of the
	 * file to CLUST_EOFE.
	 */
	if (length == 0) {
		chaintofree = dep->de_StartCluster;
		dep->de_StartCluster = 0;
		eofentry = ~0;
	} else {
		error = pcbmap(dep, de_clcount(pmp, length) - 1, 0,
			       &eofentry, 0);
		if (error) {
#ifdef MSDOSFS_DEBUG
			printf("detrunc(): pcbmap fails %d\n", error);
#endif
			return (error);
		}
	}

	fc_purge(dep, de_clcount(pmp, length));

	/*
	 * If the new length is not a multiple of the cluster size then we
	 * must zero the tail end of the new last cluster in case it
	 * becomes part of the file again because of a seek.
	 */
	if ((boff = length & pmp->pm_crbomask) != 0) {
		if (isadir) {
			bn = cntobn(pmp, eofentry);
			error = bread(pmp->pm_devvp, bn, pmp->pm_bpcluster,
			    NOCRED, &bp);
		} else {
			error = bread(DETOV(dep), de_cluster(pmp, length),
			    pmp->pm_bpcluster, cred, &bp);
		}
		if (error) {
#ifdef MSDOSFS_DEBUG
			printf("detrunc(): bread fails %d\n", error);
#endif
			return (error);
		}
		memset(bp->b_data + boff, 0, pmp->pm_bpcluster - boff);
		if ((flags & IO_SYNC) != 0)
			bwrite(bp);
		else
			bdwrite(bp);
	}

	/*
	 * Write out the updated directory entry.  Even if the update fails
	 * we free the trailing clusters.
	 */
	dep->de_FileSize = length;
	if (!isadir)
		dep->de_flag |= DE_UPDATE | DE_MODIFIED;
	allerror = vtruncbuf(DETOV(dep), length, pmp->pm_bpcluster);
#ifdef MSDOSFS_DEBUG
	if (allerror)
		printf("detrunc(): vtruncbuf error %d\n", allerror);
#endif
	error = deupdat(dep, !DOINGASYNC((DETOV(dep))));
	if (error != 0 && allerror == 0)
		allerror = error;
#ifdef MSDOSFS_DEBUG
	printf("detrunc(): allerror %d, eofentry %lu\n",
	       allerror, eofentry);
#endif

	/*
	 * If we need to break the cluster chain for the file then do it
	 * now.
	 */
	if (eofentry != ~0) {
		error = fatentry(FAT_GET_AND_SET, pmp, eofentry,
				 &chaintofree, CLUST_EOFE);
		if (error) {
#ifdef MSDOSFS_DEBUG
			printf("detrunc(): fatentry errors %d\n", error);
#endif
			return (error);
		}
		fc_setcache(dep, FC_LASTFC, de_cluster(pmp, length - 1),
			    eofentry);
	}

	/*
	 * Now free the clusters removed from the file because of the
	 * truncation.
	 */
	if (chaintofree != 0 && !MSDOSFSEOF(pmp, chaintofree))
		freeclusterchain(pmp, chaintofree);

	return (allerror);
}