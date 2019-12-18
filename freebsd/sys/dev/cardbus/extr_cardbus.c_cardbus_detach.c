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
struct cardbus_softc {int /*<<< orphan*/  sc_bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_RES_BUS ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cardbus_detach_card (int /*<<< orphan*/ ) ; 
 struct cardbus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cardbus_detach(device_t cbdev)
{
#ifdef PCI_RES_BUS
	struct cardbus_softc *sc;
#endif

	cardbus_detach_card(cbdev);
#ifdef PCI_RES_BUS
	sc = device_get_softc(cbdev);
	device_printf(cbdev, "Freeing up the allocatd bus\n");
	(void)bus_release_resource(cbdev, PCI_RES_BUS, 0, sc->sc_bus);
#endif
	return (0);
}