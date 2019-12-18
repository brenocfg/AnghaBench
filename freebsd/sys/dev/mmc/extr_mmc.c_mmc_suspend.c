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
struct mmc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_suspend (int /*<<< orphan*/ ) ; 
 struct mmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mmc_acquire_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_power_down (struct mmc_softc*) ; 
 int mmc_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mmc_suspend(device_t dev)
{
	struct mmc_softc *sc = device_get_softc(dev);
	int err;

	err = bus_generic_suspend(dev);
	if (err != 0)
		return (err);
	/*
	 * We power down with the bus acquired here, mainly so that no device
	 * is selected any longer and sc->last_rca gets set to 0.  Otherwise,
	 * the deselect as part of the bus acquisition in mmc_scan() may fail
	 * during resume, as the bus isn't powered up again before later in
	 * mmc_go_discovery().
	 */
	err = mmc_acquire_bus(dev, dev);
	if (err != 0)
		return (err);
	mmc_power_down(sc);
	err = mmc_release_bus(dev, dev);
	return (err);
}