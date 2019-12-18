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
struct dwmmc_softc {int /*<<< orphan*/  bus_busy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWMMC_LOCK (struct dwmmc_softc*) ; 
 int /*<<< orphan*/  DWMMC_UNLOCK (struct dwmmc_softc*) ; 
 struct dwmmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct dwmmc_softc*) ; 

__attribute__((used)) static int
dwmmc_release_host(device_t brdev, device_t reqdev)
{
	struct dwmmc_softc *sc;

	sc = device_get_softc(brdev);

	DWMMC_LOCK(sc);
	sc->bus_busy--;
	wakeup(sc);
	DWMMC_UNLOCK(sc);
	return (0);
}