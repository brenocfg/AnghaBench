#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xbd_softc {int /*<<< orphan*/  xbd_io_lock; } ;
struct bio {int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_resid; int /*<<< orphan*/  bio_flags; int /*<<< orphan*/  bio_error; TYPE_1__* bio_disk; } ;
struct TYPE_2__ {struct xbd_softc* d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbd_enqueue_bio (struct xbd_softc*,struct bio*) ; 
 int /*<<< orphan*/  xbd_startio (struct xbd_softc*) ; 

__attribute__((used)) static void
xbd_strategy(struct bio *bp)
{
	struct xbd_softc *sc = bp->bio_disk->d_drv1;

	/* bogus disk? */
	if (sc == NULL) {
		bp->bio_error = EINVAL;
		bp->bio_flags |= BIO_ERROR;
		bp->bio_resid = bp->bio_bcount;
		biodone(bp);
		return;
	}

	/*
	 * Place it in the queue of disk activities for this disk
	 */
	mtx_lock(&sc->xbd_io_lock);

	xbd_enqueue_bio(sc, bp);
	xbd_startio(sc);

	mtx_unlock(&sc->xbd_io_lock);
	return;
}