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
struct aw_mmc_softc {int /*<<< orphan*/  aw_bus_busy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AW_MMC_LOCK (struct aw_mmc_softc*) ; 
 int /*<<< orphan*/  AW_MMC_UNLOCK (struct aw_mmc_softc*) ; 
 struct aw_mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct aw_mmc_softc*) ; 

__attribute__((used)) static int
aw_mmc_release_host(device_t bus, device_t child)
{
	struct aw_mmc_softc *sc;

	sc = device_get_softc(bus);
	AW_MMC_LOCK(sc);
	sc->aw_bus_busy--;
	wakeup(sc);
	AW_MMC_UNLOCK(sc);

	return (0);
}