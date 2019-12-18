#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ z_sync_cnt; int /*<<< orphan*/  z_id; scalar_t__ z_unlinked; } ;
typedef  TYPE_1__ znode_t ;
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_15__ {void* z_fuid_group; void* z_fuid_owner; scalar_t__ z_domain_str_sz; } ;
typedef  TYPE_2__ zfs_fuid_info_t ;
struct TYPE_16__ {int /*<<< orphan*/  xva_mapsize; } ;
typedef  TYPE_3__ xvattr_t ;
struct TYPE_17__ {int va_mask; int /*<<< orphan*/  va_mtime; int /*<<< orphan*/  va_atime; scalar_t__ va_size; scalar_t__ va_gid; scalar_t__ va_uid; scalar_t__ va_mode; } ;
typedef  TYPE_4__ vattr_t ;
typedef  int uint_t ;
typedef  void* uint64_t ;
struct TYPE_18__ {int /*<<< orphan*/  lr_mtime; int /*<<< orphan*/  lr_atime; void* lr_size; void* lr_gid; void* lr_uid; void* lr_mode; void* lr_mask; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_5__ lr_setattr_t ;
typedef  int /*<<< orphan*/  lr_attr_t ;
struct TYPE_19__ {int itx_sync; int /*<<< orphan*/  itx_lr; } ;
typedef  TYPE_6__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  void* caddr_t ;

/* Variables and functions */
 int AT_GID ; 
 int AT_UID ; 
 int AT_XVATTR ; 
 scalar_t__ IS_EPHEMERAL (scalar_t__) ; 
 int /*<<< orphan*/  ZFS_TIME_ENCODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ZIL_XVAT_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_log_fuid_domains (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  zfs_log_xvattr (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zil_itx_assign (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *) ; 
 TYPE_6__* zil_itx_create (int,size_t) ; 
 scalar_t__ zil_replaying (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
zfs_log_setattr(zilog_t *zilog, dmu_tx_t *tx, int txtype,
    znode_t *zp, vattr_t *vap, uint_t mask_applied, zfs_fuid_info_t *fuidp)
{
	itx_t		*itx;
	lr_setattr_t	*lr;
	xvattr_t	*xvap = (xvattr_t *)vap;
	size_t		recsize = sizeof (lr_setattr_t);
	void		*start;

	if (zil_replaying(zilog, tx) || zp->z_unlinked)
		return;

	/*
	 * If XVATTR set, then log record size needs to allow
	 * for lr_attr_t + xvattr mask, mapsize and create time
	 * plus actual attribute values
	 */
	if (vap->va_mask & AT_XVATTR)
		recsize = sizeof (*lr) + ZIL_XVAT_SIZE(xvap->xva_mapsize);

	if (fuidp)
		recsize += fuidp->z_domain_str_sz;

	itx = zil_itx_create(txtype, recsize);
	lr = (lr_setattr_t *)&itx->itx_lr;
	lr->lr_foid = zp->z_id;
	lr->lr_mask = (uint64_t)mask_applied;
	lr->lr_mode = (uint64_t)vap->va_mode;
	if ((mask_applied & AT_UID) && IS_EPHEMERAL(vap->va_uid))
		lr->lr_uid = fuidp->z_fuid_owner;
	else
		lr->lr_uid = (uint64_t)vap->va_uid;

	if ((mask_applied & AT_GID) && IS_EPHEMERAL(vap->va_gid))
		lr->lr_gid = fuidp->z_fuid_group;
	else
		lr->lr_gid = (uint64_t)vap->va_gid;

	lr->lr_size = (uint64_t)vap->va_size;
	ZFS_TIME_ENCODE(&vap->va_atime, lr->lr_atime);
	ZFS_TIME_ENCODE(&vap->va_mtime, lr->lr_mtime);
	start = (lr_setattr_t *)(lr + 1);
	if (vap->va_mask & AT_XVATTR) {
		zfs_log_xvattr((lr_attr_t *)start, xvap);
		start = (caddr_t)start + ZIL_XVAT_SIZE(xvap->xva_mapsize);
	}

	/*
	 * Now stick on domain information if any on end
	 */

	if (fuidp)
		(void) zfs_log_fuid_domains(fuidp, start);

	itx->itx_sync = (zp->z_sync_cnt != 0);
	zil_itx_assign(zilog, itx, tx);
}