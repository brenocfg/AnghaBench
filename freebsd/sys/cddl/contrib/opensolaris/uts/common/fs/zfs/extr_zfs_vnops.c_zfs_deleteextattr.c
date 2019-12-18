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
struct vop_deleteextattr_args {int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_name; int /*<<< orphan*/  a_attrnamespace; struct thread* a_td; } ;
struct vattr {int dummy; } ;
struct thread {int dummy; } ;
struct nameidata {int /*<<< orphan*/ * ni_dvp; int /*<<< orphan*/  ni_cnd; int /*<<< orphan*/ * ni_vp; } ;
typedef  int /*<<< orphan*/  attrname ;
struct TYPE_2__ {int /*<<< orphan*/ * z_zfsvfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE ; 
 int ENOATTR ; 
 int ENOENT ; 
 int LOCKLEAF ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  LOOKUP_XATTR ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATVP (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct thread*) ; 
 int NOFOLLOW ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* VTOZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VWRITE ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int extattr_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ ) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ *) ; 
 int zfs_create_attrname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int zfs_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ ) ; 

int
zfs_deleteextattr(struct vop_deleteextattr_args *ap)
/*
vop_deleteextattr {
	IN struct vnode *a_vp;
	IN int a_attrnamespace;
	IN const char *a_name;
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
	    LOOKUP_XATTR);
	if (error != 0) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	NDINIT_ATVP(&nd, DELETE, NOFOLLOW | LOCKPARENT | LOCKLEAF,
	    UIO_SYSSPACE, attrname, xvp, td);
	error = namei(&nd);
	vp = nd.ni_vp;
	if (error != 0) {
		ZFS_EXIT(zfsvfs);
		NDFREE(&nd, NDF_ONLY_PNBUF);
		if (error == ENOENT)
			error = ENOATTR;
		return (error);
	}

	error = VOP_REMOVE(nd.ni_dvp, vp, &nd.ni_cnd);
	NDFREE(&nd, NDF_ONLY_PNBUF);

	vput(nd.ni_dvp);
	if (vp == nd.ni_dvp)
		vrele(vp);
	else
		vput(vp);
	ZFS_EXIT(zfsvfs);

	return (error);
}