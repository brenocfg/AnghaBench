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
typedef  int uint64_t ;
typedef  int u_long ;
typedef  char u_char ;
struct winentry {int dummy; } ;
struct vnode {int v_vflag; } ;
struct msdosfsmount {int pm_flags; int pm_rootdirblk; scalar_t__ pm_bpcluster; int /*<<< orphan*/  pm_devvp; } ;
struct mbnambuf {int dummy; } ;
struct direntry {scalar_t__* deName; int deAttributes; int /*<<< orphan*/  deHighClust; int /*<<< orphan*/  deStartCluster; } ;
struct denode {int de_Attributes; int de_fndoffset; int de_fndcnt; int de_refcnt; int de_StartCluster; int de_inode; struct msdosfsmount* de_pmp; } ;
struct deget_dotdot {int cluster; int blkoff; } ;
struct componentname {int cn_flags; int cn_nameiop; char* cn_nameptr; int cn_namelen; int /*<<< orphan*/  cn_lkflags; int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int ATTR_VOLUME ; 
 int ATTR_WIN95 ; 
 int CREATE ; 
 int DELETE ; 
 struct vnode* DETOV (struct denode*) ; 
 int E2BIG ; 
 int EBUSY ; 
 int EINVAL ; 
 int EISDIR ; 
 int EJUSTRETURN ; 
 int ENOENT ; 
 scalar_t__ FAT32 (struct msdosfsmount*) ; 
 int ISDOTDOT ; 
 int ISLASTCN ; 
 int MAKEENTRY ; 
 int MSDOSFSMNT_SHORTNAME ; 
 int MSDOSFSROOT ; 
 int MSDOSFSROOT_OFS ; 
 int /*<<< orphan*/  NOCRED ; 
 int RENAME ; 
 int SAVENAME ; 
 scalar_t__ SLOT_DELETED ; 
 scalar_t__ SLOT_EMPTY ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VREF (struct vnode*) ; 
 struct denode* VTODE (struct vnode*) ; 
 int VV_ROOT ; 
 int /*<<< orphan*/  VWRITE ; 
 scalar_t__ bcmp (char*,scalar_t__*,int) ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int /*<<< orphan*/  cache_enter (struct vnode*,struct vnode*,struct componentname*) ; 
 int deget (struct msdosfsmount*,int,int,struct denode**) ; 
 int getushort (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbnambuf_init (struct mbnambuf*) ; 
 int /*<<< orphan*/  msdosfs_deget_dotdot ; 
 int pcbmap (struct denode*,int,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int unix2dosfn (char const*,char*,int,int /*<<< orphan*/ ,struct msdosfsmount*) ; 
 int vn_vget_ino_gen (struct vnode*,int /*<<< orphan*/ ,struct deget_dotdot*,int /*<<< orphan*/ ,struct vnode**) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int win2unixfn (struct mbnambuf*,struct winentry*,int,struct msdosfsmount*) ; 
 int winChkName (struct mbnambuf*,char const*,int,int,struct msdosfsmount*) ; 
 int winChksum (scalar_t__*) ; 
 int winLenFixup (char*,int) ; 
 int /*<<< orphan*/  winSlotCnt (char const*,int,struct msdosfsmount*) ; 

__attribute__((used)) static int
msdosfs_lookup_(struct vnode *vdp, struct vnode **vpp,
    struct componentname *cnp, uint64_t *dd_inum)
{
	struct mbnambuf nb;
	daddr_t bn;
	int error;
	int slotcount;
	int slotoffset = 0;
	int frcn;
	u_long cluster;
	int blkoff;
	int diroff;
	int blsize;
	int isadir;		/* ~0 if found direntry is a directory	 */
	u_long scn;		/* starting cluster number		 */
	struct vnode *pdp;
	struct denode *dp;
	struct denode *tdp;
	struct msdosfsmount *pmp;
	struct buf *bp = NULL;
	struct direntry *dep = NULL;
	struct deget_dotdot dd_arg;
	u_char dosfilename[12];
	int flags = cnp->cn_flags;
	int nameiop = cnp->cn_nameiop;
	int unlen;
	uint64_t inode1;

	int wincnt = 1;
	int chksum = -1, chksum_ok;
	int olddos = 1;

#ifdef MSDOSFS_DEBUG
	printf("msdosfs_lookup(): looking for %s\n", cnp->cn_nameptr);
#endif
	dp = VTODE(vdp);
	pmp = dp->de_pmp;
#ifdef MSDOSFS_DEBUG
	printf("msdosfs_lookup(): vdp %p, dp %p, Attr %02x\n",
	    vdp, dp, dp->de_Attributes);
#endif

 restart:
	if (vpp != NULL)
		*vpp = NULL;
	/*
	 * If they are going after the . or .. entry in the root directory,
	 * they won't find it.  DOS filesystems don't have them in the root
	 * directory.  So, we fake it. deget() is in on this scam too.
	 */
	if ((vdp->v_vflag & VV_ROOT) && cnp->cn_nameptr[0] == '.' &&
	    (cnp->cn_namelen == 1 ||
		(cnp->cn_namelen == 2 && cnp->cn_nameptr[1] == '.'))) {
		isadir = ATTR_DIRECTORY;
		scn = MSDOSFSROOT;
#ifdef MSDOSFS_DEBUG
		printf("msdosfs_lookup(): looking for . or .. in root directory\n");
#endif
		cluster = MSDOSFSROOT;
		blkoff = MSDOSFSROOT_OFS;
		goto foundroot;
	}

	switch (unix2dosfn((const u_char *)cnp->cn_nameptr, dosfilename,
	    cnp->cn_namelen, 0, pmp)) {
	case 0:
		return (EINVAL);
	case 1:
		break;
	case 2:
		wincnt = winSlotCnt((const u_char *)cnp->cn_nameptr,
		    cnp->cn_namelen, pmp) + 1;
		break;
	case 3:
		olddos = 0;
		wincnt = winSlotCnt((const u_char *)cnp->cn_nameptr,
		    cnp->cn_namelen, pmp) + 1;
		break;
	}
	if (pmp->pm_flags & MSDOSFSMNT_SHORTNAME) {
		wincnt = 1;
		olddos = 1;
	}
	unlen = winLenFixup(cnp->cn_nameptr, cnp->cn_namelen);

	/*
	 * Suppress search for slots unless creating
	 * file and at end of pathname, in which case
	 * we watch for a place to put the new file in
	 * case it doesn't already exist.
	 */
	slotcount = wincnt;
	if ((nameiop == CREATE || nameiop == RENAME) &&
	    (flags & ISLASTCN))
		slotcount = 0;

#ifdef MSDOSFS_DEBUG
	printf("msdosfs_lookup(): dos version of filename %s, length %ld\n",
	    dosfilename, cnp->cn_namelen);
#endif
	/*
	 * Search the directory pointed at by vdp for the name pointed at
	 * by cnp->cn_nameptr.
	 */
	tdp = NULL;
	mbnambuf_init(&nb);
	/*
	 * The outer loop ranges over the clusters that make up the
	 * directory.  Note that the root directory is different from all
	 * other directories.  It has a fixed number of blocks that are not
	 * part of the pool of allocatable clusters.  So, we treat it a
	 * little differently. The root directory starts at "cluster" 0.
	 */
	diroff = 0;
	for (frcn = 0;; frcn++) {
		error = pcbmap(dp, frcn, &bn, &cluster, &blsize);
		if (error) {
			if (error == E2BIG)
				break;
			return (error);
		}
		error = bread(pmp->pm_devvp, bn, blsize, NOCRED, &bp);
		if (error) {
			return (error);
		}
		for (blkoff = 0; blkoff < blsize;
		     blkoff += sizeof(struct direntry),
		     diroff += sizeof(struct direntry)) {
			dep = (struct direntry *)(bp->b_data + blkoff);
			/*
			 * If the slot is empty and we are still looking
			 * for an empty then remember this one.  If the
			 * slot is not empty then check to see if it
			 * matches what we are looking for.  If the slot
			 * has never been filled with anything, then the
			 * remainder of the directory has never been used,
			 * so there is no point in searching it.
			 */
			if (dep->deName[0] == SLOT_EMPTY ||
			    dep->deName[0] == SLOT_DELETED) {
				/*
				 * Drop memory of previous long matches
				 */
				chksum = -1;
				mbnambuf_init(&nb);

				if (slotcount < wincnt) {
					slotcount++;
					slotoffset = diroff;
				}
				if (dep->deName[0] == SLOT_EMPTY) {
					brelse(bp);
					goto notfound;
				}
			} else {
				/*
				 * If there wasn't enough space for our winentries,
				 * forget about the empty space
				 */
				if (slotcount < wincnt)
					slotcount = 0;

				/*
				 * Check for Win95 long filename entry
				 */
				if (dep->deAttributes == ATTR_WIN95) {
					if (pmp->pm_flags & MSDOSFSMNT_SHORTNAME)
						continue;

					chksum = win2unixfn(&nb,
					    (struct winentry *)dep, chksum,
					    pmp);
					continue;
				}

				chksum = winChkName(&nb,
				    (const u_char *)cnp->cn_nameptr, unlen,
				    chksum, pmp);
				if (chksum == -2) {
					chksum = -1;
					continue;
				}

				/*
				 * Ignore volume labels (anywhere, not just
				 * the root directory).
				 */
				if (dep->deAttributes & ATTR_VOLUME) {
					chksum = -1;
					continue;
				}

				/*
				 * Check for a checksum or name match
				 */
				chksum_ok = (chksum == winChksum(dep->deName));
				if (!chksum_ok
				    && (!olddos || bcmp(dosfilename, dep->deName, 11))) {
					chksum = -1;
					continue;
				}
#ifdef MSDOSFS_DEBUG
				printf("msdosfs_lookup(): match blkoff %d, diroff %d\n",
				    blkoff, diroff);
#endif
				/*
				 * Remember where this directory
				 * entry came from for whoever did
				 * this lookup.
				 */
				dp->de_fndoffset = diroff;
				if (chksum_ok && nameiop == RENAME) {
					/*
					 * Target had correct long name
					 * directory entries, reuse them
					 * as needed.
					 */
					dp->de_fndcnt = wincnt - 1;
				} else {
					/*
					 * Long name directory entries
					 * not present or corrupt, can only
					 * reuse dos directory entry.
					 */
					dp->de_fndcnt = 0;
				}

				goto found;
			}
		}	/* for (blkoff = 0; .... */
		/*
		 * Release the buffer holding the directory cluster just
		 * searched.
		 */
		brelse(bp);
	}	/* for (frcn = 0; ; frcn++) */

notfound:
	/*
	 * We hold no disk buffers at this point.
	 */

	/*
	 * Fixup the slot description to point to the place where
	 * we might put the new DOS direntry (putting the Win95
	 * long name entries before that)
	 */
	if (!slotcount) {
		slotcount = 1;
		slotoffset = diroff;
	}
	if (wincnt > slotcount)
		slotoffset += sizeof(struct direntry) * (wincnt - slotcount);

	/*
	 * If we get here we didn't find the entry we were looking for. But
	 * that's ok if we are creating or renaming and are at the end of
	 * the pathname and the directory hasn't been removed.
	 */
#ifdef MSDOSFS_DEBUG
	printf("msdosfs_lookup(): op %d, refcnt %ld\n",
	    nameiop, dp->de_refcnt);
	printf("               slotcount %d, slotoffset %d\n",
	       slotcount, slotoffset);
#endif
	if ((nameiop == CREATE || nameiop == RENAME) &&
	    (flags & ISLASTCN) && dp->de_refcnt != 0) {
		/*
		 * Access for write is interpreted as allowing
		 * creation of files in the directory.
		 */
		error = VOP_ACCESS(vdp, VWRITE, cnp->cn_cred, cnp->cn_thread);
		if (error)
			return (error);
		/*
		 * Return an indication of where the new directory
		 * entry should be put.
		 */
		dp->de_fndoffset = slotoffset;
		dp->de_fndcnt = wincnt - 1;

		/*
		 * We return with the directory locked, so that
		 * the parameters we set up above will still be
		 * valid if we actually decide to do a direnter().
		 * We return ni_vp == NULL to indicate that the entry
		 * does not currently exist; we leave a pointer to
		 * the (locked) directory inode in ndp->ni_dvp.
		 * The pathname buffer is saved so that the name
		 * can be obtained later.
		 *
		 * NB - if the directory is unlocked, then this
		 * information cannot be used.
		 */
		cnp->cn_flags |= SAVENAME;
		return (EJUSTRETURN);
	}
#if 0
	/*
	 * Insert name into cache (as non-existent) if appropriate.
	 *
	 * XXX Negative caching is broken for msdosfs because the name
	 * cache doesn't understand peculiarities such as case insensitivity
	 * and 8.3 filenames.  Hence, it may not invalidate all negative
	 * entries if a file with this name is later created.
	 */
	if ((cnp->cn_flags & MAKEENTRY) != 0)
		cache_enter(vdp, *vpp, cnp);
#endif
	return (ENOENT);

found:
	/*
	 * NOTE:  We still have the buffer with matched directory entry at
	 * this point.
	 */
	isadir = dep->deAttributes & ATTR_DIRECTORY;
	scn = getushort(dep->deStartCluster);
	if (FAT32(pmp)) {
		scn |= getushort(dep->deHighClust) << 16;
		if (scn == pmp->pm_rootdirblk) {
			/*
			 * There should actually be 0 here.
			 * Just ignore the error.
			 */
			scn = MSDOSFSROOT;
		}
	}

	if (isadir) {
		cluster = scn;
		if (cluster == MSDOSFSROOT)
			blkoff = MSDOSFSROOT_OFS;
		else
			blkoff = 0;
	} else if (cluster == MSDOSFSROOT)
		blkoff = diroff;

	/*
	 * Now release buf to allow deget to read the entry again.
	 * Reserving it here and giving it to deget could result
	 * in a deadlock.
	 */
	brelse(bp);
	bp = NULL;

foundroot:
	/*
	 * If we entered at foundroot, then we are looking for the . or ..
	 * entry of the filesystems root directory.  isadir and scn were
	 * setup before jumping here.  And, bp is already null.
	 */
	if (FAT32(pmp) && scn == MSDOSFSROOT)
		scn = pmp->pm_rootdirblk;

	if (dd_inum != NULL) {
		*dd_inum = (uint64_t)pmp->pm_bpcluster * scn + blkoff;
		return (0);
	}

	/*
	 * If deleting, and at end of pathname, return
	 * parameters which can be used to remove file.
	 */
	if (nameiop == DELETE && (flags & ISLASTCN)) {
		/*
		 * Don't allow deleting the root.
		 */
		if (blkoff == MSDOSFSROOT_OFS)
			return (EBUSY);

		/*
		 * Write access to directory required to delete files.
		 */
		error = VOP_ACCESS(vdp, VWRITE, cnp->cn_cred, cnp->cn_thread);
		if (error)
			return (error);

		/*
		 * Return pointer to current entry in dp->i_offset.
		 * Save directory inode pointer in ndp->ni_dvp for dirremove().
		 */
		if (dp->de_StartCluster == scn && isadir) {	/* "." */
			VREF(vdp);
			*vpp = vdp;
			return (0);
		}
		error = deget(pmp, cluster, blkoff, &tdp);
		if (error)
			return (error);
		*vpp = DETOV(tdp);
		return (0);
	}

	/*
	 * If rewriting (RENAME), return the inode and the
	 * information required to rewrite the present directory
	 * Must get inode of directory entry to verify it's a
	 * regular file, or empty directory.
	 */
	if (nameiop == RENAME && (flags & ISLASTCN)) {
		if (blkoff == MSDOSFSROOT_OFS)
			return (EBUSY);

		error = VOP_ACCESS(vdp, VWRITE, cnp->cn_cred, cnp->cn_thread);
		if (error)
			return (error);

		/*
		 * Careful about locking second inode.
		 * This can only occur if the target is ".".
		 */
		if (dp->de_StartCluster == scn && isadir)
			return (EISDIR);

		if ((error = deget(pmp, cluster, blkoff, &tdp)) != 0)
			return (error);
		*vpp = DETOV(tdp);
		cnp->cn_flags |= SAVENAME;
		return (0);
	}

	/*
	 * Step through the translation in the name.  We do not `vput' the
	 * directory because we may need it again if a symbolic link
	 * is relative to the current directory.  Instead we save it
	 * unlocked as "pdp".  We must get the target inode before unlocking
	 * the directory to insure that the inode will not be removed
	 * before we get it.  We prevent deadlock by always fetching
	 * inodes from the root, moving down the directory tree. Thus
	 * when following backward pointers ".." we must unlock the
	 * parent directory before getting the requested directory.
	 */
	pdp = vdp;
	if (flags & ISDOTDOT) {
		dd_arg.cluster = cluster;
		dd_arg.blkoff = blkoff;
		error = vn_vget_ino_gen(vdp, msdosfs_deget_dotdot,
		    &dd_arg, cnp->cn_lkflags, vpp);
		if (error != 0) {
			*vpp = NULL;
			return (error);
		}
		/*
		 * Recheck that ".." still points to the inode we
		 * looked up before pdp lock was dropped.
		 */
		error = msdosfs_lookup_(pdp, NULL, cnp, &inode1);
		if (error) {
			vput(*vpp);
			*vpp = NULL;
			return (error);
		}
		if (VTODE(*vpp)->de_inode != inode1) {
			vput(*vpp);
			goto restart;
		}
	} else if (dp->de_StartCluster == scn && isadir) {
		VREF(vdp);	/* we want ourself, ie "." */
		*vpp = vdp;
	} else {
		if ((error = deget(pmp, cluster, blkoff, &tdp)) != 0)
			return (error);
		*vpp = DETOV(tdp);
	}

	/*
	 * Insert name into cache if appropriate.
	 */
	if (cnp->cn_flags & MAKEENTRY)
		cache_enter(vdp, *vpp, cnp);
	return (0);
}