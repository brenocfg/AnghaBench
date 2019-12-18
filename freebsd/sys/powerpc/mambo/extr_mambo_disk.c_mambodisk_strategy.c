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
struct mambodisk_softc {int /*<<< orphan*/  bio_queue; } ;
struct bio {TYPE_1__* bio_disk; } ;
struct TYPE_2__ {scalar_t__ d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBODISK_LOCK (struct mambodisk_softc*) ; 
 int /*<<< orphan*/  MBODISK_UNLOCK (struct mambodisk_softc*) ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  wakeup (struct mambodisk_softc*) ; 

__attribute__((used)) static void
mambodisk_strategy(struct bio *bp)
{
	struct mambodisk_softc *sc;

	sc = (struct mambodisk_softc *)bp->bio_disk->d_drv1;
	MBODISK_LOCK(sc);
	bioq_disksort(&sc->bio_queue, bp);
	wakeup(sc);
	MBODISK_UNLOCK(sc);
}