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
typedef  int u16 ;
struct usb_dmac {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  USB_DMAOR ; 
 int USB_DMAOR_AE ; 
 int USB_DMAOR_DME ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int usb_dmac_read (struct usb_dmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_dmac_write (struct usb_dmac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usb_dmac_init(struct usb_dmac *dmac)
{
	u16 dmaor;

	/* Clear all channels and enable the DMAC globally. */
	usb_dmac_write(dmac, USB_DMAOR, USB_DMAOR_DME);

	dmaor = usb_dmac_read(dmac, USB_DMAOR);
	if ((dmaor & (USB_DMAOR_AE | USB_DMAOR_DME)) != USB_DMAOR_DME) {
		dev_warn(dmac->dev, "DMAOR initialization failed.\n");
		return -EIO;
	}

	return 0;
}