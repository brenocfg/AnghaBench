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
typedef  int uint8_t ;
struct uss820dci_softc {int dummy; } ;
struct TYPE_4__ {scalar_t__ control_hdr; scalar_t__ control_xfr; } ;
struct usb_xfer {int endpointno; TYPE_2__ flags_int; TYPE_1__* xroot; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int) ; 
 int UE_ADDR ; 
 int UE_DIR_IN ; 
 struct uss820dci_softc* USS820_DCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int USS820_READ_1 (struct uss820dci_softc*,int) ; 
 int USS820_SBIE ; 
 int USS820_SBIE1 ; 
 int /*<<< orphan*/  USS820_WRITE_1 (struct uss820dci_softc*,int,int) ; 

__attribute__((used)) static void
uss820dci_intr_set(struct usb_xfer *xfer, uint8_t set)
{
	struct uss820dci_softc *sc = USS820_DCI_BUS2SC(xfer->xroot->bus);
	uint8_t ep_no = (xfer->endpointno & UE_ADDR);
	uint8_t ep_reg;
	uint8_t temp;

	DPRINTFN(15, "endpoint 0x%02x\n", xfer->endpointno);

	if (ep_no > 3) {
		ep_reg = USS820_SBIE1;
	} else {
		ep_reg = USS820_SBIE;
	}

	ep_no &= 3;
	ep_no = 1 << (2 * ep_no);

	if (xfer->flags_int.control_xfr) {
		if (xfer->flags_int.control_hdr) {
			ep_no <<= 1;	/* RX interrupt only */
		} else {
			ep_no |= (ep_no << 1);	/* RX and TX interrupt */
		}
	} else {
		if (!(xfer->endpointno & UE_DIR_IN)) {
			ep_no <<= 1;
		}
	}
	temp = USS820_READ_1(sc, ep_reg);
	if (set) {
		temp |= ep_no;
	} else {
		temp &= ~ep_no;
	}
	USS820_WRITE_1(sc, ep_reg, temp);
}