#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int z_pflags; int z_mode; scalar_t__ z_links; scalar_t__ z_blksz; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/ * z_atime; int /*<<< orphan*/  z_gen; int /*<<< orphan*/  z_seq; int /*<<< orphan*/  z_size; int /*<<< orphan*/  z_id; TYPE_3__* z_zfsvfs; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_27__ {int /*<<< orphan*/  z_max_blksz; scalar_t__ z_use_fuids; TYPE_1__* z_vfs; } ;
typedef  TYPE_3__ zfsvfs_t ;
typedef  int /*<<< orphan*/  xvattr_t ;
struct TYPE_28__ {int xoa_archive; int xoa_readonly; int xoa_system; int xoa_hidden; int xoa_nounlink; int xoa_immutable; int xoa_appendonly; int xoa_nodump; int xoa_opaque; int xoa_av_quarantined; int xoa_av_modified; int xoa_reparse; int xoa_offline; int xoa_sparse; int /*<<< orphan*/  xoa_generation; } ;
typedef  TYPE_4__ xoptattr_t ;
struct TYPE_29__ {scalar_t__ v_type; int v_flag; int /*<<< orphan*/  v_rdev; } ;
typedef  TYPE_5__ vnode_t ;
struct TYPE_30__ {int va_mode; scalar_t__ va_nlink; int va_bytes; int /*<<< orphan*/  va_blksize; int /*<<< orphan*/  va_birthtime; int /*<<< orphan*/  va_ctime; int /*<<< orphan*/  va_mtime; int /*<<< orphan*/  va_atime; int /*<<< orphan*/  va_filerev; scalar_t__ va_flags; int /*<<< orphan*/  va_seq; int /*<<< orphan*/  va_rdev; int /*<<< orphan*/  va_size; int /*<<< orphan*/  va_nodeid; int /*<<< orphan*/  va_fsid; int /*<<< orphan*/  va_type; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_gid; } ;
typedef  TYPE_6__ vattr_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_longlong_t ;
typedef  int /*<<< orphan*/  sa_bulk_attr_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  caller_context_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_25__ {int /*<<< orphan*/  vfs_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_READ_ATTRIBUTES ; 
 int ATTR_NOACLCHECK ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  IFTOVT (int) ; 
 int /*<<< orphan*/  SA_ADD_BULK_ATTR (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SA_ZPL_CRTIME (TYPE_3__*) ; 
 int /*<<< orphan*/  SA_ZPL_CTIME (TYPE_3__*) ; 
 int /*<<< orphan*/  SA_ZPL_MTIME (TYPE_3__*) ; 
 int /*<<< orphan*/  SA_ZPL_RDEV (TYPE_3__*) ; 
 int S_IFMT ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 scalar_t__ VREG ; 
 int VROOT ; 
 TYPE_2__* VTOZ (TYPE_5__*) ; 
 int /*<<< orphan*/  XAT_APPENDONLY ; 
 int /*<<< orphan*/  XAT_ARCHIVE ; 
 int /*<<< orphan*/  XAT_AV_MODIFIED ; 
 int /*<<< orphan*/  XAT_AV_QUARANTINED ; 
 int /*<<< orphan*/  XAT_AV_SCANSTAMP ; 
 int /*<<< orphan*/  XAT_GEN ; 
 int /*<<< orphan*/  XAT_HIDDEN ; 
 int /*<<< orphan*/  XAT_IMMUTABLE ; 
 int /*<<< orphan*/  XAT_NODUMP ; 
 int /*<<< orphan*/  XAT_NOUNLINK ; 
 int /*<<< orphan*/  XAT_OFFLINE ; 
 int /*<<< orphan*/  XAT_OPAQUE ; 
 int /*<<< orphan*/  XAT_READONLY ; 
 int /*<<< orphan*/  XAT_REPARSE ; 
 int /*<<< orphan*/  XAT_SPARSE ; 
 int /*<<< orphan*/  XAT_SYSTEM ; 
 scalar_t__ XVA_ISSET_REQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVA_SET_RTN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ZFS_ACL_TRIVIAL ; 
 int ZFS_APPENDONLY ; 
 int ZFS_ARCHIVE ; 
 int ZFS_AV_MODIFIED ; 
 int ZFS_AV_QUARANTINED ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_3__*) ; 
 int ZFS_HIDDEN ; 
 int ZFS_IMMUTABLE ; 
 scalar_t__ ZFS_LINK_MAX ; 
 int ZFS_NODUMP ; 
 int ZFS_NOUNLINK ; 
 int ZFS_OFFLINE ; 
 int ZFS_OPAQUE ; 
 int ZFS_READONLY ; 
 int ZFS_REPARSE ; 
 int ZFS_SPARSE ; 
 int ZFS_SYSTEM ; 
 int /*<<< orphan*/  ZFS_TIME_DECODE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_2__*) ; 
 int /*<<< orphan*/  crgetuid (int /*<<< orphan*/ *) ; 
 int sa_bulk_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sa_object_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  vn_fsid (TYPE_5__*,TYPE_6__*) ; 
 TYPE_4__* xva_getxoptattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_cmpldev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_fuid_map_ids (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_sa_get_scanstamp (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_show_ctldir (TYPE_2__*) ; 
 int zfs_zaccess (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_getattr(vnode_t *vp, vattr_t *vap, int flags, cred_t *cr,
    caller_context_t *ct)
{
	znode_t *zp = VTOZ(vp);
	zfsvfs_t *zfsvfs = zp->z_zfsvfs;
	int	error = 0;
	uint32_t blksize;
	u_longlong_t nblocks;
	uint64_t mtime[2], ctime[2], crtime[2], rdev;
	xvattr_t *xvap = (xvattr_t *)vap;	/* vap may be an xvattr_t * */
	xoptattr_t *xoap = NULL;
	boolean_t skipaclchk = (flags & ATTR_NOACLCHECK) ? B_TRUE : B_FALSE;
	sa_bulk_attr_t bulk[4];
	int count = 0;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	zfs_fuid_map_ids(zp, cr, &vap->va_uid, &vap->va_gid);

	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_MTIME(zfsvfs), NULL, &mtime, 16);
	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_CTIME(zfsvfs), NULL, &ctime, 16);
	SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_CRTIME(zfsvfs), NULL, &crtime, 16);
	if (vp->v_type == VBLK || vp->v_type == VCHR)
		SA_ADD_BULK_ATTR(bulk, count, SA_ZPL_RDEV(zfsvfs), NULL,
		    &rdev, 8);

	if ((error = sa_bulk_lookup(zp->z_sa_hdl, bulk, count)) != 0) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	/*
	 * If ACL is trivial don't bother looking for ACE_READ_ATTRIBUTES.
	 * Also, if we are the owner don't bother, since owner should
	 * always be allowed to read basic attributes of file.
	 */
	if (!(zp->z_pflags & ZFS_ACL_TRIVIAL) &&
	    (vap->va_uid != crgetuid(cr))) {
		if (error = zfs_zaccess(zp, ACE_READ_ATTRIBUTES, 0,
		    skipaclchk, cr)) {
			ZFS_EXIT(zfsvfs);
			return (error);
		}
	}

	/*
	 * Return all attributes.  It's cheaper to provide the answer
	 * than to determine whether we were asked the question.
	 */

	vap->va_type = IFTOVT(zp->z_mode);
	vap->va_mode = zp->z_mode & ~S_IFMT;
#ifdef illumos
	vap->va_fsid = zp->z_zfsvfs->z_vfs->vfs_dev;
#else
	vn_fsid(vp, vap);
#endif
	vap->va_nodeid = zp->z_id;
	vap->va_nlink = zp->z_links;
	if ((vp->v_flag & VROOT) && zfs_show_ctldir(zp) &&
	    zp->z_links < ZFS_LINK_MAX)
		vap->va_nlink++;
	vap->va_size = zp->z_size;
#ifdef illumos
	vap->va_rdev = vp->v_rdev;
#else
	if (vp->v_type == VBLK || vp->v_type == VCHR)
		vap->va_rdev = zfs_cmpldev(rdev);
#endif
	vap->va_seq = zp->z_seq;
	vap->va_flags = 0;	/* FreeBSD: Reset chflags(2) flags. */
     	vap->va_filerev = zp->z_seq;

	/*
	 * Add in any requested optional attributes and the create time.
	 * Also set the corresponding bits in the returned attribute bitmap.
	 */
	if ((xoap = xva_getxoptattr(xvap)) != NULL && zfsvfs->z_use_fuids) {
		if (XVA_ISSET_REQ(xvap, XAT_ARCHIVE)) {
			xoap->xoa_archive =
			    ((zp->z_pflags & ZFS_ARCHIVE) != 0);
			XVA_SET_RTN(xvap, XAT_ARCHIVE);
		}

		if (XVA_ISSET_REQ(xvap, XAT_READONLY)) {
			xoap->xoa_readonly =
			    ((zp->z_pflags & ZFS_READONLY) != 0);
			XVA_SET_RTN(xvap, XAT_READONLY);
		}

		if (XVA_ISSET_REQ(xvap, XAT_SYSTEM)) {
			xoap->xoa_system =
			    ((zp->z_pflags & ZFS_SYSTEM) != 0);
			XVA_SET_RTN(xvap, XAT_SYSTEM);
		}

		if (XVA_ISSET_REQ(xvap, XAT_HIDDEN)) {
			xoap->xoa_hidden =
			    ((zp->z_pflags & ZFS_HIDDEN) != 0);
			XVA_SET_RTN(xvap, XAT_HIDDEN);
		}

		if (XVA_ISSET_REQ(xvap, XAT_NOUNLINK)) {
			xoap->xoa_nounlink =
			    ((zp->z_pflags & ZFS_NOUNLINK) != 0);
			XVA_SET_RTN(xvap, XAT_NOUNLINK);
		}

		if (XVA_ISSET_REQ(xvap, XAT_IMMUTABLE)) {
			xoap->xoa_immutable =
			    ((zp->z_pflags & ZFS_IMMUTABLE) != 0);
			XVA_SET_RTN(xvap, XAT_IMMUTABLE);
		}

		if (XVA_ISSET_REQ(xvap, XAT_APPENDONLY)) {
			xoap->xoa_appendonly =
			    ((zp->z_pflags & ZFS_APPENDONLY) != 0);
			XVA_SET_RTN(xvap, XAT_APPENDONLY);
		}

		if (XVA_ISSET_REQ(xvap, XAT_NODUMP)) {
			xoap->xoa_nodump =
			    ((zp->z_pflags & ZFS_NODUMP) != 0);
			XVA_SET_RTN(xvap, XAT_NODUMP);
		}

		if (XVA_ISSET_REQ(xvap, XAT_OPAQUE)) {
			xoap->xoa_opaque =
			    ((zp->z_pflags & ZFS_OPAQUE) != 0);
			XVA_SET_RTN(xvap, XAT_OPAQUE);
		}

		if (XVA_ISSET_REQ(xvap, XAT_AV_QUARANTINED)) {
			xoap->xoa_av_quarantined =
			    ((zp->z_pflags & ZFS_AV_QUARANTINED) != 0);
			XVA_SET_RTN(xvap, XAT_AV_QUARANTINED);
		}

		if (XVA_ISSET_REQ(xvap, XAT_AV_MODIFIED)) {
			xoap->xoa_av_modified =
			    ((zp->z_pflags & ZFS_AV_MODIFIED) != 0);
			XVA_SET_RTN(xvap, XAT_AV_MODIFIED);
		}

		if (XVA_ISSET_REQ(xvap, XAT_AV_SCANSTAMP) &&
		    vp->v_type == VREG) {
			zfs_sa_get_scanstamp(zp, xvap);
		}

		if (XVA_ISSET_REQ(xvap, XAT_REPARSE)) {
			xoap->xoa_reparse = ((zp->z_pflags & ZFS_REPARSE) != 0);
			XVA_SET_RTN(xvap, XAT_REPARSE);
		}
		if (XVA_ISSET_REQ(xvap, XAT_GEN)) {
			xoap->xoa_generation = zp->z_gen;
			XVA_SET_RTN(xvap, XAT_GEN);
		}

		if (XVA_ISSET_REQ(xvap, XAT_OFFLINE)) {
			xoap->xoa_offline =
			    ((zp->z_pflags & ZFS_OFFLINE) != 0);
			XVA_SET_RTN(xvap, XAT_OFFLINE);
		}

		if (XVA_ISSET_REQ(xvap, XAT_SPARSE)) {
			xoap->xoa_sparse =
			    ((zp->z_pflags & ZFS_SPARSE) != 0);
			XVA_SET_RTN(xvap, XAT_SPARSE);
		}
	}

	ZFS_TIME_DECODE(&vap->va_atime, zp->z_atime);
	ZFS_TIME_DECODE(&vap->va_mtime, mtime);
	ZFS_TIME_DECODE(&vap->va_ctime, ctime);
	ZFS_TIME_DECODE(&vap->va_birthtime, crtime);


	sa_object_size(zp->z_sa_hdl, &blksize, &nblocks);
	vap->va_blksize = blksize;
	vap->va_bytes = nblocks << 9;	/* nblocks * 512 */

	if (zp->z_blksz == 0) {
		/*
		 * Block size hasn't been set; suggest maximal I/O transfers.
		 */
		vap->va_blksize = zfsvfs->z_max_blksz;
	}

	ZFS_EXIT(zfsvfs);
	return (0);
}