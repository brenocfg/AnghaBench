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
struct mmc_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mmc_acquire_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_go_discovery (struct mmc_softc*) ; 
 int mmc_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmc_scan(struct mmc_softc *sc)
{
	device_t dev = sc->dev;
	int err;

	err = mmc_acquire_bus(dev, dev);
	if (err != 0) {
		device_printf(dev, "Failed to acquire bus for scanning\n");
		return;
	}
	mmc_go_discovery(sc);
	err = mmc_release_bus(dev, dev);
	if (err != 0) {
		device_printf(dev, "Failed to release bus after scanning\n");
		return;
	}
	(void)bus_generic_attach(dev);
}