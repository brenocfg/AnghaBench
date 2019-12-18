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
typedef  int uint32_t ;
struct TYPE_5__ {int td_token; int td_self; struct TYPE_5__* alt_next; struct TYPE_5__* obj_next; int /*<<< orphan*/  page_cache; } ;
typedef  TYPE_2__ uhci_td_t ;
struct TYPE_6__ {int qh_e_next; int /*<<< orphan*/  page_cache; } ;
typedef  TYPE_3__ uhci_qh_t ;
struct TYPE_4__ {size_t curr_dma_set; scalar_t__ control_xfr; } ;
struct usb_xfer {TYPE_2__* td_transfer_last; TYPE_1__ flags_int; TYPE_2__* td_transfer_cache; TYPE_3__** qh_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_xfer*) ; 
 int /*<<< orphan*/  UHCI_TD_SET_DT (int) ; 
 int htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uhci_check_transfer_sub(struct usb_xfer *xfer)
{
	uhci_qh_t *qh;
	uhci_td_t *td;
	uhci_td_t *td_alt_next;

	uint32_t td_token;
	uint32_t td_self;

	td = xfer->td_transfer_cache;
	qh = xfer->qh_start[xfer->flags_int.curr_dma_set];

	td_token = td->obj_next->td_token;
	td = td->alt_next;
	xfer->td_transfer_cache = td;
	td_self = td->td_self;
	td_alt_next = td->alt_next;

	if (xfer->flags_int.control_xfr)
		goto skip;	/* don't touch the DT value! */

	if (!((td->td_token ^ td_token) & htole32(UHCI_TD_SET_DT(1))))
		goto skip;	/* data toggle has correct value */

	/*
	 * The data toggle is wrong and we need to toggle it !
	 */
	while (1) {

		td->td_token ^= htole32(UHCI_TD_SET_DT(1));
		usb_pc_cpu_flush(td->page_cache);

		if (td == xfer->td_transfer_last) {
			/* last transfer */
			break;
		}
		td = td->obj_next;

		if (td->alt_next != td_alt_next) {
			/* next frame */
			break;
		}
	}
skip:

	/* update the QH */
	qh->qh_e_next = td_self;
	usb_pc_cpu_flush(qh->page_cache);

	DPRINTFN(13, "xfer=%p following alt next\n", xfer);
}