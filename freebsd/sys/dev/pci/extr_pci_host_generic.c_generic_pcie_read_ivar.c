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
struct generic_pcie_core_softc {uintptr_t bus_start; uintptr_t ecam; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int PCIB_IVAR_BUS ; 
 int PCIB_IVAR_DOMAIN ; 
 scalar_t__ bootverbose ; 
 struct generic_pcie_core_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
generic_pcie_read_ivar(device_t dev, device_t child, int index,
    uintptr_t *result)
{
	struct generic_pcie_core_softc *sc;

	sc = device_get_softc(dev);

	if (index == PCIB_IVAR_BUS) {
		*result = sc->bus_start;
		return (0);

	}

	if (index == PCIB_IVAR_DOMAIN) {
		*result = sc->ecam;
		return (0);
	}

	if (bootverbose)
		device_printf(dev, "ERROR: Unknown index %d.\n", index);
	return (ENOENT);
}