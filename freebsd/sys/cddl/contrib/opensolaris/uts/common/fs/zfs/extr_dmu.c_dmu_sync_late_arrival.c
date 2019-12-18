#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_14__ {int /*<<< orphan*/  zp_nopwrite; } ;
typedef  TYPE_2__ zio_prop_t ;
struct TYPE_15__ {TYPE_1__* zgd_db; int /*<<< orphan*/  zgd_bp; int /*<<< orphan*/  zgd_lwb; } ;
typedef  TYPE_3__ zgd_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct TYPE_16__ {int /*<<< orphan*/  os_spa; } ;
typedef  TYPE_4__ objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_sync_cb_t ;
struct TYPE_17__ {int /*<<< orphan*/ * dsa_tx; TYPE_3__* dsa_zgd; int /*<<< orphan*/ * dsa_done; int /*<<< orphan*/ * dsa_dr; } ;
typedef  TYPE_5__ dmu_sync_arg_t ;
struct TYPE_13__ {int /*<<< orphan*/  db_size; int /*<<< orphan*/  db_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  ZIO_FLAG_CANFAIL ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_WRITE ; 
 int /*<<< orphan*/  abd_get_from_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_sync_late_arrival_done ; 
 int /*<<< orphan*/  dmu_sync_late_arrival_ready ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dmu_tx_create (TYPE_4__*) ; 
 int /*<<< orphan*/  dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_space (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_lwb_add_txg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dmu_sync_late_arrival(zio_t *pio, objset_t *os, dmu_sync_cb_t *done, zgd_t *zgd,
    zio_prop_t *zp, zbookmark_phys_t *zb)
{
	dmu_sync_arg_t *dsa;
	dmu_tx_t *tx;

	tx = dmu_tx_create(os);
	dmu_tx_hold_space(tx, zgd->zgd_db->db_size);
	if (dmu_tx_assign(tx, TXG_WAIT) != 0) {
		dmu_tx_abort(tx);
		/* Make zl_get_data do txg_waited_synced() */
		return (SET_ERROR(EIO));
	}

	/*
	 * In order to prevent the zgd's lwb from being free'd prior to
	 * dmu_sync_late_arrival_done() being called, we have to ensure
	 * the lwb's "max txg" takes this tx's txg into account.
	 */
	zil_lwb_add_txg(zgd->zgd_lwb, dmu_tx_get_txg(tx));

	dsa = kmem_alloc(sizeof (dmu_sync_arg_t), KM_SLEEP);
	dsa->dsa_dr = NULL;
	dsa->dsa_done = done;
	dsa->dsa_zgd = zgd;
	dsa->dsa_tx = tx;

	/*
	 * Since we are currently syncing this txg, it's nontrivial to
	 * determine what BP to nopwrite against, so we disable nopwrite.
	 *
	 * When syncing, the db_blkptr is initially the BP of the previous
	 * txg.  We can not nopwrite against it because it will be changed
	 * (this is similar to the non-late-arrival case where the dbuf is
	 * dirty in a future txg).
	 *
	 * Then dbuf_write_ready() sets bp_blkptr to the location we will write.
	 * We can not nopwrite against it because although the BP will not
	 * (typically) be changed, the data has not yet been persisted to this
	 * location.
	 *
	 * Finally, when dbuf_write_done() is called, it is theoretically
	 * possible to always nopwrite, because the data that was written in
	 * this txg is the same data that we are trying to write.  However we
	 * would need to check that this dbuf is not dirty in any future
	 * txg's (as we do in the normal dmu_sync() path). For simplicity, we
	 * don't nopwrite in this case.
	 */
	zp->zp_nopwrite = B_FALSE;

	zio_nowait(zio_write(pio, os->os_spa, dmu_tx_get_txg(tx), zgd->zgd_bp,
	    abd_get_from_buf(zgd->zgd_db->db_data, zgd->zgd_db->db_size),
	    zgd->zgd_db->db_size, zgd->zgd_db->db_size, zp,
	    dmu_sync_late_arrival_ready, NULL, NULL, dmu_sync_late_arrival_done,
	    dsa, ZIO_PRIORITY_SYNC_WRITE, ZIO_FLAG_CANFAIL, zb));

	return (0);
}