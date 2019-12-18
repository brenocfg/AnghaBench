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
typedef  int uint8_t ;
struct pmu_softc {int /*<<< orphan*/  sc_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMU_SET_SLEEPLED ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmu_send (struct pmu_softc*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmu_set_sleepled(void *xsc, int onoff)
{
	struct pmu_softc *sc = xsc;
	uint8_t cmd[] = {4, 0, 0};

	cmd[2] = onoff;
	
	mtx_lock(&sc->sc_mutex);
	pmu_send(sc, PMU_SET_SLEEPLED, 3, cmd, 0, NULL);
	mtx_unlock(&sc->sc_mutex);
}