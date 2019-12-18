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
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  fwnode; } ;
struct platform_device {struct device dev; } ;
struct logic_pio_hwaddr {scalar_t__ io_start; scalar_t__ size; int /*<<< orphan*/ * ops; struct hisi_lpc_dev* hostdata; int /*<<< orphan*/  flags; int /*<<< orphan*/  fwnode; } ;
struct hisi_lpc_dev {struct logic_pio_hwaddr* io_host; int /*<<< orphan*/  membase; int /*<<< orphan*/  cycle_lock; } ;
struct acpi_device {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGIC_PIO_INDIRECT ; 
 scalar_t__ PIO_INDIRECT_SIZE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct hisi_lpc_dev*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int hisi_lpc_acpi_probe (struct device*) ; 
 int /*<<< orphan*/  hisi_lpc_ops ; 
 int logic_pio_register_range (struct logic_pio_hwaddr*) ; 
 int /*<<< orphan*/  logic_pio_unregister_range (struct logic_pio_hwaddr*) ; 
 int of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_lpc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct acpi_device *acpi_device = ACPI_COMPANION(dev);
	struct logic_pio_hwaddr *range;
	struct hisi_lpc_dev *lpcdev;
	resource_size_t io_end;
	struct resource *res;
	int ret;

	lpcdev = devm_kzalloc(dev, sizeof(*lpcdev), GFP_KERNEL);
	if (!lpcdev)
		return -ENOMEM;

	spin_lock_init(&lpcdev->cycle_lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	lpcdev->membase = devm_ioremap_resource(dev, res);
	if (IS_ERR(lpcdev->membase))
		return PTR_ERR(lpcdev->membase);

	range = devm_kzalloc(dev, sizeof(*range), GFP_KERNEL);
	if (!range)
		return -ENOMEM;

	range->fwnode = dev->fwnode;
	range->flags = LOGIC_PIO_INDIRECT;
	range->size = PIO_INDIRECT_SIZE;
	range->hostdata = lpcdev;
	range->ops = &hisi_lpc_ops;
	lpcdev->io_host = range;

	ret = logic_pio_register_range(range);
	if (ret) {
		dev_err(dev, "register IO range failed (%d)!\n", ret);
		return ret;
	}

	/* register the LPC host PIO resources */
	if (acpi_device)
		ret = hisi_lpc_acpi_probe(dev);
	else
		ret = of_platform_populate(dev->of_node, NULL, NULL, dev);
	if (ret) {
		logic_pio_unregister_range(range);
		return ret;
	}

	dev_set_drvdata(dev, lpcdev);

	io_end = lpcdev->io_host->io_start + lpcdev->io_host->size;
	dev_info(dev, "registered range [%pa - %pa]\n",
		 &lpcdev->io_host->io_start, &io_end);

	return ret;
}