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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct usb_device_request {scalar_t__ bmRequestType; scalar_t__ bRequest; int* wValue; } ;
struct avr32dci_td {int did_stall; int remainder; int offset; int /*<<< orphan*/  ep_no; int /*<<< orphan*/  pc; } ;
struct avr32dci_softc {int sc_dv_addr; int /*<<< orphan*/  physdata; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int AVR32_CTRL_DEV_ADDR ; 
 int AVR32_CTRL_DEV_FADDR_EN ; 
 int /*<<< orphan*/  AVR32_EPTCLRSTA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVR32_EPTSETSTA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVR32_EPTSTA (int /*<<< orphan*/ ) ; 
 int AVR32_EPTSTA_BYTE_COUNT (int) ; 
 int AVR32_EPTSTA_FRCESTALL ; 
 int AVR32_EPTSTA_RX_SETUP ; 
 struct avr32dci_softc* AVR32_PC2SC (int /*<<< orphan*/ ) ; 
 int AVR32_READ_4 (struct avr32dci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVR32_WRITE_4 (struct avr32dci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 scalar_t__ UR_SET_ADDRESS ; 
 scalar_t__ UT_WRITE_DEVICE ; 
 int /*<<< orphan*/  avr32dci_mod_ctrl (struct avr32dci_softc*,int,int) ; 
 int /*<<< orphan*/  memcpy (struct usb_device_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_copy_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 

__attribute__((used)) static uint8_t
avr32dci_setup_rx(struct avr32dci_td *td)
{
	struct avr32dci_softc *sc;
	struct usb_device_request req;
	uint16_t count;
	uint32_t temp;

	/* get pointer to softc */
	sc = AVR32_PC2SC(td->pc);

	/* check endpoint status */
	temp = AVR32_READ_4(sc, AVR32_EPTSTA(td->ep_no));

	DPRINTFN(5, "EPTSTA(%u)=0x%08x\n", td->ep_no, temp);

	if (!(temp & AVR32_EPTSTA_RX_SETUP)) {
		goto not_complete;
	}
	/* clear did stall */
	td->did_stall = 0;
	/* get the packet byte count */
	count = AVR32_EPTSTA_BYTE_COUNT(temp);

	/* verify data length */
	if (count != td->remainder) {
		DPRINTFN(0, "Invalid SETUP packet "
		    "length, %d bytes\n", count);
		goto not_complete;
	}
	if (count != sizeof(req)) {
		DPRINTFN(0, "Unsupported SETUP packet "
		    "length, %d bytes\n", count);
		goto not_complete;
	}
	/* receive data */
	memcpy(&req, sc->physdata, sizeof(req));

	/* copy data into real buffer */
	usbd_copy_in(td->pc, 0, &req, sizeof(req));

	td->offset = sizeof(req);
	td->remainder = 0;

	/* sneak peek the set address */
	if ((req.bmRequestType == UT_WRITE_DEVICE) &&
	    (req.bRequest == UR_SET_ADDRESS)) {
		sc->sc_dv_addr = req.wValue[0] & 0x7F;
		/* must write address before ZLP */
		avr32dci_mod_ctrl(sc, 0, AVR32_CTRL_DEV_FADDR_EN |
		    AVR32_CTRL_DEV_ADDR);
		avr32dci_mod_ctrl(sc, sc->sc_dv_addr, 0);
	} else {
		sc->sc_dv_addr = 0xFF;
	}

	/* clear SETUP packet interrupt */
	AVR32_WRITE_4(sc, AVR32_EPTCLRSTA(td->ep_no), AVR32_EPTSTA_RX_SETUP);
	return (0);			/* complete */

not_complete:
	if (temp & AVR32_EPTSTA_RX_SETUP) {
		/* clear SETUP packet interrupt */
		AVR32_WRITE_4(sc, AVR32_EPTCLRSTA(td->ep_no), AVR32_EPTSTA_RX_SETUP);
	}
	/* abort any ongoing transfer */
	if (!td->did_stall) {
		DPRINTFN(5, "stalling\n");
		AVR32_WRITE_4(sc, AVR32_EPTSETSTA(td->ep_no),
		    AVR32_EPTSTA_FRCESTALL);
		td->did_stall = 1;
	}
	return (1);			/* not complete */
}