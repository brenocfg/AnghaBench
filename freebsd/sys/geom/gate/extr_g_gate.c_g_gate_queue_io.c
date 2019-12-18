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
struct g_gate_softc {int sc_flags; scalar_t__ sc_queue_size; scalar_t__ sc_queue_count; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_inqueue; scalar_t__ sc_seq; } ;
struct bio {void* bio_driver1; TYPE_2__* bio_to; } ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_gate_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 int G_GATE_FLAG_DESTROY ; 
 int /*<<< orphan*/  G_GATE_LOGREQ (int,struct bio*,char*) ; 
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct g_gate_softc*) ; 

__attribute__((used)) static void
g_gate_queue_io(struct bio *bp)
{
	struct g_gate_softc *sc;

	sc = bp->bio_to->geom->softc;
	if (sc == NULL || (sc->sc_flags & G_GATE_FLAG_DESTROY) != 0) {
		g_io_deliver(bp, ENXIO);
		return;
	}

	mtx_lock(&sc->sc_queue_mtx);

	if (sc->sc_queue_size > 0 && sc->sc_queue_count > sc->sc_queue_size) {
		mtx_unlock(&sc->sc_queue_mtx);
		G_GATE_LOGREQ(1, bp, "Queue full, request canceled.");
		g_io_deliver(bp, ENOMEM);
		return;
	}

	bp->bio_driver1 = (void *)sc->sc_seq;
	sc->sc_seq++;
	sc->sc_queue_count++;

	bioq_insert_tail(&sc->sc_inqueue, bp);
	wakeup(sc);

	mtx_unlock(&sc->sc_queue_mtx);
}