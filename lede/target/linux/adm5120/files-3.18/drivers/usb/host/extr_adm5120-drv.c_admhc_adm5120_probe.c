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
struct usb_hcd {scalar_t__ rsrc_len; scalar_t__ rsrc_start; int /*<<< orphan*/  regs; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hc_driver {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HCD_DBG (char*) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  admhc_hcd_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcd_name ; 
 int /*<<< orphan*/  hcd_to_admhcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  ioremap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  request_mem_region (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (struct hc_driver const*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int admhc_adm5120_probe(const struct hc_driver *driver,
		  struct platform_device *dev)
{
	int retval;
	struct usb_hcd *hcd;
	int irq;
	struct resource *regs;

	/* sanity checks */
	regs = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!regs) {
		HCD_DBG("no IOMEM resource found\n");
		return -ENODEV;
	}

	irq = platform_get_irq(dev, 0);
	if (irq < 0) {
		HCD_DBG("no IRQ resource found\n");
		return -ENODEV;
	}

	hcd = usb_create_hcd(driver, &dev->dev, "ADM5120");
	if (!hcd)
		return -ENOMEM;

	hcd->rsrc_start = regs->start;
	hcd->rsrc_len = regs->end - regs->start + 1;

	if (!request_mem_region(hcd->rsrc_start, hcd->rsrc_len, hcd_name)) {
		HCD_DBG("request_mem_region failed\n");
		retval = -EBUSY;
		goto err_dev;
	}

	hcd->regs = ioremap(hcd->rsrc_start, hcd->rsrc_len);
	if (!hcd->regs) {
		HCD_DBG("ioremap failed\n");
		retval = -ENOMEM;
		goto err_mem;
	}

	admhc_hcd_init(hcd_to_admhcd(hcd));

	retval = usb_add_hcd(hcd, irq, 0);
	if (retval)
		goto err_io;

	return 0;

err_io:
	iounmap(hcd->regs);
err_mem:
	release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
err_dev:
	usb_put_hcd(hcd);
	return retval;
}