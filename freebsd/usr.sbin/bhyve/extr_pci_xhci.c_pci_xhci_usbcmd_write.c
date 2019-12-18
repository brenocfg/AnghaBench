#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct xhci_trb {int dummy; } ;
struct TYPE_4__ {int usbcmd; int /*<<< orphan*/  usbsts; } ;
struct pci_xhci_softc {TYPE_2__ opregs; } ;
struct pci_xhci_portregs {int portsc; } ;
struct pci_xhci_dev_emu {TYPE_1__* dev_ue; } ;
struct TYPE_3__ {int ue_usbver; } ;

/* Variables and functions */
 int /*<<< orphan*/  UPS_PORT_LS_POLL ; 
 int /*<<< orphan*/  UPS_PORT_LS_U0 ; 
 int XHCI_CMD_CRS ; 
 int XHCI_CMD_CSS ; 
 int XHCI_CMD_HCRST ; 
 int XHCI_CMD_RS ; 
 struct pci_xhci_dev_emu* XHCI_DEVINST_PTR (struct pci_xhci_softc*,int) ; 
 int XHCI_MAX_DEVS ; 
 struct pci_xhci_portregs* XHCI_PORTREG_PTR (struct pci_xhci_softc*,int) ; 
 int XHCI_PS_CCS ; 
 int XHCI_PS_CSC ; 
 int XHCI_PS_PLS_MASK ; 
 int XHCI_PS_PLS_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_STS_HCH ; 
 int /*<<< orphan*/  XHCI_STS_PCD ; 
 scalar_t__ XHCI_TRB_ERROR_SUCCESS ; 
 int /*<<< orphan*/  XHCI_TRB_EVENT_PORT_STS_CHANGE ; 
 int /*<<< orphan*/  pci_xhci_assert_interrupt (struct pci_xhci_softc*) ; 
 scalar_t__ pci_xhci_insert_event (struct pci_xhci_softc*,struct xhci_trb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_xhci_reset (struct pci_xhci_softc*) ; 
 int /*<<< orphan*/  pci_xhci_set_evtrb (struct xhci_trb*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
pci_xhci_usbcmd_write(struct pci_xhci_softc *sc, uint32_t cmd)
{
	int do_intr = 0;
	int i;

	if (cmd & XHCI_CMD_RS) {
		do_intr = (sc->opregs.usbcmd & XHCI_CMD_RS) == 0;

		sc->opregs.usbcmd |= XHCI_CMD_RS;
		sc->opregs.usbsts &= ~XHCI_STS_HCH;
		sc->opregs.usbsts |= XHCI_STS_PCD;

		/* Queue port change event on controller run from stop */
		if (do_intr)
			for (i = 1; i <= XHCI_MAX_DEVS; i++) {
				struct pci_xhci_dev_emu *dev;
				struct pci_xhci_portregs *port;
				struct xhci_trb		evtrb;

				if ((dev = XHCI_DEVINST_PTR(sc, i)) == NULL)
					continue;

				port = XHCI_PORTREG_PTR(sc, i);
				port->portsc |= XHCI_PS_CSC | XHCI_PS_CCS;
				port->portsc &= ~XHCI_PS_PLS_MASK;

				/*
				 * XHCI 4.19.3 USB2 RxDetect->Polling,
				 *             USB3 Polling->U0
				 */
				if (dev->dev_ue->ue_usbver == 2)
					port->portsc |=
					    XHCI_PS_PLS_SET(UPS_PORT_LS_POLL);
				else
					port->portsc |=
					    XHCI_PS_PLS_SET(UPS_PORT_LS_U0);

				pci_xhci_set_evtrb(&evtrb, i,
				    XHCI_TRB_ERROR_SUCCESS,
				    XHCI_TRB_EVENT_PORT_STS_CHANGE);

				if (pci_xhci_insert_event(sc, &evtrb, 0) !=
				    XHCI_TRB_ERROR_SUCCESS)
					break;
			}
	} else {
		sc->opregs.usbcmd &= ~XHCI_CMD_RS;
		sc->opregs.usbsts |= XHCI_STS_HCH;
		sc->opregs.usbsts &= ~XHCI_STS_PCD;
	}

	/* start execution of schedule; stop when set to 0 */
	cmd |= sc->opregs.usbcmd & XHCI_CMD_RS;

	if (cmd & XHCI_CMD_HCRST) {
		/* reset controller */
		pci_xhci_reset(sc);
		cmd &= ~XHCI_CMD_HCRST;
	}

	cmd &= ~(XHCI_CMD_CSS | XHCI_CMD_CRS);

	if (do_intr)
		pci_xhci_assert_interrupt(sc);

	return (cmd);
}