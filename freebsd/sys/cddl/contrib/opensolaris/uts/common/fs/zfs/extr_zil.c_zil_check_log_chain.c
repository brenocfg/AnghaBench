#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {TYPE_3__* zl_header; TYPE_2__* zl_spa; } ;
typedef  TYPE_4__ zilog_t ;
struct TYPE_26__ {scalar_t__ zh_claim_txg; } ;
typedef  TYPE_5__ zil_header_t ;
struct TYPE_27__ {scalar_t__ vdev_islog; } ;
typedef  TYPE_6__ vdev_t ;
struct TYPE_28__ {int /*<<< orphan*/  os_spa; } ;
typedef  TYPE_7__ objset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_29__ {scalar_t__ ds_object; } ;
typedef  TYPE_8__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_30__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_9__ blkptr_t ;
struct TYPE_24__ {scalar_t__ zh_claim_txg; int /*<<< orphan*/  zh_log; } ;
struct TYPE_22__ {scalar_t__ ub_checkpoint_txg; } ;
struct TYPE_23__ {TYPE_1__ spa_uberblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_IS_HOLE (TYPE_9__*) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  CE_WARN ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/ *) ; 
 int ECKSUM ; 
 int ENOENT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,unsigned long long,int) ; 
 int dmu_objset_from_ds (TYPE_8__*,TYPE_7__**) ; 
 TYPE_4__* dmu_objset_zil (TYPE_7__*) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long long spa_min_claim_txg (int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_is_dead (TYPE_6__*) ; 
 int /*<<< orphan*/  vdev_log_state_valid (TYPE_6__*) ; 
 TYPE_6__* vdev_lookup_top (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_claim_log_block ; 
 int /*<<< orphan*/  zil_claim_log_record ; 
 TYPE_5__* zil_header_in_syncing_context (TYPE_4__*) ; 
 int zil_parse (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned long long) ; 

int
zil_check_log_chain(dsl_pool_t *dp, dsl_dataset_t *ds, void *tx)
{
	zilog_t *zilog;
	objset_t *os;
	blkptr_t *bp;
	int error;

	ASSERT(tx == NULL);

	error = dmu_objset_from_ds(ds, &os);
	if (error != 0) {
		cmn_err(CE_WARN, "can't open objset %llu, error %d",
		    (unsigned long long)ds->ds_object, error);
		return (0);
	}

	zilog = dmu_objset_zil(os);
	bp = (blkptr_t *)&zilog->zl_header->zh_log;

	if (!BP_IS_HOLE(bp)) {
		vdev_t *vd;
		boolean_t valid = B_TRUE;

		/*
		 * Check the first block and determine if it's on a log device
		 * which may have been removed or faulted prior to loading this
		 * pool.  If so, there's no point in checking the rest of the
		 * log as its content should have already been synced to the
		 * pool.
		 */
		spa_config_enter(os->os_spa, SCL_STATE, FTAG, RW_READER);
		vd = vdev_lookup_top(os->os_spa, DVA_GET_VDEV(&bp->blk_dva[0]));
		if (vd->vdev_islog && vdev_is_dead(vd))
			valid = vdev_log_state_valid(vd);
		spa_config_exit(os->os_spa, SCL_STATE, FTAG);

		if (!valid)
			return (0);

		/*
		 * Check whether the current uberblock is checkpointed (e.g.
		 * we are rewinding) and whether the current header has been
		 * claimed or not. If it hasn't then skip verifying it. We
		 * do this because its ZIL blocks may be part of the pool's
		 * state before the rewind, which is no longer valid.
		 */
		zil_header_t *zh = zil_header_in_syncing_context(zilog);
		if (zilog->zl_spa->spa_uberblock.ub_checkpoint_txg != 0 &&
		    zh->zh_claim_txg == 0)
			return (0);
	}

	/*
	 * Because tx == NULL, zil_claim_log_block() will not actually claim
	 * any blocks, but just determine whether it is possible to do so.
	 * In addition to checking the log chain, zil_claim_log_block()
	 * will invoke zio_claim() with a done func of spa_claim_notify(),
	 * which will update spa_max_claim_txg.  See spa_load() for details.
	 */
	error = zil_parse(zilog, zil_claim_log_block, zil_claim_log_record, tx,
	    zilog->zl_header->zh_claim_txg ? -1ULL :
	    spa_min_claim_txg(os->os_spa));

	return ((error == ECKSUM || error == ENOENT) ? 0 : error);
}