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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct pmu_softc {int sc_autopoll; int /*<<< orphan*/  sc_mutex; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMU_ADB_CMD ; 
 int /*<<< orphan*/  PMU_ADB_POLL_OFF ; 
 int PMU_SET_POLL_MASK ; 
 struct pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmu_send (struct pmu_softc*,int /*<<< orphan*/ ,int,int*,int,int*) ; 

__attribute__((used)) static u_int 
pmu_adb_autopoll(device_t dev, uint16_t mask) 
{
	struct pmu_softc *sc = device_get_softc(dev);

	/* magical incantation to re-enable autopolling */
	uint8_t cmd[] = {0, PMU_SET_POLL_MASK, (mask >> 8) & 0xff, mask & 0xff};
	uint8_t resp[16];

	mtx_lock(&sc->sc_mutex);

	if (sc->sc_autopoll == mask) {
		mtx_unlock(&sc->sc_mutex);
		return 0;
	}

	sc->sc_autopoll = mask & 0xffff;

	if (mask)
		pmu_send(sc, PMU_ADB_CMD, 4, cmd, 16, resp);
	else
		pmu_send(sc, PMU_ADB_POLL_OFF, 0, NULL, 16, resp);

	mtx_unlock(&sc->sc_mutex);
	
	return 0;
}