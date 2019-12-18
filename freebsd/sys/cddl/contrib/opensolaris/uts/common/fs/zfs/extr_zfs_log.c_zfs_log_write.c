#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ z_sync_cnt; TYPE_1__* z_zfsvfs; int /*<<< orphan*/  z_id; scalar_t__ z_unlinked; scalar_t__ z_blksz; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_16__ {scalar_t__ zl_logbias; int /*<<< orphan*/  zl_spa; } ;
typedef  TYPE_3__ zilog_t ;
typedef  scalar_t__ uint32_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  offset_t ;
struct TYPE_17__ {int lr_length; int /*<<< orphan*/  lr_blkptr; scalar_t__ lr_blkoff; int /*<<< orphan*/  lr_offset; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_4__ lr_write_t ;
typedef  scalar_t__ itx_wr_state_t ;
struct TYPE_18__ {int /*<<< orphan*/  itx_sync; TYPE_1__* itx_private; scalar_t__ itx_wr_state; int /*<<< orphan*/  itx_lr; } ;
typedef  TYPE_5__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_14__ {int /*<<< orphan*/  z_os; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DMU_READ_NO_PREFETCH ; 
 int FDSYNC ; 
 int FSYNC ; 
 int MIN (scalar_t__,int) ; 
 scalar_t__ P2PHASE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ WR_COPIED ; 
 scalar_t__ WR_INDIRECT ; 
 scalar_t__ WR_NEED_COPY ; 
 scalar_t__ ZFS_LOGBIAS_THROUGHPUT ; 
 int ZIL_MAX_COPIED_DATA ; 
 scalar_t__ dmu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_has_slogs (int /*<<< orphan*/ ) ; 
 scalar_t__ tsd_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_set (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  zfs_fsyncer_key ; 
 int zfs_immediate_write_sz ; 
 int /*<<< orphan*/  zil_itx_assign (TYPE_3__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* zil_itx_create (int,int) ; 
 int /*<<< orphan*/  zil_itx_destroy (TYPE_5__*) ; 
 scalar_t__ zil_replaying (TYPE_3__*,int /*<<< orphan*/ *) ; 

void
zfs_log_write(zilog_t *zilog, dmu_tx_t *tx, int txtype,
    znode_t *zp, offset_t off, ssize_t resid, int ioflag)
{
	uint32_t blocksize = zp->z_blksz;
	itx_wr_state_t write_state;
	uintptr_t fsync_cnt;

	if (zil_replaying(zilog, tx) || zp->z_unlinked)
		return;

	if (zilog->zl_logbias == ZFS_LOGBIAS_THROUGHPUT)
		write_state = WR_INDIRECT;
	else if (!spa_has_slogs(zilog->zl_spa) &&
	    resid >= zfs_immediate_write_sz)
		write_state = WR_INDIRECT;
	else if (ioflag & (FSYNC | FDSYNC))
		write_state = WR_COPIED;
	else
		write_state = WR_NEED_COPY;

	if ((fsync_cnt = (uintptr_t)tsd_get(zfs_fsyncer_key)) != 0) {
		(void) tsd_set(zfs_fsyncer_key, (void *)(fsync_cnt - 1));
	}

	while (resid) {
		itx_t *itx;
		lr_write_t *lr;
		itx_wr_state_t wr_state = write_state;
		ssize_t len = resid;

		if (wr_state == WR_COPIED && resid > ZIL_MAX_COPIED_DATA)
			wr_state = WR_NEED_COPY;
		else if (wr_state == WR_INDIRECT)
			len = MIN(blocksize - P2PHASE(off, blocksize), resid);

		itx = zil_itx_create(txtype, sizeof (*lr) +
		    (wr_state == WR_COPIED ? len : 0));
		lr = (lr_write_t *)&itx->itx_lr;
		if (wr_state == WR_COPIED && dmu_read(zp->z_zfsvfs->z_os,
		    zp->z_id, off, len, lr + 1, DMU_READ_NO_PREFETCH) != 0) {
			zil_itx_destroy(itx);
			itx = zil_itx_create(txtype, sizeof (*lr));
			lr = (lr_write_t *)&itx->itx_lr;
			wr_state = WR_NEED_COPY;
		}

		itx->itx_wr_state = wr_state;
		lr->lr_foid = zp->z_id;
		lr->lr_offset = off;
		lr->lr_length = len;
		lr->lr_blkoff = 0;
		BP_ZERO(&lr->lr_blkptr);

		itx->itx_private = zp->z_zfsvfs;

		if (!(ioflag & (FSYNC | FDSYNC)) && (zp->z_sync_cnt == 0) &&
		    (fsync_cnt == 0))
			itx->itx_sync = B_FALSE;

		zil_itx_assign(zilog, itx, tx);

		off += len;
		resid -= len;
	}
}