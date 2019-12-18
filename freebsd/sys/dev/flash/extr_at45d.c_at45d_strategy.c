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
struct bio {TYPE_1__* bio_disk; } ;
struct at45d_softc {int /*<<< orphan*/  bio_queue; } ;
struct TYPE_2__ {scalar_t__ d_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT45D_LOCK (struct at45d_softc*) ; 
 int /*<<< orphan*/  AT45D_UNLOCK (struct at45d_softc*) ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  wakeup (struct at45d_softc*) ; 

__attribute__((used)) static void
at45d_strategy(struct bio *bp)
{
	struct at45d_softc *sc;

	sc = (struct at45d_softc *)bp->bio_disk->d_drv1;
	AT45D_LOCK(sc);
	bioq_disksort(&sc->bio_queue, bp);
	wakeup(sc);
	AT45D_UNLOCK(sc);
}