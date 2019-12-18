#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * z_zfsvfs; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_12__ {int /*<<< orphan*/  v_type; int /*<<< orphan*/  v_vfsp; } ;
typedef  TYPE_2__ vnode_t ;
typedef  int ulong_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  caller_context_t ;

/* Variables and functions */
 int ACL_MAX_ENTRIES ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  VDIR ; 
 int /*<<< orphan*/  VFSFT_ACCESS_FILTER ; 
 int /*<<< orphan*/  VFSFT_SYSATTR_VIEWS ; 
 int /*<<< orphan*/  VREG ; 
 TYPE_1__* VTOZ (TYPE_2__*) ; 
 int ZEXISTS ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_LINK_MAX ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 int ZSHARED ; 
 int /*<<< orphan*/  ZTOV (TYPE_1__*) ; 
 int ZXATTR ; 
 int _ACL_ACE_ENABLED ; 
#define  _PC_ACCESS_FILTERING 139 
#define  _PC_ACL_ENABLED 138 
#define  _PC_ACL_EXTENDED 137 
#define  _PC_ACL_NFS4 136 
#define  _PC_ACL_PATH_MAX 135 
#define  _PC_FILESIZEBITS 134 
#define  _PC_LINK_MAX 133 
#define  _PC_MIN_HOLE_SIZE 132 
#define  _PC_SATTR_ENABLED 131 
#define  _PC_SATTR_EXISTS 130 
#define  _PC_TIMESTAMP_RESOLUTION 129 
#define  _PC_XATTR_EXISTS 128 
 int /*<<< orphan*/  vfs_has_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dirempty (TYPE_1__*) ; 
 int zfs_dirent_lookup (TYPE_1__*,char*,TYPE_1__**,int) ; 

__attribute__((used)) static int
zfs_pathconf(vnode_t *vp, int cmd, ulong_t *valp, cred_t *cr,
    caller_context_t *ct)
{
	znode_t		*zp, *xzp;
	zfsvfs_t	*zfsvfs;
	int		error;

	switch (cmd) {
	case _PC_LINK_MAX:
		*valp = MIN(LONG_MAX, ZFS_LINK_MAX);
		return (0);

	case _PC_FILESIZEBITS:
		*valp = 64;
		return (0);
#ifdef illumos
	case _PC_XATTR_EXISTS:
		zp = VTOZ(vp);
		zfsvfs = zp->z_zfsvfs;
		ZFS_ENTER(zfsvfs);
		ZFS_VERIFY_ZP(zp);
		*valp = 0;
		error = zfs_dirent_lookup(zp, "", &xzp,
		    ZXATTR | ZEXISTS | ZSHARED);
		if (error == 0) {
			if (!zfs_dirempty(xzp))
				*valp = 1;
			vrele(ZTOV(xzp));
		} else if (error == ENOENT) {
			/*
			 * If there aren't extended attributes, it's the
			 * same as having zero of them.
			 */
			error = 0;
		}
		ZFS_EXIT(zfsvfs);
		return (error);

	case _PC_SATTR_ENABLED:
	case _PC_SATTR_EXISTS:
		*valp = vfs_has_feature(vp->v_vfsp, VFSFT_SYSATTR_VIEWS) &&
		    (vp->v_type == VREG || vp->v_type == VDIR);
		return (0);

	case _PC_ACCESS_FILTERING:
		*valp = vfs_has_feature(vp->v_vfsp, VFSFT_ACCESS_FILTER) &&
		    vp->v_type == VDIR;
		return (0);

	case _PC_ACL_ENABLED:
		*valp = _ACL_ACE_ENABLED;
		return (0);
#endif	/* illumos */
	case _PC_MIN_HOLE_SIZE:
		*valp = (int)SPA_MINBLOCKSIZE;
		return (0);
#ifdef illumos
	case _PC_TIMESTAMP_RESOLUTION:
		/* nanosecond timestamp resolution */
		*valp = 1L;
		return (0);
#endif
	case _PC_ACL_EXTENDED:
		*valp = 0;
		return (0);

	case _PC_ACL_NFS4:
		*valp = 1;
		return (0);

	case _PC_ACL_PATH_MAX:
		*valp = ACL_MAX_ENTRIES;
		return (0);

	default:
		return (EOPNOTSUPP);
	}
}