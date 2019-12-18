#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bwn_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_tq; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_watchdog_ch; int /*<<< orphan*/  sc_task_ch; int /*<<< orphan*/  sc_rfswitch_ch; int /*<<< orphan*/  sc_maclist; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_LOCK_INIT (struct bwn_softc*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifqmaxlen ; 
 int /*<<< orphan*/  mbufq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static void
bwn_attach_pre(struct bwn_softc *sc)
{

	BWN_LOCK_INIT(sc);
	TAILQ_INIT(&sc->sc_maclist);
	callout_init_mtx(&sc->sc_rfswitch_ch, &sc->sc_mtx, 0);
	callout_init_mtx(&sc->sc_task_ch, &sc->sc_mtx, 0);
	callout_init_mtx(&sc->sc_watchdog_ch, &sc->sc_mtx, 0);
	mbufq_init(&sc->sc_snd, ifqmaxlen);
	sc->sc_tq = taskqueue_create_fast("bwn_taskq", M_NOWAIT,
		taskqueue_thread_enqueue, &sc->sc_tq);
	taskqueue_start_threads(&sc->sc_tq, 1, PI_NET,
		"%s taskq", device_get_nameunit(sc->sc_dev));
}