#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_1__ ;
typedef  struct TYPE_39__   TYPE_18__ ;

/* Type definitions */
struct TYPE_41__ {int zp_copies; size_t zp_checksum; int /*<<< orphan*/  zp_dedup; scalar_t__ zp_dedup_verify; } ;
struct TYPE_40__ {scalar_t__ io_txg; int io_flags; int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_abd; int /*<<< orphan*/  io_bookmark; int /*<<< orphan*/  io_priority; int /*<<< orphan*/  io_orig_size; int /*<<< orphan*/  io_orig_abd; int /*<<< orphan*/ * io_bp_override; void* io_pipeline; void* io_stage; TYPE_2__ io_prop; TYPE_5__* io_bp; int /*<<< orphan*/ * io_spa; } ;
typedef  TYPE_1__ zio_t ;
typedef  TYPE_2__ zio_prop_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  ddt_t ;
struct TYPE_42__ {scalar_t__ ddp_phys_birth; } ;
typedef  TYPE_3__ ddt_phys_t ;
struct TYPE_43__ {TYPE_1__** dde_lead_zio; TYPE_3__* dde_phys; } ;
typedef  TYPE_4__ ddt_entry_t ;
struct TYPE_44__ {scalar_t__ blk_birth; } ;
typedef  TYPE_5__ blkptr_t ;
struct TYPE_39__ {int ci_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BP_EQUAL (TYPE_5__*,int /*<<< orphan*/ *) ; 
 size_t BP_GET_CHECKSUM (TYPE_5__*) ; 
 int BP_GET_DEDUP (TYPE_5__*) ; 
 scalar_t__ BP_IS_HOLE (TYPE_5__*) ; 
 int /*<<< orphan*/  BP_SET_DEDUP (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_ZERO (TYPE_5__*) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 size_t DDT_PHYS_DITTO ; 
 int SPA_DVAS_PER_BP ; 
 int ZCHECKSUM_FLAG_DEDUP ; 
 int /*<<< orphan*/  ZIO_DDT_CHILD_FLAGS (TYPE_1__*) ; 
 int ZIO_FLAG_RAW ; 
 void* ZIO_STAGE_OPEN ; 
 void* ZIO_WRITE_PIPELINE ; 
 int /*<<< orphan*/  ddt_bp_fill (TYPE_3__*,TYPE_5__*,scalar_t__) ; 
 int ddt_ditto_copies_needed (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*) ; 
 int ddt_ditto_copies_present (TYPE_4__*) ; 
 int /*<<< orphan*/  ddt_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_exit (int /*<<< orphan*/ *) ; 
 TYPE_4__* ddt_lookup (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddt_phys_addref (TYPE_3__*) ; 
 int /*<<< orphan*/  ddt_phys_fill (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/ * ddt_select (int /*<<< orphan*/ *,TYPE_5__*) ; 
 size_t spa_dedup_checksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_add_child (TYPE_1__*,TYPE_1__*) ; 
 TYPE_18__* zio_checksum_table ; 
 int /*<<< orphan*/  zio_ddt_child_write_done ; 
 int /*<<< orphan*/ * zio_ddt_child_write_ready ; 
 scalar_t__ zio_ddt_collision (TYPE_1__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  zio_ddt_ditto_write_done ; 
 int /*<<< orphan*/  zio_nowait (TYPE_1__*) ; 
 int /*<<< orphan*/  zio_pop_transforms (TYPE_1__*) ; 
 int /*<<< orphan*/  zio_push_transform (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* zio_write (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zio_t *
zio_ddt_write(zio_t *zio)
{
	spa_t *spa = zio->io_spa;
	blkptr_t *bp = zio->io_bp;
	uint64_t txg = zio->io_txg;
	zio_prop_t *zp = &zio->io_prop;
	int p = zp->zp_copies;
	int ditto_copies;
	zio_t *cio = NULL;
	zio_t *dio = NULL;
	ddt_t *ddt = ddt_select(spa, bp);
	ddt_entry_t *dde;
	ddt_phys_t *ddp;

	ASSERT(BP_GET_DEDUP(bp));
	ASSERT(BP_GET_CHECKSUM(bp) == zp->zp_checksum);
	ASSERT(BP_IS_HOLE(bp) || zio->io_bp_override);
	ASSERT(!(zio->io_bp_override && (zio->io_flags & ZIO_FLAG_RAW)));

	ddt_enter(ddt);
	dde = ddt_lookup(ddt, bp, B_TRUE);
	ddp = &dde->dde_phys[p];

	if (zp->zp_dedup_verify && zio_ddt_collision(zio, ddt, dde)) {
		/*
		 * If we're using a weak checksum, upgrade to a strong checksum
		 * and try again.  If we're already using a strong checksum,
		 * we can't resolve it, so just convert to an ordinary write.
		 * (And automatically e-mail a paper to Nature?)
		 */
		if (!(zio_checksum_table[zp->zp_checksum].ci_flags &
		    ZCHECKSUM_FLAG_DEDUP)) {
			zp->zp_checksum = spa_dedup_checksum(spa);
			zio_pop_transforms(zio);
			zio->io_stage = ZIO_STAGE_OPEN;
			BP_ZERO(bp);
		} else {
			zp->zp_dedup = B_FALSE;
			BP_SET_DEDUP(bp, B_FALSE);
		}
		ASSERT(!BP_GET_DEDUP(bp));
		zio->io_pipeline = ZIO_WRITE_PIPELINE;
		ddt_exit(ddt);
		return (zio);
	}

	ditto_copies = ddt_ditto_copies_needed(ddt, dde, ddp);
	ASSERT(ditto_copies < SPA_DVAS_PER_BP);

	if (ditto_copies > ddt_ditto_copies_present(dde) &&
	    dde->dde_lead_zio[DDT_PHYS_DITTO] == NULL) {
		zio_prop_t czp = *zp;

		czp.zp_copies = ditto_copies;

		/*
		 * If we arrived here with an override bp, we won't have run
		 * the transform stack, so we won't have the data we need to
		 * generate a child i/o.  So, toss the override bp and restart.
		 * This is safe, because using the override bp is just an
		 * optimization; and it's rare, so the cost doesn't matter.
		 */
		if (zio->io_bp_override) {
			zio_pop_transforms(zio);
			zio->io_stage = ZIO_STAGE_OPEN;
			zio->io_pipeline = ZIO_WRITE_PIPELINE;
			zio->io_bp_override = NULL;
			BP_ZERO(bp);
			ddt_exit(ddt);
			return (zio);
		}

		dio = zio_write(zio, spa, txg, bp, zio->io_orig_abd,
		    zio->io_orig_size, zio->io_orig_size, &czp, NULL, NULL,
		    NULL, zio_ddt_ditto_write_done, dde, zio->io_priority,
		    ZIO_DDT_CHILD_FLAGS(zio), &zio->io_bookmark);

		zio_push_transform(dio, zio->io_abd, zio->io_size, 0, NULL);
		dde->dde_lead_zio[DDT_PHYS_DITTO] = dio;
	}

	if (ddp->ddp_phys_birth != 0 || dde->dde_lead_zio[p] != NULL) {
		if (ddp->ddp_phys_birth != 0)
			ddt_bp_fill(ddp, bp, txg);
		if (dde->dde_lead_zio[p] != NULL)
			zio_add_child(zio, dde->dde_lead_zio[p]);
		else
			ddt_phys_addref(ddp);
	} else if (zio->io_bp_override) {
		ASSERT(bp->blk_birth == txg);
		ASSERT(BP_EQUAL(bp, zio->io_bp_override));
		ddt_phys_fill(ddp, bp);
		ddt_phys_addref(ddp);
	} else {
		cio = zio_write(zio, spa, txg, bp, zio->io_orig_abd,
		    zio->io_orig_size, zio->io_orig_size, zp,
		    zio_ddt_child_write_ready, NULL, NULL,
		    zio_ddt_child_write_done, dde, zio->io_priority,
		    ZIO_DDT_CHILD_FLAGS(zio), &zio->io_bookmark);

		zio_push_transform(cio, zio->io_abd, zio->io_size, 0, NULL);
		dde->dde_lead_zio[p] = cio;
	}

	ddt_exit(ddt);

	if (cio)
		zio_nowait(cio);
	if (dio)
		zio_nowait(dio);

	return (zio);
}