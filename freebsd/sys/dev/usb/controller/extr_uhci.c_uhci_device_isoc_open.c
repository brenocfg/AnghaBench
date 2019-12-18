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
typedef  int uint8_t ;
typedef  void* uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  page_cache; void* td_token; void* td_status; struct TYPE_2__* obj_next; } ;
typedef  TYPE_1__ uhci_td_t ;
struct usb_xfer {TYPE_1__** td_start; int /*<<< orphan*/  address; int /*<<< orphan*/  endpointno; } ;

/* Variables and functions */
 scalar_t__ UE_DIR_IN ; 
 scalar_t__ UE_GET_DIR (int /*<<< orphan*/ ) ; 
 void* UHCI_TD_IN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* UHCI_TD_IOS ; 
 void* UHCI_TD_OUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htole32 (void*) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhci_device_isoc_open(struct usb_xfer *xfer)
{
	uhci_td_t *td;
	uint32_t td_token;
	uint8_t ds;

	td_token =
	    (UE_GET_DIR(xfer->endpointno) == UE_DIR_IN) ?
	    UHCI_TD_IN(0, xfer->endpointno, xfer->address, 0) :
	    UHCI_TD_OUT(0, xfer->endpointno, xfer->address, 0);

	td_token = htole32(td_token);

	/* initialize all TD's */

	for (ds = 0; ds != 2; ds++) {

		for (td = xfer->td_start[ds]; td; td = td->obj_next) {

			/* mark TD as inactive */
			td->td_status = htole32(UHCI_TD_IOS);
			td->td_token = td_token;

			usb_pc_cpu_flush(td->page_cache);
		}
	}
}