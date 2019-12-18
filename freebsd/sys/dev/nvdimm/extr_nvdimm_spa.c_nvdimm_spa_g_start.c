#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_spa {int /*<<< orphan*/  spa_g_mtx; int /*<<< orphan*/  spa_g_queue; int /*<<< orphan*/  spa_g_stat_mtx; int /*<<< orphan*/  spa_g_devstat; } ;
struct bio {scalar_t__ bio_cmd; TYPE_2__* bio_to; } ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_spa* softc; } ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  devstat_start_transaction_bio (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvdimm_spa_g_start(struct bio *bp)
{
	struct g_spa *sc;

	sc = bp->bio_to->geom->softc;
	if (bp->bio_cmd == BIO_READ || bp->bio_cmd == BIO_WRITE) {
		mtx_lock(&sc->spa_g_stat_mtx);
		devstat_start_transaction_bio(sc->spa_g_devstat, bp);
		mtx_unlock(&sc->spa_g_stat_mtx);
	}
	mtx_lock(&sc->spa_g_mtx);
	bioq_disksort(&sc->spa_g_queue, bp);
	wakeup(&sc->spa_g_queue);
	mtx_unlock(&sc->spa_g_mtx);
}