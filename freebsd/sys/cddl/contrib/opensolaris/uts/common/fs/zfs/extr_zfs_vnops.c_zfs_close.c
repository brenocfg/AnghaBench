#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int z_pflags; scalar_t__ z_size; TYPE_2__* z_zfsvfs; int /*<<< orphan*/  z_sync_cnt; } ;
typedef  TYPE_1__ znode_t ;
struct TYPE_11__ {scalar_t__ z_vscan; } ;
typedef  TYPE_2__ zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  offset_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  caller_context_t ;
struct TYPE_12__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int FDSYNC ; 
 int FSYNC ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ VREG ; 
 TYPE_1__* VTOZ (int /*<<< orphan*/ *) ; 
 int ZFS_AV_QUARANTINED ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_2__*) ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_1__*) ; 
 TYPE_4__* ZTOV (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_dec_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanlocks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanshares (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddi_get_pid () ; 
 scalar_t__ fs_vscan (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_has_ctldir (TYPE_1__*) ; 

__attribute__((used)) static int
zfs_close(vnode_t *vp, int flag, int count, offset_t offset, cred_t *cr,
    caller_context_t *ct)
{
	znode_t	*zp = VTOZ(vp);
	zfsvfs_t *zfsvfs = zp->z_zfsvfs;

	/*
	 * Clean up any locks held by this process on the vp.
	 */
	cleanlocks(vp, ddi_get_pid(), 0);
	cleanshares(vp, ddi_get_pid());

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	/* Decrement the synchronous opens in the znode */
	if ((flag & (FSYNC | FDSYNC)) && (count == 1))
		atomic_dec_32(&zp->z_sync_cnt);

	if (!zfs_has_ctldir(zp) && zp->z_zfsvfs->z_vscan &&
	    ZTOV(zp)->v_type == VREG &&
	    !(zp->z_pflags & ZFS_AV_QUARANTINED) && zp->z_size > 0)
		VERIFY(fs_vscan(vp, cr, 1) == 0);

	ZFS_EXIT(zfsvfs);
	return (0);
}