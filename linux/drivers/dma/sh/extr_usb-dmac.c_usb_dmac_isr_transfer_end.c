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
struct TYPE_3__ {int /*<<< orphan*/  cookie; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct usb_dmac_desc {scalar_t__ sg_index; scalar_t__ sg_len; TYPE_2__ vd; int /*<<< orphan*/  done_cookie; int /*<<< orphan*/  residue; } ;
struct usb_dmac_chan {struct usb_dmac_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  usb_dmac_chan_start_desc (struct usb_dmac_chan*) ; 
 int /*<<< orphan*/  usb_dmac_chan_start_sg (struct usb_dmac_chan*,scalar_t__) ; 
 int /*<<< orphan*/  usb_dmac_get_current_residue (struct usb_dmac_chan*,struct usb_dmac_desc*,scalar_t__) ; 
 int /*<<< orphan*/  vchan_cookie_complete (TYPE_2__*) ; 

__attribute__((used)) static void usb_dmac_isr_transfer_end(struct usb_dmac_chan *chan)
{
	struct usb_dmac_desc *desc = chan->desc;

	BUG_ON(!desc);

	if (++desc->sg_index < desc->sg_len) {
		usb_dmac_chan_start_sg(chan, desc->sg_index);
	} else {
		desc->residue = usb_dmac_get_current_residue(chan, desc,
							desc->sg_index - 1);
		desc->done_cookie = desc->vd.tx.cookie;
		vchan_cookie_complete(&desc->vd);

		/* Restart the next transfer if this driver has a next desc */
		usb_dmac_chan_start_desc(chan);
	}
}