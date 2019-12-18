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
struct TYPE_4__ {size_t curr_dma_set; scalar_t__ short_frames_ok; } ;
struct usb_xfer {TYPE_2__* endpoint; scalar_t__ td_transfer_cache; TYPE_1__ flags_int; TYPE_3__** qh_start; } ;
struct TYPE_6__ {int /*<<< orphan*/  ed_tailp; int /*<<< orphan*/  ed_headp; int /*<<< orphan*/  page_cache; } ;
typedef  TYPE_3__ ohci_ed_t ;
struct TYPE_5__ {int toggle_next; int /*<<< orphan*/ * methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_xfer*) ; 
 int OHCI_HALTED ; 
 int OHCI_TOGGLECARRY ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohci_check_transfer_sub (struct usb_xfer*) ; 
 int /*<<< orphan*/  ohci_device_isoc_methods ; 
 int /*<<< orphan*/  ohci_isoc_done (struct usb_xfer*) ; 
 int /*<<< orphan*/  ohci_non_isoc_done (struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_pc_cpu_invalidate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
ohci_check_transfer(struct usb_xfer *xfer)
{
	ohci_ed_t *ed;
	uint32_t ed_headp;
	uint32_t ed_tailp;

	DPRINTFN(13, "xfer=%p checking transfer\n", xfer);

	ed = xfer->qh_start[xfer->flags_int.curr_dma_set];

	usb_pc_cpu_invalidate(ed->page_cache);
	ed_headp = le32toh(ed->ed_headp);
	ed_tailp = le32toh(ed->ed_tailp);

	if ((ed_headp & OHCI_HALTED) ||
	    (((ed_headp ^ ed_tailp) & (~0xF)) == 0)) {
		if (xfer->endpoint->methods == &ohci_device_isoc_methods) {
			/* isochronous transfer */
			ohci_isoc_done(xfer);
		} else {
			if (xfer->flags_int.short_frames_ok) {
				ohci_check_transfer_sub(xfer);
				if (xfer->td_transfer_cache) {
					/* not finished yet */
					return (0);
				}
			}
			/* store data-toggle */
			if (ed_headp & OHCI_TOGGLECARRY) {
				xfer->endpoint->toggle_next = 1;
			} else {
				xfer->endpoint->toggle_next = 0;
			}

			/* non-isochronous transfer */
			ohci_non_isoc_done(xfer);
		}
		return (1);
	}
	DPRINTFN(13, "xfer=%p is still active\n", xfer);
	return (0);
}