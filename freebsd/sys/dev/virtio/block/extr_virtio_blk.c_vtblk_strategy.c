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
struct vtblk_softc {int vtblk_flags; int /*<<< orphan*/  vtblk_bioq; } ;
struct bio {scalar_t__ bio_cmd; TYPE_1__* bio_disk; } ;
struct TYPE_2__ {struct vtblk_softc* d_drv1; } ;

/* Variables and functions */
 scalar_t__ BIO_FLUSH ; 
 scalar_t__ BIO_WRITE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EROFS ; 
 int VTBLK_FLAG_DETACH ; 
 int VTBLK_FLAG_READONLY ; 
 int /*<<< orphan*/  VTBLK_LOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_UNLOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  vtblk_bio_done (struct vtblk_softc*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_startio (struct vtblk_softc*) ; 

__attribute__((used)) static void
vtblk_strategy(struct bio *bp)
{
	struct vtblk_softc *sc;

	if ((sc = bp->bio_disk->d_drv1) == NULL) {
		vtblk_bio_done(NULL, bp, EINVAL);
		return;
	}

	/*
	 * Fail any write if RO. Unfortunately, there does not seem to
	 * be a better way to report our readonly'ness to GEOM above.
	 */
	if (sc->vtblk_flags & VTBLK_FLAG_READONLY &&
	    (bp->bio_cmd == BIO_WRITE || bp->bio_cmd == BIO_FLUSH)) {
		vtblk_bio_done(sc, bp, EROFS);
		return;
	}

	VTBLK_LOCK(sc);

	if (sc->vtblk_flags & VTBLK_FLAG_DETACH) {
		VTBLK_UNLOCK(sc);
		vtblk_bio_done(sc, bp, ENXIO);
		return;
	}

	bioq_insert_tail(&sc->vtblk_bioq, bp);
	vtblk_startio(sc);

	VTBLK_UNLOCK(sc);
}