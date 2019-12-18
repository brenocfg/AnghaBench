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
struct TYPE_6__ {int /*<<< orphan*/  z_sa_hdl; scalar_t__ z_is_sa; int /*<<< orphan*/ * z_zfsvfs; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  caller_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  SA_ZPL_SYMLINK (int /*<<< orphan*/ *) ; 
 TYPE_1__* VTOZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_ACCESSTIME_STAMP (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 int sa_lookup_uio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_sa_readlink (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_readlink(vnode_t *vp, uio_t *uio, cred_t *cr, caller_context_t *ct)
{
	znode_t		*zp = VTOZ(vp);
	zfsvfs_t	*zfsvfs = zp->z_zfsvfs;
	int		error;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	if (zp->z_is_sa)
		error = sa_lookup_uio(zp->z_sa_hdl,
		    SA_ZPL_SYMLINK(zfsvfs), uio);
	else
		error = zfs_sa_readlink(zp, uio);

	ZFS_ACCESSTIME_STAMP(zfsvfs, zp);

	ZFS_EXIT(zfsvfs);
	return (error);
}