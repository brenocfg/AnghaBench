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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct usb_dmac_chan {TYPE_1__ vc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  USB_DMACHCR ; 
 int USB_DMACHCR_DE ; 
 int USB_DMACHCR_FTE ; 
 int USB_DMACHCR_NULL ; 
 int USB_DMACHCR_SP ; 
 int USB_DMACHCR_TE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int usb_dmac_chan_read (struct usb_dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dmac_chan_write (struct usb_dmac_chan*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_dmac_isr_transfer_end (struct usb_dmac_chan*) ; 

__attribute__((used)) static irqreturn_t usb_dmac_isr_channel(int irq, void *dev)
{
	struct usb_dmac_chan *chan = dev;
	irqreturn_t ret = IRQ_NONE;
	u32 mask = 0;
	u32 chcr;
	bool xfer_end = false;

	spin_lock(&chan->vc.lock);

	chcr = usb_dmac_chan_read(chan, USB_DMACHCR);
	if (chcr & (USB_DMACHCR_TE | USB_DMACHCR_SP)) {
		mask |= USB_DMACHCR_DE | USB_DMACHCR_TE | USB_DMACHCR_SP;
		if (chcr & USB_DMACHCR_DE)
			xfer_end = true;
		ret |= IRQ_HANDLED;
	}
	if (chcr & USB_DMACHCR_NULL) {
		/* An interruption of TE will happen after we set FTE */
		mask |= USB_DMACHCR_NULL;
		chcr |= USB_DMACHCR_FTE;
		ret |= IRQ_HANDLED;
	}
	if (mask)
		usb_dmac_chan_write(chan, USB_DMACHCR, chcr & ~mask);

	if (xfer_end)
		usb_dmac_isr_transfer_end(chan);

	spin_unlock(&chan->vc.lock);

	return ret;
}