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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u_long ;
struct vnode {int /*<<< orphan*/  v_type; int /*<<< orphan*/  v_vflag; struct denode* v_data; int /*<<< orphan*/  v_vnlock; } ;
struct msdosfsmount {scalar_t__ pm_rootdirblk; int pm_rootdirsize; scalar_t__ pm_bpcluster; struct mount* pm_mountp; } ;
struct mount {int dummy; } ;
struct direntry {int dummy; } ;
struct denode {scalar_t__ de_dirclust; scalar_t__ de_diroffset; int de_refcnt; int de_Attributes; scalar_t__ de_StartCluster; int de_FileSize; int de_CTime; int de_CDate; int de_ADate; int de_MTime; int de_MDate; int /*<<< orphan*/  de_modrev; int /*<<< orphan*/ * de_Name; scalar_t__ de_CHun; scalar_t__ de_LowerCase; struct msdosfsmount* de_pmp; scalar_t__ de_inode; scalar_t__ de_flag; struct vnode* de_vnode; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int DD_DAY_SHIFT ; 
 int DD_MONTH_SHIFT ; 
 int DD_YEAR_SHIFT ; 
 int DEV_BSIZE ; 
 int /*<<< orphan*/  DE_INTERNALIZE (struct denode*,struct direntry*) ; 
 int E2BIG ; 
 scalar_t__ FAT32 (struct msdosfsmount*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 scalar_t__ MSDOSFSROOT ; 
 scalar_t__ MSDOSFSROOT_OFS ; 
 int /*<<< orphan*/  M_MSDOSFSNODE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLOT_DELETED ; 
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  VREG ; 
 struct denode* VTODE (struct vnode*) ; 
 int /*<<< orphan*/  VV_ROOT ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  curthread ; 
 int de_cn2off (struct msdosfsmount*,scalar_t__) ; 
 int /*<<< orphan*/  de_vncmpf ; 
 int /*<<< orphan*/  fc_purge (struct denode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct denode*,int /*<<< orphan*/ ) ; 
 int getnewvnode (char*,struct mount*,int /*<<< orphan*/ *,struct vnode**) ; 
 int /*<<< orphan*/  init_va_filerev () ; 
 int insmntque (struct vnode*,struct mount*) ; 
 int /*<<< orphan*/  lockmgr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct denode* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msdosfs_vnodeops ; 
 int pcbmap (struct denode*,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int readep (struct msdosfsmount*,scalar_t__,scalar_t__,struct buf**,struct direntry**) ; 
 int vfs_hash_get (struct mount*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**,int /*<<< orphan*/ ,scalar_t__*) ; 
 int vfs_hash_insert (struct vnode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode**,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
deget(struct msdosfsmount *pmp, u_long dirclust, u_long diroffset,
    struct denode **depp)
{
	int error;
	uint64_t inode;
	struct mount *mntp = pmp->pm_mountp;
	struct direntry *direntptr;
	struct denode *ldep;
	struct vnode *nvp, *xvp;
	struct buf *bp;

#ifdef MSDOSFS_DEBUG
	printf("deget(pmp %p, dirclust %lu, diroffset %lx, depp %p)\n",
	    pmp, dirclust, diroffset, depp);
#endif

	/*
	 * On FAT32 filesystems, root is a (more or less) normal
	 * directory
	 */
	if (FAT32(pmp) && dirclust == MSDOSFSROOT)
		dirclust = pmp->pm_rootdirblk;

	/*
	 * See if the denode is in the denode cache. Use the location of
	 * the directory entry to compute the hash value. For subdir use
	 * address of "." entry. For root dir (if not FAT32) use cluster
	 * MSDOSFSROOT, offset MSDOSFSROOT_OFS
	 *
	 * NOTE: de_vncmpf will explicitly skip any denodes that do not have
	 * a de_refcnt > 0.  This insures that that we do not attempt to use
	 * a denode that represents an unlinked but still open file.
	 * These files are not to be accessible even when the directory
	 * entry that represented the file happens to be reused while the
	 * deleted file is still open.
	 */
	inode = (uint64_t)pmp->pm_bpcluster * dirclust + diroffset;

	error = vfs_hash_get(mntp, inode, LK_EXCLUSIVE, curthread, &nvp,
	    de_vncmpf, &inode);
	if (error)
		return (error);
	if (nvp != NULL) {
		*depp = VTODE(nvp);
		KASSERT((*depp)->de_dirclust == dirclust, ("wrong dirclust"));
		KASSERT((*depp)->de_diroffset == diroffset, ("wrong diroffset"));
		return (0);
	}
	ldep = malloc(sizeof(struct denode), M_MSDOSFSNODE, M_WAITOK | M_ZERO);

	/*
	 * Directory entry was not in cache, have to create a vnode and
	 * copy it from the passed disk buffer.
	 */
	/* getnewvnode() does a VREF() on the vnode */
	error = getnewvnode("msdosfs", mntp, &msdosfs_vnodeops, &nvp);
	if (error) {
		*depp = NULL;
		free(ldep, M_MSDOSFSNODE);
		return error;
	}
	nvp->v_data = ldep;
	ldep->de_vnode = nvp;
	ldep->de_flag = 0;
	ldep->de_dirclust = dirclust;
	ldep->de_diroffset = diroffset;
	ldep->de_inode = inode;
	lockmgr(nvp->v_vnlock, LK_EXCLUSIVE, NULL);
	fc_purge(ldep, 0);	/* init the FAT cache for this denode */
	error = insmntque(nvp, mntp);
	if (error != 0) {
		free(ldep, M_MSDOSFSNODE);
		*depp = NULL;
		return (error);
	}
	error = vfs_hash_insert(nvp, inode, LK_EXCLUSIVE, curthread, &xvp,
	    de_vncmpf, &inode);
	if (error) {
		*depp = NULL;
		return (error);
	}
	if (xvp != NULL) {
		*depp = xvp->v_data;
		return (0);
	}

	ldep->de_pmp = pmp;
	ldep->de_refcnt = 1;
	/*
	 * Copy the directory entry into the denode area of the vnode.
	 */
	if ((dirclust == MSDOSFSROOT
	     || (FAT32(pmp) && dirclust == pmp->pm_rootdirblk))
	    && diroffset == MSDOSFSROOT_OFS) {
		/*
		 * Directory entry for the root directory. There isn't one,
		 * so we manufacture one. We should probably rummage
		 * through the root directory and find a label entry (if it
		 * exists), and then use the time and date from that entry
		 * as the time and date for the root denode.
		 */
		nvp->v_vflag |= VV_ROOT; /* should be further down XXX */

		ldep->de_Attributes = ATTR_DIRECTORY;
		ldep->de_LowerCase = 0;
		if (FAT32(pmp))
			ldep->de_StartCluster = pmp->pm_rootdirblk;
			/* de_FileSize will be filled in further down */
		else {
			ldep->de_StartCluster = MSDOSFSROOT;
			ldep->de_FileSize = pmp->pm_rootdirsize * DEV_BSIZE;
		}
		/*
		 * fill in time and date so that fattime2timespec() doesn't
		 * spit up when called from msdosfs_getattr() with root
		 * denode
		 */
		ldep->de_CHun = 0;
		ldep->de_CTime = 0x0000;	/* 00:00:00	 */
		ldep->de_CDate = (0 << DD_YEAR_SHIFT) | (1 << DD_MONTH_SHIFT)
		    | (1 << DD_DAY_SHIFT);
		/* Jan 1, 1980	 */
		ldep->de_ADate = ldep->de_CDate;
		ldep->de_MTime = ldep->de_CTime;
		ldep->de_MDate = ldep->de_CDate;
		/* leave the other fields as garbage */
	} else {
		error = readep(pmp, dirclust, diroffset, &bp, &direntptr);
		if (error) {
			/*
			 * The denode does not contain anything useful, so
			 * it would be wrong to leave it on its hash chain.
			 * Arrange for vput() to just forget about it.
			 */
			ldep->de_Name[0] = SLOT_DELETED;

			vput(nvp);
			*depp = NULL;
			return (error);
		}
		(void)DE_INTERNALIZE(ldep, direntptr);
		brelse(bp);
	}

	/*
	 * Fill in a few fields of the vnode and finish filling in the
	 * denode.  Then return the address of the found denode.
	 */
	if (ldep->de_Attributes & ATTR_DIRECTORY) {
		/*
		 * Since DOS directory entries that describe directories
		 * have 0 in the filesize field, we take this opportunity
		 * to find out the length of the directory and plug it into
		 * the denode structure.
		 */
		u_long size;

		/*
		 * XXX it sometimes happens that the "." entry has cluster
		 * number 0 when it shouldn't.  Use the actual cluster number
		 * instead of what is written in directory entry.
		 */
		if (diroffset == 0 && ldep->de_StartCluster != dirclust) {
#ifdef MSDOSFS_DEBUG
			printf("deget(): \".\" entry at clust %lu != %lu\n",
			    dirclust, ldep->de_StartCluster);
#endif
			ldep->de_StartCluster = dirclust;
		}

		nvp->v_type = VDIR;
		if (ldep->de_StartCluster != MSDOSFSROOT) {
			error = pcbmap(ldep, 0xffff, 0, &size, 0);
			if (error == E2BIG) {
				ldep->de_FileSize = de_cn2off(pmp, size);
				error = 0;
			} else {
#ifdef MSDOSFS_DEBUG
				printf("deget(): pcbmap returned %d\n", error);
#endif
			}
		}
	} else
		nvp->v_type = VREG;
	ldep->de_modrev = init_va_filerev();
	*depp = ldep;
	return (0);
}