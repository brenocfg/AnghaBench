#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xhci_trb {int dummy; } ;
struct pci_xhci_softc {int dummy; } ;
struct pci_xhci_portregs {int portsc; } ;
struct pci_xhci_dev_emu {TYPE_1__* dev_ue; } ;
struct TYPE_2__ {int ue_usbver; int /*<<< orphan*/  ue_usbspeed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 struct pci_xhci_dev_emu* XHCI_DEVINST_PTR (struct pci_xhci_softc*,int) ; 
 int XHCI_MAX_DEVS ; 
 struct pci_xhci_portregs* XHCI_PORTREG_PTR (struct pci_xhci_softc*,int) ; 
 int XHCI_PS_PED ; 
 int XHCI_PS_PLS_MASK ; 
 int XHCI_PS_PR ; 
 int XHCI_PS_PRC ; 
 int XHCI_PS_SPEED_SET (int /*<<< orphan*/ ) ; 
 int XHCI_PS_WRC ; 
 int XHCI_TRB_ERROR_SUCCESS ; 
 int /*<<< orphan*/  XHCI_TRB_EVENT_PORT_STS_CHANGE ; 
 int /*<<< orphan*/  assert (int) ; 
 int pci_xhci_insert_event (struct pci_xhci_softc*,struct xhci_trb*,int) ; 
 int /*<<< orphan*/  pci_xhci_set_evtrb (struct xhci_trb*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_xhci_reset_port(struct pci_xhci_softc *sc, int portn, int warm)
{
	struct pci_xhci_portregs *port;
	struct pci_xhci_dev_emu	*dev;
	struct xhci_trb		evtrb;
	int	error;

	assert(portn <= XHCI_MAX_DEVS);

	DPRINTF(("xhci reset port %d\r\n", portn));

	port = XHCI_PORTREG_PTR(sc, portn);
	dev = XHCI_DEVINST_PTR(sc, portn);
	if (dev) {
		port->portsc &= ~(XHCI_PS_PLS_MASK | XHCI_PS_PR | XHCI_PS_PRC);
		port->portsc |= XHCI_PS_PED |
		    XHCI_PS_SPEED_SET(dev->dev_ue->ue_usbspeed);

		if (warm && dev->dev_ue->ue_usbver == 3) {
			port->portsc |= XHCI_PS_WRC;
		}

		if ((port->portsc & XHCI_PS_PRC) == 0) {
			port->portsc |= XHCI_PS_PRC;

			pci_xhci_set_evtrb(&evtrb, portn,
			     XHCI_TRB_ERROR_SUCCESS,
			     XHCI_TRB_EVENT_PORT_STS_CHANGE);
			error = pci_xhci_insert_event(sc, &evtrb, 1);
			if (error != XHCI_TRB_ERROR_SUCCESS)
				DPRINTF(("xhci reset port insert event "
				         "failed\r\n"));
		}
	}
}