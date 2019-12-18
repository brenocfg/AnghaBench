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
struct xhci_softc {int /*<<< orphan*/  sc_cmd_sx; int /*<<< orphan*/  sc_cmd_cv; int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_bus_mem_free_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_iterate_hw_softc ; 

void
xhci_uninit(struct xhci_softc *sc)
{
	/*
	 * NOTE: At this point the control transfer process is gone
	 * and "xhci_configure_msg" is no longer called. Consequently
	 * waiting for the configuration messages to complete is not
	 * needed.
	 */
	usb_bus_mem_free_all(&sc->sc_bus, &xhci_iterate_hw_softc);

	cv_destroy(&sc->sc_cmd_cv);
	sx_destroy(&sc->sc_cmd_sx);
}