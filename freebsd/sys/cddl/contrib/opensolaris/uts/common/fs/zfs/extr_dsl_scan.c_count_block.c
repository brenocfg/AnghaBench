#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  zb_ditto_3_of_3_samevdev; int /*<<< orphan*/  zb_ditto_2_of_3_samevdev; int /*<<< orphan*/  zb_ditto_2_of_2_samevdev; int /*<<< orphan*/  zb_gangs; int /*<<< orphan*/  zb_psize; int /*<<< orphan*/  zb_lsize; int /*<<< orphan*/  zb_asize; int /*<<< orphan*/  zb_count; } ;
typedef  TYPE_3__ zfs_blkstat_t ;
struct TYPE_20__ {int /*<<< orphan*/  zab_lock; TYPE_3__** zab_type; } ;
typedef  TYPE_4__ zfs_all_blkstats_t ;
struct TYPE_21__ {TYPE_2__* scn_dp; } ;
typedef  TYPE_5__ dsl_scan_t ;
struct TYPE_22__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_6__ blkptr_t ;
struct TYPE_18__ {TYPE_1__* dp_spa; } ;
struct TYPE_17__ {int /*<<< orphan*/  spa_scan_pass_issued; } ;

/* Variables and functions */
 scalar_t__ BP_COUNT_GANG (TYPE_6__ const*) ; 
 scalar_t__ BP_GET_ASIZE (TYPE_6__ const*) ; 
 int BP_GET_LEVEL (TYPE_6__ const*) ; 
 scalar_t__ BP_GET_LSIZE (TYPE_6__ const*) ; 
 int BP_GET_NDVAS (TYPE_6__ const*) ; 
 scalar_t__ BP_GET_PSIZE (TYPE_6__ const*) ; 
 int BP_GET_TYPE (TYPE_6__ const*) ; 
 int DMU_OT_NEWTYPE ; 
 int DMU_OT_OTHER ; 
 int DMU_OT_TOTAL ; 
 int DN_MAX_LEVELS ; 
 int /*<<< orphan*/  DVA_GET_ASIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
count_block(dsl_scan_t *scn, zfs_all_blkstats_t *zab, const blkptr_t *bp)
{
	int i;

	/* update the spa's stats on how many bytes we have issued */
	for (i = 0; i < BP_GET_NDVAS(bp); i++) {
		atomic_add_64(&scn->scn_dp->dp_spa->spa_scan_pass_issued,
		    DVA_GET_ASIZE(&bp->blk_dva[i]));
	}

	/*
	 * If we resume after a reboot, zab will be NULL; don't record
	 * incomplete stats in that case.
	 */
	if (zab == NULL)
		return;

	mutex_enter(&zab->zab_lock);

	for (i = 0; i < 4; i++) {
		int l = (i < 2) ? BP_GET_LEVEL(bp) : DN_MAX_LEVELS;
		int t = (i & 1) ? BP_GET_TYPE(bp) : DMU_OT_TOTAL;
		if (t & DMU_OT_NEWTYPE)
			t = DMU_OT_OTHER;
		zfs_blkstat_t *zb = &zab->zab_type[l][t];
		int equal;

		zb->zb_count++;
		zb->zb_asize += BP_GET_ASIZE(bp);
		zb->zb_lsize += BP_GET_LSIZE(bp);
		zb->zb_psize += BP_GET_PSIZE(bp);
		zb->zb_gangs += BP_COUNT_GANG(bp);

		switch (BP_GET_NDVAS(bp)) {
		case 2:
			if (DVA_GET_VDEV(&bp->blk_dva[0]) ==
			    DVA_GET_VDEV(&bp->blk_dva[1]))
				zb->zb_ditto_2_of_2_samevdev++;
			break;
		case 3:
			equal = (DVA_GET_VDEV(&bp->blk_dva[0]) ==
			    DVA_GET_VDEV(&bp->blk_dva[1])) +
			    (DVA_GET_VDEV(&bp->blk_dva[0]) ==
			    DVA_GET_VDEV(&bp->blk_dva[2])) +
			    (DVA_GET_VDEV(&bp->blk_dva[1]) ==
			    DVA_GET_VDEV(&bp->blk_dva[2]));
			if (equal == 1)
				zb->zb_ditto_2_of_3_samevdev++;
			else if (equal == 3)
				zb->zb_ditto_3_of_3_samevdev++;
			break;
		}
	}

	mutex_exit(&zab->zab_lock);
}