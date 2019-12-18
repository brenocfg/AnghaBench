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
struct usb_dmac_sg {int mem_addr; int /*<<< orphan*/  size; } ;
struct usb_dmac_desc {scalar_t__ direction; struct usb_dmac_sg* sg; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__ chan; } ;
struct usb_dmac_chan {int /*<<< orphan*/  index; TYPE_3__ vc; struct usb_dmac_desc* desc; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  USB_DMACHCR ; 
 int USB_DMACHCR_DE ; 
 int USB_DMACHCR_IE ; 
 int USB_DMACHCR_NULLE ; 
 int USB_DMAC_CHCR_TS ; 
 int /*<<< orphan*/  USB_DMAC_XFER_SIZE ; 
 int /*<<< orphan*/  USB_DMADAR ; 
 int /*<<< orphan*/  USB_DMASAR ; 
 int /*<<< orphan*/  USB_DMATCR ; 
 int /*<<< orphan*/  USB_DMATEND ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct usb_dmac_sg*,int /*<<< orphan*/ ,int*,int*) ; 
 int usb_dmac_calc_tend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dmac_chan_is_busy (struct usb_dmac_chan*) ; 
 int /*<<< orphan*/  usb_dmac_chan_write (struct usb_dmac_chan*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usb_dmac_chan_start_sg(struct usb_dmac_chan *chan,
				   unsigned int index)
{
	struct usb_dmac_desc *desc = chan->desc;
	struct usb_dmac_sg *sg = desc->sg + index;
	dma_addr_t src_addr = 0, dst_addr = 0;

	WARN_ON_ONCE(usb_dmac_chan_is_busy(chan));

	if (desc->direction == DMA_DEV_TO_MEM)
		dst_addr = sg->mem_addr;
	else
		src_addr = sg->mem_addr;

	dev_dbg(chan->vc.chan.device->dev,
		"chan%u: queue sg %p: %u@%pad -> %pad\n",
		chan->index, sg, sg->size, &src_addr, &dst_addr);

	usb_dmac_chan_write(chan, USB_DMASAR, src_addr & 0xffffffff);
	usb_dmac_chan_write(chan, USB_DMADAR, dst_addr & 0xffffffff);
	usb_dmac_chan_write(chan, USB_DMATCR,
			    DIV_ROUND_UP(sg->size, USB_DMAC_XFER_SIZE));
	usb_dmac_chan_write(chan, USB_DMATEND, usb_dmac_calc_tend(sg->size));

	usb_dmac_chan_write(chan, USB_DMACHCR, USB_DMAC_CHCR_TS |
			USB_DMACHCR_NULLE | USB_DMACHCR_IE | USB_DMACHCR_DE);
}