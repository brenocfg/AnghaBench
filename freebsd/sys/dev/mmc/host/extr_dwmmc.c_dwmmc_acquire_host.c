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
struct dwmmc_softc {scalar_t__ bus_busy; int /*<<< orphan*/  sc_mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWMMC_LOCK (struct dwmmc_softc*) ; 
 int /*<<< orphan*/  DWMMC_UNLOCK (struct dwmmc_softc*) ; 
 int /*<<< orphan*/  PZERO ; 
 struct dwmmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  msleep (struct dwmmc_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
dwmmc_acquire_host(device_t brdev, device_t reqdev)
{
	struct dwmmc_softc *sc;

	sc = device_get_softc(brdev);

	DWMMC_LOCK(sc);
	while (sc->bus_busy)
		msleep(sc, &sc->sc_mtx, PZERO, "dwmmcah", hz / 5);
	sc->bus_busy++;
	DWMMC_UNLOCK(sc);
	return (0);
}