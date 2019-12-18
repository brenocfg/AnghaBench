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
struct octusb_td {int error_any; TYPE_2__* qh; } ;
struct octusb_softc {TYPE_1__* sc_port; } ;
struct TYPE_4__ {scalar_t__ fixup_complete; int* fixup_buf; size_t root_port_index; int fixup_handle; int fixup_pending; int /*<<< orphan*/  fixup_len; scalar_t__ fixup_phys; int /*<<< orphan*/  ep_handle; int /*<<< orphan*/  fixup_pc; struct octusb_softc* sc; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int UE_DIR_IN ; 
 int cvmx_usb_submit_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct octusb_td*) ; 
 int /*<<< orphan*/  octusb_complete_cb ; 
 scalar_t__ octusb_host_alloc_endpoint (struct octusb_td*) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
octusb_host_control_status_tx(struct octusb_td *td)
{
	int status;

	/* allocate endpoint and check pending */
	if (octusb_host_alloc_endpoint(td))
		return (1);		/* busy */

	/* check error */
	if (td->error_any)
		return (0);		/* done */

	if (td->qh->fixup_complete != 0) {
		/* clear complete flag */
		td->qh->fixup_complete = 0;
		/* done */
		return (0);
	}
	/* do control IN request */
	if (!(td->qh->fixup_buf[0] & UE_DIR_IN)) {

		struct octusb_softc *sc;

		/* get softc */
		sc = td->qh->sc;

		/* flush data */
		usb_pc_cpu_flush(td->qh->fixup_pc);

		/* start USB transfer */
		status = cvmx_usb_submit_control(
		    &sc->sc_port[td->qh->root_port_index].state,
		    td->qh->ep_handle, td->qh->fixup_phys,
		    td->qh->fixup_phys + 8, td->qh->fixup_len,
		    &octusb_complete_cb, td);

		/* check status */
		if (status < 0) {
			td->error_any = 1;
			return (0);	/* done */
		}
		td->qh->fixup_handle = status;
		td->qh->fixup_pending = 1;
		td->qh->fixup_complete = 0;

		return (1);		/* busy */
	}
	return (0);			/* done */
}