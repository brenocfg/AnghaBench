#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int has_tt; struct reset_control* regs; int /*<<< orphan*/  rsrc_len; int /*<<< orphan*/  rsrc_start; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct reset_control {int dummy; } ;
struct TYPE_6__ {scalar_t__ coherent_dma_mask; scalar_t__* dma_mask; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct oxnas_hcd {struct reset_control* clk; struct reset_control* refsrc; struct reset_control* phyref; struct reset_control* rst_phyb; struct reset_control* rst_phya; struct reset_control* rst_host; void* use_pllb; struct reset_control* syscon; void* use_phya; } ;
struct ehci_hcd {struct reset_control* caps; scalar_t__ priv; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  clk_put (struct reset_control*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 struct reset_control* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct reset_control* devm_reset_control_get (TYPE_1__*,char*) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 void* of_clk_get_by_name (struct device_node*,char*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  oxnas_hc_driver ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  start_oxnas_usb_ehci (struct oxnas_hcd*) ; 
 int /*<<< orphan*/  stop_oxnas_usb_ehci (struct oxnas_hcd*) ; 
 struct reset_control* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 
 int usb_add_hcd (struct usb_hcd*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_create_hcd (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_disabled () ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int ehci_oxnas_drv_probe(struct platform_device *ofdev)
{
	struct device_node *np = ofdev->dev.of_node;
	struct usb_hcd *hcd;
	struct ehci_hcd *ehci;
	struct resource res;
	struct oxnas_hcd *oxnas;
	int irq, err;
	struct reset_control *rstc;

	if (usb_disabled())
		return -ENODEV;

	if (!ofdev->dev.dma_mask)
		ofdev->dev.dma_mask = &ofdev->dev.coherent_dma_mask;
	if (!ofdev->dev.coherent_dma_mask)
		ofdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	hcd = usb_create_hcd(&oxnas_hc_driver,	&ofdev->dev,
					dev_name(&ofdev->dev));
	if (!hcd)
		return -ENOMEM;

	err = of_address_to_resource(np, 0, &res);
	if (err)
		goto err_res;

	hcd->rsrc_start = res.start;
	hcd->rsrc_len = resource_size(&res);

	hcd->regs = devm_ioremap_resource(&ofdev->dev, &res);
	if (IS_ERR(hcd->regs)) {
		dev_err(&ofdev->dev, "devm_ioremap_resource failed\n");
		err = PTR_ERR(hcd->regs);
		goto err_ioremap;
	}

	oxnas = (struct oxnas_hcd *)hcd_to_ehci(hcd)->priv;

	oxnas->use_pllb = of_property_read_bool(np, "oxsemi,ehci_use_pllb");
	oxnas->use_phya = of_property_read_bool(np, "oxsemi,ehci_use_phya");

	oxnas->syscon = syscon_regmap_lookup_by_phandle(np, "oxsemi,sys-ctrl");
	if (IS_ERR(oxnas->syscon)) {
		err = PTR_ERR(oxnas->syscon);
		goto err_syscon;
	}

	oxnas->clk = of_clk_get_by_name(np, "usb");
	if (IS_ERR(oxnas->clk)) {
		err = PTR_ERR(oxnas->clk);
		goto err_clk;
	}

	if (oxnas->use_pllb) {
		oxnas->refsrc = of_clk_get_by_name(np, "refsrc");
		if (IS_ERR(oxnas->refsrc)) {
			err = PTR_ERR(oxnas->refsrc);
			goto err_refsrc;
		}
		oxnas->phyref = of_clk_get_by_name(np, "phyref");
		if (IS_ERR(oxnas->refsrc)) {
			err = PTR_ERR(oxnas->refsrc);
			goto err_phyref;
		}

	} else {
		oxnas->refsrc = NULL;
		oxnas->phyref = NULL;
	}

	rstc = devm_reset_control_get(&ofdev->dev, "host");
	if (IS_ERR(rstc)) {
		err = PTR_ERR(rstc);
		goto err_rst;
	}
	oxnas->rst_host = rstc;

	rstc = devm_reset_control_get(&ofdev->dev, "phya");
	if (IS_ERR(rstc)) {
		err = PTR_ERR(rstc);
		goto err_rst;
	}
	oxnas->rst_phya = rstc;

	rstc = devm_reset_control_get(&ofdev->dev, "phyb");
	if (IS_ERR(rstc)) {
		err = PTR_ERR(rstc);
		goto err_rst;
	}
	oxnas->rst_phyb = rstc;

	irq = irq_of_parse_and_map(np, 0);
	if (!irq) {
		dev_err(&ofdev->dev, "irq_of_parse_and_map failed\n");
		err = -EBUSY;
		goto err_irq;
	}

	hcd->has_tt = 1;
	ehci = hcd_to_ehci(hcd);
	ehci->caps = hcd->regs;

	start_oxnas_usb_ehci(oxnas);

	err = usb_add_hcd(hcd, irq, IRQF_SHARED);
	if (err)
		goto err_hcd;

	return 0;

err_hcd:
	stop_oxnas_usb_ehci(oxnas);
err_irq:
err_rst:
	if (oxnas->phyref)
		clk_put(oxnas->phyref);
err_phyref:
	if (oxnas->refsrc)
		clk_put(oxnas->refsrc);
err_refsrc:
	clk_put(oxnas->clk);
err_syscon:
err_clk:
err_ioremap:
err_res:
	usb_put_hcd(hcd);

	return err;
}