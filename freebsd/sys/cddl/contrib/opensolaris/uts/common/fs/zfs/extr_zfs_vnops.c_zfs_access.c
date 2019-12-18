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
struct TYPE_6__ {int /*<<< orphan*/ * z_zfsvfs; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  caller_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 TYPE_1__* VTOZ (int /*<<< orphan*/ *) ; 
 int V_ACE_MASK ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 int zfs_zaccess (TYPE_1__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zfs_zaccess_rwx (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_access(vnode_t *vp, int mode, int flag, cred_t *cr,
    caller_context_t *ct)
{
	znode_t *zp = VTOZ(vp);
	zfsvfs_t *zfsvfs = zp->z_zfsvfs;
	int error;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	if (flag & V_ACE_MASK)
		error = zfs_zaccess(zp, mode, flag, B_FALSE, cr);
	else
		error = zfs_zaccess_rwx(zp, mode, flag, cr);

	ZFS_EXIT(zfsvfs);
	return (error);
}