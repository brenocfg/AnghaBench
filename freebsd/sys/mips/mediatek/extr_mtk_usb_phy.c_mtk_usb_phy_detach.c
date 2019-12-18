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
struct mtk_usb_phy_softc {int /*<<< orphan*/ * res; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mtk_usb_phy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_clock_disable_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_reset_assert_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtk_usb_phy_detach(device_t dev)
{
	struct mtk_usb_phy_softc *sc = device_get_softc(dev);
	phandle_t node;

	/* Get our FDT node */
	node = ofw_bus_get_node(dev);

	/* If we have resets defined - assert them */
	if (OF_hasprop(node, "resets"))
		fdt_reset_assert_all(dev);

	/* If we have clocks defined - disable them */
	if (OF_hasprop(node, "clocks"))
		fdt_clock_disable_all(dev);

	/* Finally, release resources, if any were allocated */
	if (sc->res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->res);

	return (0);
}