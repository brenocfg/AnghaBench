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
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;
struct vop_setextattr_args {int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_uio; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_name; int /*<<< orphan*/  a_attrnamespace; struct thread* a_td; } ;
struct vattr {scalar_t__ va_size; } ;
struct thread {int dummy; } ;
struct nameidata {int /*<<< orphan*/ * ni_vp; } ;
typedef  int /*<<< orphan*/  attrname ;
struct TYPE_2__ {int /*<<< orphan*/ * z_zfsvfs; } ;

/* Variables and functions */
 int CREATE_XATTR_DIR ; 
 int FFLAGS (int) ; 
 int /*<<< orphan*/  IO_UNIT ; 
 int /*<<< orphan*/  LOOKUP ; 
 int LOOKUP_XATTR ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATVP (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct thread*) ; 
 int /*<<< orphan*/  NOFOLLOW ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  VATTR_NULL (struct vattr*) ; 
 int VOP_SETATTR (int /*<<< orphan*/ *,struct vattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* VTOZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VWRITE ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int extattr_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_close (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct thread*) ; 
 int vn_open_cred (struct nameidata*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_create_attrname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int zfs_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int) ; 

__attribute__((used)) static int
zfs_setextattr(struct vop_setextattr_args *ap)
/*
vop_setextattr {
	IN struct vnode *a_vp;
	IN int a_attrnamespace;
	IN const char *a_name;
	INOUT struct uio *a_uio;
	IN struct ucred *a_cred;
	IN struct thread *a_td;
};
*/
{
	zfsvfs_t *zfsvfs = VTOZ(ap->a_vp)->z_zfsvfs;
	struct thread *td = ap->a_td;
	struct nameidata nd;
	char attrname[255];
	struct vattr va;
	vnode_t *xvp = NULL, *vp;
	int error, flags;

	error = extattr_check_cred(ap->a_vp, ap->a_attrnamespace,
	    ap->a_cred, ap->a_td, VWRITE);
	if (error != 0)
		return (error);

	error = zfs_create_attrname(ap->a_attrnamespace, ap->a_name, attrname,
	    sizeof(attrname));
	if (error != 0)
		return (error);

	ZFS_ENTER(zfsvfs);

	error = zfs_lookup(ap->a_vp, NULL, &xvp, NULL, 0, ap->a_cred, td,
	    LOOKUP_XATTR | CREATE_XATTR_DIR);
	if (error != 0) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	flags = FFLAGS(O_WRONLY | O_CREAT);
	NDINIT_ATVP(&nd, LOOKUP, NOFOLLOW, UIO_SYSSPACE, attrname,
	    xvp, td);
	error = vn_open_cred(&nd, &flags, 0600, 0, ap->a_cred, NULL);
	vp = nd.ni_vp;
	NDFREE(&nd, NDF_ONLY_PNBUF);
	if (error != 0) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	VATTR_NULL(&va);
	va.va_size = 0;
	error = VOP_SETATTR(vp, &va, ap->a_cred);
	if (error == 0)
		VOP_WRITE(vp, ap->a_uio, IO_UNIT, ap->a_cred);

	VOP_UNLOCK(vp, 0);
	vn_close(vp, flags, ap->a_cred, td);
	ZFS_EXIT(zfsvfs);

	return (error);
}