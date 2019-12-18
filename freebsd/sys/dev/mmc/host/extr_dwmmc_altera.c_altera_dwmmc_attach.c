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
struct dwmmc_softc {int bus_hz; int use_pio; int /*<<< orphan*/  hwtype; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HWTYPE_ALTERA ; 
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 struct dwmmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int dwmmc_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_node_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
altera_dwmmc_attach(device_t dev)
{
	struct dwmmc_softc *sc;
	phandle_t root;

	sc = device_get_softc(dev);
	sc->hwtype = HWTYPE_ALTERA;

	root = OF_finddevice("/");

	if (ofw_bus_node_is_compatible(root, "altr,socfpga-stratix10")) {
		sc->bus_hz = 24000000;
		sc->use_pio = 1;
	}

	return (dwmmc_attach(dev));
}