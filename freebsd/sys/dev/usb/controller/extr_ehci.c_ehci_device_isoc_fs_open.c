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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct usb_xfer {TYPE_3__** td_start; int /*<<< orphan*/  endpointno; TYPE_2__* xroot; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  ehci_softc_t ;
struct TYPE_6__ {int sitd_portaddr; int /*<<< orphan*/  page_cache; void* sitd_back; struct TYPE_6__* obj_next; } ;
typedef  TYPE_3__ ehci_sitd_t ;
struct TYPE_5__ {TYPE_1__* udev; int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  hs_port_no; int /*<<< orphan*/  hs_hub_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int EHCI_LINK_TERMINATE ; 
 int EHCI_SITD_SET_ADDR (int /*<<< orphan*/ ) ; 
 int EHCI_SITD_SET_DIR_IN ; 
 int EHCI_SITD_SET_ENDPT (int /*<<< orphan*/ ) ; 
 int EHCI_SITD_SET_HUBA (int /*<<< orphan*/ ) ; 
 int EHCI_SITD_SET_PORT (int /*<<< orphan*/ ) ; 
 scalar_t__ UE_DIR_IN ; 
 int /*<<< orphan*/  UE_GET_ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ UE_GET_DIR (int /*<<< orphan*/ ) ; 
 void* htohc32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ehci_device_isoc_fs_open(struct usb_xfer *xfer)
{
	ehci_softc_t *sc = EHCI_BUS2SC(xfer->xroot->bus);
	ehci_sitd_t *td;
	uint32_t sitd_portaddr;
	uint8_t ds;

	sitd_portaddr =
	    EHCI_SITD_SET_ADDR(xfer->address) |
	    EHCI_SITD_SET_ENDPT(UE_GET_ADDR(xfer->endpointno)) |
	    EHCI_SITD_SET_HUBA(xfer->xroot->udev->hs_hub_addr) |
	    EHCI_SITD_SET_PORT(xfer->xroot->udev->hs_port_no);

	if (UE_GET_DIR(xfer->endpointno) == UE_DIR_IN)
		sitd_portaddr |= EHCI_SITD_SET_DIR_IN;

	sitd_portaddr = htohc32(sc, sitd_portaddr);

	/* initialize all TD's */

	for (ds = 0; ds != 2; ds++) {

		for (td = xfer->td_start[ds]; td; td = td->obj_next) {

			td->sitd_portaddr = sitd_portaddr;

			/*
			 * TODO: make some kind of automatic
			 * SMASK/CMASK selection based on micro-frame
			 * usage
			 *
			 * micro-frame usage (8 microframes per 1ms)
			 */
			td->sitd_back = htohc32(sc, EHCI_LINK_TERMINATE);

			usb_pc_cpu_flush(td->page_cache);
		}
	}
}