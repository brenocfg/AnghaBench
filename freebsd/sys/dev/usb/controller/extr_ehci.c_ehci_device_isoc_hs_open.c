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
typedef  int uint32_t ;
struct usb_xfer {int max_packet_size; int max_packet_count; int /*<<< orphan*/  endpointno; int /*<<< orphan*/  address; TYPE_2__** td_start; TYPE_1__* xroot; } ;
typedef  int /*<<< orphan*/  ehci_softc_t ;
struct TYPE_4__ {int /*<<< orphan*/  page_cache; void** itd_bp; scalar_t__* itd_status; struct TYPE_4__* obj_next; } ;
typedef  TYPE_2__ ehci_itd_t ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int EHCI_ITD_SET_ADDR (int /*<<< orphan*/ ) ; 
 int EHCI_ITD_SET_DIR_IN ; 
 int EHCI_ITD_SET_ENDPT (int /*<<< orphan*/ ) ; 
 int EHCI_ITD_SET_MPL (int) ; 
 scalar_t__ UE_DIR_IN ; 
 int /*<<< orphan*/  UE_GET_ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ UE_GET_DIR (int /*<<< orphan*/ ) ; 
 void* htohc32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_hs_bandwidth_alloc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ehci_device_isoc_hs_open(struct usb_xfer *xfer)
{
	ehci_softc_t *sc = EHCI_BUS2SC(xfer->xroot->bus);
	ehci_itd_t *td;
	uint32_t temp;
	uint8_t ds;

	usb_hs_bandwidth_alloc(xfer);

	/* initialize all TD's */

	for (ds = 0; ds != 2; ds++) {

		for (td = xfer->td_start[ds]; td; td = td->obj_next) {

			/* set TD inactive */
			td->itd_status[0] = 0;
			td->itd_status[1] = 0;
			td->itd_status[2] = 0;
			td->itd_status[3] = 0;
			td->itd_status[4] = 0;
			td->itd_status[5] = 0;
			td->itd_status[6] = 0;
			td->itd_status[7] = 0;

			/* set endpoint and address */
			td->itd_bp[0] = htohc32(sc,
			    EHCI_ITD_SET_ADDR(xfer->address) |
			    EHCI_ITD_SET_ENDPT(UE_GET_ADDR(xfer->endpointno)));

			temp =
			    EHCI_ITD_SET_MPL(xfer->max_packet_size & 0x7FF);

			/* set direction */
			if (UE_GET_DIR(xfer->endpointno) == UE_DIR_IN) {
				temp |= EHCI_ITD_SET_DIR_IN;
			}
			/* set maximum packet size */
			td->itd_bp[1] = htohc32(sc, temp);

			/* set transfer multiplier */
			td->itd_bp[2] = htohc32(sc, xfer->max_packet_count & 3);

			usb_pc_cpu_flush(td->page_cache);
		}
	}
}