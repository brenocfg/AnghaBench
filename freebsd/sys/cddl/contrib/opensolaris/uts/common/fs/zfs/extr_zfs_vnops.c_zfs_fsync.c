#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  z_id; TYPE_3__* z_zfsvfs; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_10__ {int /*<<< orphan*/  z_log; TYPE_1__* z_os; } ;
typedef  TYPE_3__ zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  caller_context_t ;
struct TYPE_8__ {scalar_t__ os_sync; } ;

/* Variables and functions */
 TYPE_2__* VTOZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_3__*) ; 
 scalar_t__ ZFS_SYNC_DISABLED ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_2__*) ; 
 int /*<<< orphan*/  tsd_set (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ zfs_fsync_sync_cnt ; 
 int /*<<< orphan*/  zfs_fsyncer_key ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_fsync(vnode_t *vp, int syncflag, cred_t *cr, caller_context_t *ct)
{
	znode_t	*zp = VTOZ(vp);
	zfsvfs_t *zfsvfs = zp->z_zfsvfs;

	(void) tsd_set(zfs_fsyncer_key, (void *)zfs_fsync_sync_cnt);

	if (zfsvfs->z_os->os_sync != ZFS_SYNC_DISABLED) {
		ZFS_ENTER(zfsvfs);
		ZFS_VERIFY_ZP(zp);
		zil_commit(zfsvfs->z_log, zp->z_id);
		ZFS_EXIT(zfsvfs);
	}
	return (0);
}