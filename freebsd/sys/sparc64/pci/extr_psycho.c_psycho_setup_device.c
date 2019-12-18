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
typedef  scalar_t__ uint32_t ;
struct psycho_softc {int dummy; } ;
typedef  int /*<<< orphan*/  rev ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int PCICTL_ARB_PARK ; 
 int PCICTL_READ8 (struct psycho_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCICTL_WRITE8 (struct psycho_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCR_CS ; 
 struct psycho_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
psycho_setup_device(device_t bus, device_t child)
{
	struct psycho_softc *sc;
	uint32_t rev;

	sc = device_get_softc(bus);
	/*
	 * Revision 0 EBus bridges have a bug which prevents them from
	 * working when bus parking is enabled.
	 */
	if ((strcmp(ofw_bus_get_name(child), "ebus") == 0 ||
	    strcmp(ofw_bus_get_name(child), "pci108e,1000") == 0) &&
	    OF_getprop(ofw_bus_get_node(child), "revision-id", &rev,
	    sizeof(rev)) > 0 && rev == 0)
		PCICTL_WRITE8(sc, PCR_CS, PCICTL_READ8(sc, PCR_CS) &
		    ~PCICTL_ARB_PARK);
}