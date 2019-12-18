#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t uint64_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  root_pc; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_mtx; } ;
struct xhci_softc {int sc_command_ccs; TYPE_2__ sc_hw; scalar_t__ sc_command_idx; TYPE_1__ sc_bus; } ;
struct xhci_hw_root {TYPE_3__* hwr_commands; } ;
struct usb_page_search {uintptr_t physaddr; struct xhci_hw_root* buffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  qwTrb0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int USB_ERR_IOERROR ; 
 int /*<<< orphan*/  XHCI_CRCR_HI ; 
 int /*<<< orphan*/  XHCI_CRCR_LO ; 
 int XHCI_CRCR_LO_CA ; 
 int XHCI_CRCR_LO_CRR ; 
 int XHCI_CRCR_LO_CS ; 
 int XHCI_CRCR_LO_RCS ; 
 int XHCI_MAX_COMMANDS ; 
 int XREAD4 (struct xhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XWRITE4 (struct xhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htole64 (uintptr_t) ; 
 int hz ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oper ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_page_search*) ; 

__attribute__((used)) static int
xhci_reset_command_queue_locked(struct xhci_softc *sc)
{
	struct usb_page_search buf_res;
	struct xhci_hw_root *phwr;
	uint64_t addr;
	uint32_t temp;

	DPRINTF("\n");

	temp = XREAD4(sc, oper, XHCI_CRCR_LO);
	if (temp & XHCI_CRCR_LO_CRR) {
		DPRINTF("Command ring running\n");
		temp &= ~(XHCI_CRCR_LO_CS | XHCI_CRCR_LO_CA);

		/*
		 * Try to abort the last command as per section
		 * 4.6.1.2 "Aborting a Command" of the XHCI
		 * specification:
		 */

		/* stop and cancel */
		XWRITE4(sc, oper, XHCI_CRCR_LO, temp | XHCI_CRCR_LO_CS);
		XWRITE4(sc, oper, XHCI_CRCR_HI, 0);

		XWRITE4(sc, oper, XHCI_CRCR_LO, temp | XHCI_CRCR_LO_CA);
		XWRITE4(sc, oper, XHCI_CRCR_HI, 0);

 		/* wait 250ms */
 		usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 4);

		/* check if command ring is still running */
		temp = XREAD4(sc, oper, XHCI_CRCR_LO);
		if (temp & XHCI_CRCR_LO_CRR) {
			DPRINTF("Comand ring still running\n");
			return (USB_ERR_IOERROR);
		}
	}

	/* reset command ring */
	sc->sc_command_ccs = 1;
	sc->sc_command_idx = 0;

	usbd_get_page(&sc->sc_hw.root_pc, 0, &buf_res);

	/* set up command ring control base address */
	addr = buf_res.physaddr;
	phwr = buf_res.buffer;
	addr += (uintptr_t)&((struct xhci_hw_root *)0)->hwr_commands[0];

	DPRINTF("CRCR=0x%016llx\n", (unsigned long long)addr);

	memset(phwr->hwr_commands, 0, sizeof(phwr->hwr_commands));
	phwr->hwr_commands[XHCI_MAX_COMMANDS - 1].qwTrb0 = htole64(addr);

	usb_pc_cpu_flush(&sc->sc_hw.root_pc);

	XWRITE4(sc, oper, XHCI_CRCR_LO, ((uint32_t)addr) | XHCI_CRCR_LO_RCS);
	XWRITE4(sc, oper, XHCI_CRCR_HI, (uint32_t)(addr >> 32));

	return (0);
}