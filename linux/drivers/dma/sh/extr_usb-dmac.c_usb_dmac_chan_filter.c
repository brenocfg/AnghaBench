#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_dmac_chan {scalar_t__ index; } ;
struct of_phandle_args {scalar_t__* args; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct usb_dmac_chan* to_usb_dmac_chan (struct dma_chan*) ; 

__attribute__((used)) static bool usb_dmac_chan_filter(struct dma_chan *chan, void *arg)
{
	struct usb_dmac_chan *uchan = to_usb_dmac_chan(chan);
	struct of_phandle_args *dma_spec = arg;

	/* USB-DMAC should be used with fixed usb controller's FIFO */
	if (uchan->index != dma_spec->args[0])
		return false;

	return true;
}