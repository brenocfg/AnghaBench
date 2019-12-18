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
struct g_journal_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_back_queue; } ;
struct bio {TYPE_2__* bio_from; } ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_journal_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct g_journal_softc*) ; 

__attribute__((used)) static void
g_journal_std_done(struct bio *bp)
{
	struct g_journal_softc *sc;

	sc = bp->bio_from->geom->softc;
	mtx_lock(&sc->sc_mtx);
	bioq_insert_tail(&sc->sc_back_queue, bp);
	wakeup(sc);
	mtx_unlock(&sc->sc_mtx);
}