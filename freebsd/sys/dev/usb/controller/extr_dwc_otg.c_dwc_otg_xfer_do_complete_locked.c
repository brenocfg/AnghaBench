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
struct usb_xfer {struct dwc_otg_td* td_transfer_cache; } ;
struct dwc_otg_td {int dummy; } ;
struct dwc_otg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  dwc_otg_standard_done (struct usb_xfer*) ; 

__attribute__((used)) static uint8_t
dwc_otg_xfer_do_complete_locked(struct dwc_otg_softc *sc, struct usb_xfer *xfer)
{
	struct dwc_otg_td *td;

	DPRINTFN(9, "\n");

	td = xfer->td_transfer_cache;
	if (td == NULL) {
		/* compute all actual lengths */
		dwc_otg_standard_done(xfer);
		return (1);
	}
	return (0);
}