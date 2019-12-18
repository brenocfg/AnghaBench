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
struct ssp_device {scalar_t__ irq; int type; int /*<<< orphan*/  node; scalar_t__ of_node; scalar_t__ use_count; int /*<<< orphan*/  port_id; int /*<<< orphan*/ * mmio_base; int /*<<< orphan*/  phys_base; int /*<<< orphan*/  clk; struct platform_device* pdev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device_id {scalar_t__ driver_data; } ;
struct device {scalar_t__ of_node; } ;
struct platform_device {int /*<<< orphan*/  id; int /*<<< orphan*/  name; struct device dev; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ssp_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct resource* devm_request_mem_region (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ssp_device*) ; 
 int /*<<< orphan*/  pxa_ssp_of_ids ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  ssp_list ; 
 int /*<<< orphan*/  ssp_lock ; 

__attribute__((used)) static int pxa_ssp_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct ssp_device *ssp;
	struct device *dev = &pdev->dev;

	ssp = devm_kzalloc(dev, sizeof(struct ssp_device), GFP_KERNEL);
	if (ssp == NULL)
		return -ENOMEM;

	ssp->pdev = pdev;

	ssp->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(ssp->clk))
		return PTR_ERR(ssp->clk);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(dev, "no memory resource defined\n");
		return -ENODEV;
	}

	res = devm_request_mem_region(dev, res->start, resource_size(res),
				      pdev->name);
	if (res == NULL) {
		dev_err(dev, "failed to request memory resource\n");
		return -EBUSY;
	}

	ssp->phys_base = res->start;

	ssp->mmio_base = devm_ioremap(dev, res->start, resource_size(res));
	if (ssp->mmio_base == NULL) {
		dev_err(dev, "failed to ioremap() registers\n");
		return -ENODEV;
	}

	ssp->irq = platform_get_irq(pdev, 0);
	if (ssp->irq < 0) {
		dev_err(dev, "no IRQ resource defined\n");
		return -ENODEV;
	}

	if (dev->of_node) {
		const struct of_device_id *id =
			of_match_device(of_match_ptr(pxa_ssp_of_ids), dev);
		ssp->type = (int) id->data;
	} else {
		const struct platform_device_id *id =
			platform_get_device_id(pdev);
		ssp->type = (int) id->driver_data;

		/* PXA2xx/3xx SSP ports starts from 1 and the internal pdev->id
		 * starts from 0, do a translation here
		 */
		ssp->port_id = pdev->id + 1;
	}

	ssp->use_count = 0;
	ssp->of_node = dev->of_node;

	mutex_lock(&ssp_lock);
	list_add(&ssp->node, &ssp_list);
	mutex_unlock(&ssp_lock);

	platform_set_drvdata(pdev, ssp);

	return 0;
}