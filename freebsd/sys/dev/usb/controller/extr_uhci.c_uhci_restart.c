#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  bus_mtx; } ;
struct TYPE_8__ {int /*<<< orphan*/  pframes_pc; } ;
struct TYPE_9__ {TYPE_5__ sc_bus; TYPE_1__ sc_hw; } ;
typedef  TYPE_2__ uhci_softc_t ;
struct usb_page_search {int /*<<< orphan*/  physaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UHCICMD (TYPE_2__*,int) ; 
 int /*<<< orphan*/  UHCI_CMD ; 
 int UHCI_CMD_MAXP ; 
 int UHCI_CMD_RS ; 
 int /*<<< orphan*/  UHCI_FLBASEADDR ; 
 int /*<<< orphan*/  UHCI_STS ; 
 int UHCI_STS_HCH ; 
 int UREAD2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UWRITE4 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usbd_get_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_page_search*) ; 

__attribute__((used)) static uint8_t
uhci_restart(uhci_softc_t *sc)
{
	struct usb_page_search buf_res;

	USB_BUS_LOCK_ASSERT(&sc->sc_bus, MA_OWNED);

  	if (UREAD2(sc, UHCI_CMD) & UHCI_CMD_RS) {
		DPRINTFN(2, "Already started\n");
		return (0);
	}

	DPRINTFN(2, "Restarting\n");

	usbd_get_page(&sc->sc_hw.pframes_pc, 0, &buf_res);

	/* Reload fresh base address */
	UWRITE4(sc, UHCI_FLBASEADDR, buf_res.physaddr);

	/*
	 * Assume 64 byte packets at frame end and start HC controller:
	 */
	UHCICMD(sc, (UHCI_CMD_MAXP | UHCI_CMD_RS));

	/* wait 10 milliseconds */

	usb_pause_mtx(&sc->sc_bus.bus_mtx, hz / 100);

	/* check that controller has started */

	if (UREAD2(sc, UHCI_STS) & UHCI_STS_HCH) {
		DPRINTFN(2, "Failed\n");
		return (1);
	}
	return (0);
}