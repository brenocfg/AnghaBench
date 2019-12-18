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
struct ow_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct ow_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ow_device_found ; 
 int /*<<< orphan*/  ow_enumerate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ow_search_rom ; 

__attribute__((used)) static int
ow_attach(device_t ndev)
{
	struct ow_softc *sc;

	/*
	 * Find all the devices on the bus. We don't probe / attach them in the
	 * enumeration phase. We do this because we want to allow the probe /
	 * attach routines of the child drivers to have as full an access to the
	 * bus as possible. While we reset things before the next step of the
	 * search (so it would likely be OK to allow access by the clients to
	 * the bus), it is more conservative to find them all, then to do the
	 * attach of the devices. This also allows the child devices to have
	 * more knowledge of the bus. We also ignore errors from the enumeration
	 * because they might happen after we've found a few devices.
	 */
	sc = device_get_softc(ndev);
	sc->dev = ndev;
	mtx_init(&sc->mtx, device_get_nameunit(sc->dev), "ow", MTX_DEF);
	ow_enumerate(ndev, ow_search_rom, ow_device_found);
	return bus_generic_attach(ndev);
}