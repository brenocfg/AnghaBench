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
typedef  int /*<<< orphan*/  u_char ;
struct vop_rename_args {struct vnode* a_fvp; struct componentname* a_fcnp; struct componentname* a_tcnp; struct vnode* a_tvp; struct vnode* a_fdvp; struct vnode* a_tdvp; } ;
struct vnode {scalar_t__ v_mount; } ;
struct msdosfsmount {scalar_t__ pm_crbomask; scalar_t__ pm_rootdirblk; int /*<<< orphan*/  pm_bpcluster; int /*<<< orphan*/  pm_devvp; } ;
struct direntry {int /*<<< orphan*/  deHighClust; int /*<<< orphan*/  deStartCluster; } ;
struct denode {int de_Attributes; int de_flag; scalar_t__ de_fndoffset; scalar_t__ de_StartCluster; scalar_t__ de_dirclust; scalar_t__ de_diroffset; int /*<<< orphan*/  de_refcnt; int /*<<< orphan*/ * de_Name; int /*<<< orphan*/  de_fndcnt; } ;
struct componentname {int cn_flags; int cn_namelen; char* cn_nameptr; int /*<<< orphan*/  cn_thread; int /*<<< orphan*/  cn_cred; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int DE_RENAME ; 
 scalar_t__ DOINGASYNC (struct vnode*) ; 
 int EINVAL ; 
 int EISDIR ; 
 int ENOTDIR ; 
 int ENOTEMPTY ; 
 int EXDEV ; 
 scalar_t__ FAT32 (struct msdosfsmount*) ; 
 int HASBUF ; 
 int ISDOTDOT ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int LOCKLEAF ; 
 int LOCKPARENT ; 
 int MODMASK ; 
 scalar_t__ MSDOSFSROOT ; 
 int /*<<< orphan*/  NOCRED ; 
 int SAVESTART ; 
 struct msdosfsmount* VFSTOMSDOSFS (scalar_t__) ; 
 int VOP_ACCESS (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 struct denode* VTODE (struct vnode*) ; 
 int /*<<< orphan*/  VWRITE ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buf**) ; 
 int bwrite (struct buf*) ; 
 int /*<<< orphan*/  cache_purge (struct vnode*) ; 
 int /*<<< orphan*/  cntobn (struct msdosfsmount*,scalar_t__) ; 
 int createde (struct denode*,struct denode*,struct denode**,struct componentname*) ; 
 int /*<<< orphan*/  de_cluster (struct msdosfsmount*,scalar_t__) ; 
 int doscheckpath (struct denode*,struct denode*) ; 
 int /*<<< orphan*/  dosdirempty (struct denode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pcbmap (struct denode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putushort (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  reinsert (struct denode*) ; 
 scalar_t__ relookup (struct vnode*,struct vnode**,struct componentname*) ; 
 int removede (struct denode*,struct denode*) ; 
 int uniqdosname (struct denode*,struct componentname*,int /*<<< orphan*/ *) ; 
 int vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

__attribute__((used)) static int
msdosfs_rename(struct vop_rename_args *ap)
{
	struct vnode *tdvp = ap->a_tdvp;
	struct vnode *fvp = ap->a_fvp;
	struct vnode *fdvp = ap->a_fdvp;
	struct vnode *tvp = ap->a_tvp;
	struct componentname *tcnp = ap->a_tcnp;
	struct componentname *fcnp = ap->a_fcnp;
	struct denode *ip, *xp, *dp, *zp;
	u_char toname[12], oldname[11];
	u_long from_diroffset, to_diroffset;
	u_char to_count;
	int doingdirectory = 0, newparent = 0;
	int error;
	u_long cn, pcl;
	daddr_t bn;
	struct msdosfsmount *pmp;
	struct direntry *dotdotp;
	struct buf *bp;

	pmp = VFSTOMSDOSFS(fdvp->v_mount);

#ifdef DIAGNOSTIC
	if ((tcnp->cn_flags & HASBUF) == 0 ||
	    (fcnp->cn_flags & HASBUF) == 0)
		panic("msdosfs_rename: no name");
#endif
	/*
	 * Check for cross-device rename.
	 */
	if (fvp->v_mount != tdvp->v_mount ||
	    (tvp && fvp->v_mount != tvp->v_mount)) {
		error = EXDEV;
abortit:
		if (tdvp == tvp)
			vrele(tdvp);
		else
			vput(tdvp);
		if (tvp)
			vput(tvp);
		vrele(fdvp);
		vrele(fvp);
		return (error);
	}

	/*
	 * If source and dest are the same, do nothing.
	 */
	if (tvp == fvp) {
		error = 0;
		goto abortit;
	}

	error = vn_lock(fvp, LK_EXCLUSIVE);
	if (error)
		goto abortit;
	dp = VTODE(fdvp);
	ip = VTODE(fvp);

	/*
	 * Be sure we are not renaming ".", "..", or an alias of ".". This
	 * leads to a crippled directory tree.  It's pretty tough to do a
	 * "ls" or "pwd" with the "." directory entry missing, and "cd .."
	 * doesn't work if the ".." entry is missing.
	 */
	if (ip->de_Attributes & ATTR_DIRECTORY) {
		/*
		 * Avoid ".", "..", and aliases of "." for obvious reasons.
		 */
		if ((fcnp->cn_namelen == 1 && fcnp->cn_nameptr[0] == '.') ||
		    dp == ip ||
		    (fcnp->cn_flags & ISDOTDOT) ||
		    (tcnp->cn_flags & ISDOTDOT) ||
		    (ip->de_flag & DE_RENAME)) {
			VOP_UNLOCK(fvp, 0);
			error = EINVAL;
			goto abortit;
		}
		ip->de_flag |= DE_RENAME;
		doingdirectory++;
	}

	/*
	 * When the target exists, both the directory
	 * and target vnodes are returned locked.
	 */
	dp = VTODE(tdvp);
	xp = tvp ? VTODE(tvp) : NULL;
	/*
	 * Remember direntry place to use for destination
	 */
	to_diroffset = dp->de_fndoffset;
	to_count = dp->de_fndcnt;

	/*
	 * If ".." must be changed (ie the directory gets a new
	 * parent) then the source directory must not be in the
	 * directory hierarchy above the target, as this would
	 * orphan everything below the source directory. Also
	 * the user must have write permission in the source so
	 * as to be able to change "..". We must repeat the call
	 * to namei, as the parent directory is unlocked by the
	 * call to doscheckpath().
	 */
	error = VOP_ACCESS(fvp, VWRITE, tcnp->cn_cred, tcnp->cn_thread);
	VOP_UNLOCK(fvp, 0);
	if (VTODE(fdvp)->de_StartCluster != VTODE(tdvp)->de_StartCluster)
		newparent = 1;
	if (doingdirectory && newparent) {
		if (error)	/* write access check above */
			goto bad;
		if (xp != NULL)
			vput(tvp);
		/*
		 * doscheckpath() vput()'s dp,
		 * so we have to do a relookup afterwards
		 */
		error = doscheckpath(ip, dp);
		if (error)
			goto out;
		if ((tcnp->cn_flags & SAVESTART) == 0)
			panic("msdosfs_rename: lost to startdir");
		error = relookup(tdvp, &tvp, tcnp);
		if (error)
			goto out;
		dp = VTODE(tdvp);
		xp = tvp ? VTODE(tvp) : NULL;
	}

	if (xp != NULL) {
		/*
		 * Target must be empty if a directory and have no links
		 * to it. Also, ensure source and target are compatible
		 * (both directories, or both not directories).
		 */
		if (xp->de_Attributes & ATTR_DIRECTORY) {
			if (!dosdirempty(xp)) {
				error = ENOTEMPTY;
				goto bad;
			}
			if (!doingdirectory) {
				error = ENOTDIR;
				goto bad;
			}
			cache_purge(tdvp);
		} else if (doingdirectory) {
			error = EISDIR;
			goto bad;
		}
		error = removede(dp, xp);
		if (error)
			goto bad;
		vput(tvp);
		xp = NULL;
	}

	/*
	 * Convert the filename in tcnp into a dos filename. We copy this
	 * into the denode and directory entry for the destination
	 * file/directory.
	 */
	error = uniqdosname(VTODE(tdvp), tcnp, toname);
	if (error)
		goto abortit;

	/*
	 * Since from wasn't locked at various places above,
	 * have to do a relookup here.
	 */
	fcnp->cn_flags &= ~MODMASK;
	fcnp->cn_flags |= LOCKPARENT | LOCKLEAF;
	if ((fcnp->cn_flags & SAVESTART) == 0)
		panic("msdosfs_rename: lost from startdir");
	if (!newparent)
		VOP_UNLOCK(tdvp, 0);
	if (relookup(fdvp, &fvp, fcnp) == 0)
		vrele(fdvp);
	if (fvp == NULL) {
		/*
		 * From name has disappeared.
		 */
		if (doingdirectory)
			panic("rename: lost dir entry");
		if (newparent)
			VOP_UNLOCK(tdvp, 0);
		vrele(tdvp);
		vrele(ap->a_fvp);
		return 0;
	}
	xp = VTODE(fvp);
	zp = VTODE(fdvp);
	from_diroffset = zp->de_fndoffset;

	/*
	 * Ensure that the directory entry still exists and has not
	 * changed till now. If the source is a file the entry may
	 * have been unlinked or renamed. In either case there is
	 * no further work to be done. If the source is a directory
	 * then it cannot have been rmdir'ed or renamed; this is
	 * prohibited by the DE_RENAME flag.
	 */
	if (xp != ip) {
		if (doingdirectory)
			panic("rename: lost dir entry");
		VOP_UNLOCK(fvp, 0);
		if (newparent)
			VOP_UNLOCK(fdvp, 0);
		vrele(ap->a_fvp);
		xp = NULL;
	} else {
		vrele(fvp);
		xp = NULL;

		/*
		 * First write a new entry in the destination
		 * directory and mark the entry in the source directory
		 * as deleted.  Then move the denode to the correct hash
		 * chain for its new location in the filesystem.  And, if
		 * we moved a directory, then update its .. entry to point
		 * to the new parent directory.
		 */
		memcpy(oldname, ip->de_Name, 11);
		memcpy(ip->de_Name, toname, 11);	/* update denode */
		dp->de_fndoffset = to_diroffset;
		dp->de_fndcnt = to_count;
		error = createde(ip, dp, (struct denode **)0, tcnp);
		if (error) {
			memcpy(ip->de_Name, oldname, 11);
			if (newparent)
				VOP_UNLOCK(fdvp, 0);
			VOP_UNLOCK(fvp, 0);
			goto bad;
		}
		/*
		 * If ip is for a directory, then its name should always
		 * be "." since it is for the directory entry in the
		 * directory itself (msdosfs_lookup() always translates
		 * to the "." entry so as to get a unique denode, except
		 * for the root directory there are different
		 * complications).  However, we just corrupted its name
		 * to pass the correct name to createde().  Undo this.
		 */
		if ((ip->de_Attributes & ATTR_DIRECTORY) != 0)
			memcpy(ip->de_Name, oldname, 11);
		ip->de_refcnt++;
		zp->de_fndoffset = from_diroffset;
		error = removede(zp, ip);
		if (error) {
			/* XXX should downgrade to ro here, fs is corrupt */
			if (newparent)
				VOP_UNLOCK(fdvp, 0);
			VOP_UNLOCK(fvp, 0);
			goto bad;
		}
		if (!doingdirectory) {
			error = pcbmap(dp, de_cluster(pmp, to_diroffset), 0,
				       &ip->de_dirclust, 0);
			if (error) {
				/* XXX should downgrade to ro here, fs is corrupt */
				if (newparent)
					VOP_UNLOCK(fdvp, 0);
				VOP_UNLOCK(fvp, 0);
				goto bad;
			}
			if (ip->de_dirclust == MSDOSFSROOT)
				ip->de_diroffset = to_diroffset;
			else
				ip->de_diroffset = to_diroffset & pmp->pm_crbomask;
		}
		reinsert(ip);
		if (newparent)
			VOP_UNLOCK(fdvp, 0);
	}

	/*
	 * If we moved a directory to a new parent directory, then we must
	 * fixup the ".." entry in the moved directory.
	 */
	if (doingdirectory && newparent) {
		cn = ip->de_StartCluster;
		if (cn == MSDOSFSROOT) {
			/* this should never happen */
			panic("msdosfs_rename(): updating .. in root directory?");
		} else
			bn = cntobn(pmp, cn);
		error = bread(pmp->pm_devvp, bn, pmp->pm_bpcluster,
			      NOCRED, &bp);
		if (error) {
			/* XXX should downgrade to ro here, fs is corrupt */
			VOP_UNLOCK(fvp, 0);
			goto bad;
		}
		dotdotp = (struct direntry *)bp->b_data + 1;
		pcl = dp->de_StartCluster;
		if (FAT32(pmp) && pcl == pmp->pm_rootdirblk)
			pcl = MSDOSFSROOT;
		putushort(dotdotp->deStartCluster, pcl);
		if (FAT32(pmp))
			putushort(dotdotp->deHighClust, pcl >> 16);
		if (DOINGASYNC(fvp))
			bdwrite(bp);
		else if ((error = bwrite(bp)) != 0) {
			/* XXX should downgrade to ro here, fs is corrupt */
			VOP_UNLOCK(fvp, 0);
			goto bad;
		}
	}

	/*
	 * The msdosfs lookup is case insensitive. Several aliases may
	 * be inserted for a single directory entry. As a consequnce,
	 * name cache purge done by lookup for fvp when DELETE op for
	 * namei is specified, might be not enough to expunge all
	 * namecache entries that were installed for this direntry.
	 */
	cache_purge(fvp);
	VOP_UNLOCK(fvp, 0);
bad:
	if (xp)
		vput(tvp);
	vput(tdvp);
out:
	ip->de_flag &= ~DE_RENAME;
	vrele(fdvp);
	vrele(fvp);
	return (error);

}