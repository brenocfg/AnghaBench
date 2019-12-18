#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sc_intr_hdl; } ;
struct exynos_xhci_softc {TYPE_1__ base; scalar_t__* res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 
 struct exynos_xhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  exynos_xhci_spec ; 
 int /*<<< orphan*/  xhci_halt_controller (TYPE_1__*) ; 
 int /*<<< orphan*/  xhci_uninit (TYPE_1__*) ; 

__attribute__((used)) static int
exynos_xhci_detach(device_t dev)
{
	struct exynos_xhci_softc *esc = device_get_softc(dev);
	int err;

	/* During module unload there are lots of children leftover */
	device_delete_children(dev);

	xhci_halt_controller(&esc->base);
	
	if (esc->res[2] && esc->base.sc_intr_hdl) {
		err = bus_teardown_intr(dev, esc->res[2],
		    esc->base.sc_intr_hdl);
		if (err) {
			device_printf(dev, "Could not tear down IRQ,"
			    " %d\n", err);
			return (err);
		}
	}

	bus_release_resources(dev, exynos_xhci_spec, esc->res);

	xhci_uninit(&esc->base);
	
	return (0);
}