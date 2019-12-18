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
struct xhci_td {int /*<<< orphan*/  page_cache; TYPE_1__* td_trb; } ;
struct usb_xfer {struct xhci_td* td_transfer_cache; } ;
struct TYPE_2__ {int dwTrb3; } ;

/* Variables and functions */
 int /*<<< orphan*/  XHCI_TRB_3_CYCLE_BIT ; 
 int htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pc_cpu_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_endpoint_doorbell (struct usb_xfer*) ; 

__attribute__((used)) static void
xhci_activate_transfer(struct usb_xfer *xfer)
{
	struct xhci_td *td;

	td = xfer->td_transfer_cache;

	usb_pc_cpu_invalidate(td->page_cache);

	if (!(td->td_trb[0].dwTrb3 & htole32(XHCI_TRB_3_CYCLE_BIT))) {

		/* activate the transfer */

		td->td_trb[0].dwTrb3 |= htole32(XHCI_TRB_3_CYCLE_BIT);
		usb_pc_cpu_flush(td->page_cache);

		xhci_endpoint_doorbell(xfer);
	}
}