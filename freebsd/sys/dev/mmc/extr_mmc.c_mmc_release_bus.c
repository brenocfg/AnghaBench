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
struct mmc_softc {int /*<<< orphan*/ * owner; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int MMCBR_RELEASE_HOST (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMC_LOCK (struct mmc_softc*) ; 
 int /*<<< orphan*/  MMC_UNLOCK (struct mmc_softc*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 struct mmc_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
mmc_release_bus(device_t busdev, device_t dev)
{
	struct mmc_softc *sc;
	int err;

	sc = device_get_softc(busdev);

	MMC_LOCK(sc);
	if (!sc->owner)
		panic("mmc: releasing unowned bus.");
	if (sc->owner != dev)
		panic("mmc: you don't own the bus.  game over.");
	MMC_UNLOCK(sc);
	err = MMCBR_RELEASE_HOST(device_get_parent(busdev), busdev);
	if (err)
		return (err);
	MMC_LOCK(sc);
	sc->owner = NULL;
	MMC_UNLOCK(sc);
	return (0);
}