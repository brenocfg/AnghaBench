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
struct md_s {int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  bio_queue; int /*<<< orphan*/  stat_mtx; int /*<<< orphan*/  devstat; } ;
struct bio {scalar_t__ bio_cmd; TYPE_2__* bio_to; } ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct md_s* softc; } ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  devstat_start_transaction_bio (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct md_s*) ; 

__attribute__((used)) static void
g_md_start(struct bio *bp)
{
	struct md_s *sc;

	sc = bp->bio_to->geom->softc;
	if ((bp->bio_cmd == BIO_READ) || (bp->bio_cmd == BIO_WRITE)) {
		mtx_lock(&sc->stat_mtx);
		devstat_start_transaction_bio(sc->devstat, bp);
		mtx_unlock(&sc->stat_mtx);
	}
	mtx_lock(&sc->queue_mtx);
	bioq_disksort(&sc->bio_queue, bp);
	wakeup(sc);
	mtx_unlock(&sc->queue_mtx);
}