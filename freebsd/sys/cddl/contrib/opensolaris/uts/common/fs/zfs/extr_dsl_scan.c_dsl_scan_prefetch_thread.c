#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int vdev_children; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int uint64_t ;
struct TYPE_13__ {scalar_t__ spa_scrub_inflight; int /*<<< orphan*/  spa_scrub_lock; int /*<<< orphan*/  spa_scrub_io_cv; TYPE_2__* spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_14__ {int /*<<< orphan*/  spic_spc; int /*<<< orphan*/  spic_zb; int /*<<< orphan*/  spic_bp; } ;
typedef  TYPE_4__ scan_prefetch_issue_ctx_t ;
struct TYPE_15__ {scalar_t__ scn_maxinflight_bytes; int /*<<< orphan*/  scn_prefetch_queue; scalar_t__ scn_prefetch_stop; TYPE_1__* scn_dp; int /*<<< orphan*/  scn_zio_root; } ;
typedef  TYPE_5__ dsl_scan_t ;
typedef  int arc_flags_t ;
struct TYPE_11__ {TYPE_3__* dp_spa; } ;

/* Variables and functions */
 int ARC_FLAG_NOWAIT ; 
 int ARC_FLAG_PREFETCH ; 
 int ARC_FLAG_PRESCIENT_PREFETCH ; 
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  ASSERT0 (scalar_t__) ; 
 scalar_t__ BP_GET_PSIZE (int /*<<< orphan*/ *) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_SCAN_THREAD ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SCRUB ; 
 int /*<<< orphan*/  arc_read (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 TYPE_4__* avl_first (int /*<<< orphan*/ *) ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_scan_prefetch_cb ; 
 int /*<<< orphan*/  kmem_free (TYPE_4__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_prefetch_ctx_rele (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int zfs_top_maxinflight ; 

__attribute__((used)) static void
dsl_scan_prefetch_thread(void *arg)
{
	dsl_scan_t *scn = arg;
	spa_t *spa = scn->scn_dp->dp_spa;
	vdev_t *rvd = spa->spa_root_vdev;
	uint64_t maxinflight = rvd->vdev_children * zfs_top_maxinflight;
	scan_prefetch_issue_ctx_t *spic;

	/* loop until we are told to stop */
	while (!scn->scn_prefetch_stop) {
		arc_flags_t flags = ARC_FLAG_NOWAIT |
                    ARC_FLAG_PRESCIENT_PREFETCH | ARC_FLAG_PREFETCH;
		int zio_flags = ZIO_FLAG_CANFAIL | ZIO_FLAG_SCAN_THREAD;
		
		mutex_enter(&spa->spa_scrub_lock);

		/*
		 * Wait until we have an IO to issue and are not above our
		 * maximum in flight limit.
		 */
		while (!scn->scn_prefetch_stop &&
		    (avl_numnodes(&scn->scn_prefetch_queue) == 0 ||
		    spa->spa_scrub_inflight >= scn->scn_maxinflight_bytes)) {
			cv_wait(&spa->spa_scrub_io_cv, &spa->spa_scrub_lock);
		}

		/* recheck if we should stop since we waited for the cv */
		if (scn->scn_prefetch_stop) {
			mutex_exit(&spa->spa_scrub_lock);
			break;
		}

		/* remove the prefetch IO from the tree */
		spic = avl_first(&scn->scn_prefetch_queue);
		spa->spa_scrub_inflight += BP_GET_PSIZE(&spic->spic_bp);
		avl_remove(&scn->scn_prefetch_queue, spic);

		mutex_exit(&spa->spa_scrub_lock);

		/* issue the prefetch asynchronously */
		(void) arc_read(scn->scn_zio_root, scn->scn_dp->dp_spa,
		    &spic->spic_bp, dsl_scan_prefetch_cb, spic->spic_spc,
		    ZIO_PRIORITY_SCRUB, zio_flags, &flags, &spic->spic_zb);

		kmem_free(spic, sizeof (scan_prefetch_issue_ctx_t));
	}

	ASSERT(scn->scn_prefetch_stop);

	/* free any prefetches we didn't get to complete */
	mutex_enter(&spa->spa_scrub_lock);
	while ((spic = avl_first(&scn->scn_prefetch_queue)) != NULL) {
		avl_remove(&scn->scn_prefetch_queue, spic);
		scan_prefetch_ctx_rele(spic->spic_spc, scn);
		kmem_free(spic, sizeof (scan_prefetch_issue_ctx_t));
	}
	ASSERT0(avl_numnodes(&scn->scn_prefetch_queue));
	mutex_exit(&spa->spa_scrub_lock);
}