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
struct aml8726_mmc_softc {scalar_t__ bus_busy; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_MMC_LOCK (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  AML_MMC_UNLOCK (struct aml8726_mmc_softc*) ; 
 int /*<<< orphan*/  PZERO ; 
 struct aml8726_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_sleep (struct aml8726_mmc_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
aml8726_mmc_acquire_host(device_t bus, device_t child)
{
	struct aml8726_mmc_softc *sc = device_get_softc(bus);

	AML_MMC_LOCK(sc);

	while (sc->bus_busy)
		mtx_sleep(sc, &sc->mtx, PZERO, "mmc", hz / 5);
	sc->bus_busy++;

	AML_MMC_UNLOCK(sc);

	return (0);
}