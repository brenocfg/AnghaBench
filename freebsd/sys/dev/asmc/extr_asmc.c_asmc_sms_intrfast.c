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
typedef  int /*<<< orphan*/  uint8_t ;
struct asmc_softc {int /*<<< orphan*/  sc_sms_task; int /*<<< orphan*/  sc_sms_tq; int /*<<< orphan*/  sc_sms_intrtype; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_sms_intr_works; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASMC_INTPORT_READ (struct asmc_softc*) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  asmc_sms_printintr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct asmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
asmc_sms_intrfast(void *arg)
{
	uint8_t type;
	device_t dev = (device_t) arg;
	struct asmc_softc *sc = device_get_softc(dev);
	if (!sc->sc_sms_intr_works)
		return (FILTER_HANDLED);

	mtx_lock_spin(&sc->sc_mtx);
	type = ASMC_INTPORT_READ(sc);
	mtx_unlock_spin(&sc->sc_mtx);

	sc->sc_sms_intrtype = type;
	asmc_sms_printintr(dev, type);

	taskqueue_enqueue(sc->sc_sms_tq, &sc->sc_sms_task);
	return (FILTER_HANDLED);
}