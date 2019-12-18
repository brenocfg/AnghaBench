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
struct sp_platform {int coherent; } ;
struct sp_device {int /*<<< orphan*/  axcache; int /*<<< orphan*/  io_map; int /*<<< orphan*/  dev_vdata; struct sp_platform* dev_specific; } ;
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
typedef  enum dev_dma_attr { ____Placeholder_dev_dma_attr } dev_dma_attr ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_NONE ; 
 int /*<<< orphan*/  CACHE_WB_NO_ALLOC ; 
 int DEV_DMA_COHERENT ; 
 int DEV_DMA_NOT_SUPPORTED ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct sp_device*) ; 
 int device_get_dma_attr (struct device*) ; 
 struct sp_platform* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 struct sp_device* sp_alloc_struct (struct device*) ; 
 int /*<<< orphan*/  sp_get_acpi_version (struct platform_device*) ; 
 int sp_get_irqs (struct sp_device*) ; 
 int /*<<< orphan*/  sp_get_of_version (struct platform_device*) ; 
 int sp_init (struct sp_device*) ; 

__attribute__((used)) static int sp_platform_probe(struct platform_device *pdev)
{
	struct sp_device *sp;
	struct sp_platform *sp_platform;
	struct device *dev = &pdev->dev;
	enum dev_dma_attr attr;
	int ret;

	ret = -ENOMEM;
	sp = sp_alloc_struct(dev);
	if (!sp)
		goto e_err;

	sp_platform = devm_kzalloc(dev, sizeof(*sp_platform), GFP_KERNEL);
	if (!sp_platform)
		goto e_err;

	sp->dev_specific = sp_platform;
	sp->dev_vdata = pdev->dev.of_node ? sp_get_of_version(pdev)
					 : sp_get_acpi_version(pdev);
	if (!sp->dev_vdata) {
		ret = -ENODEV;
		dev_err(dev, "missing driver data\n");
		goto e_err;
	}

	sp->io_map = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(sp->io_map)) {
		ret = PTR_ERR(sp->io_map);
		goto e_err;
	}

	attr = device_get_dma_attr(dev);
	if (attr == DEV_DMA_NOT_SUPPORTED) {
		dev_err(dev, "DMA is not supported");
		goto e_err;
	}

	sp_platform->coherent = (attr == DEV_DMA_COHERENT);
	if (sp_platform->coherent)
		sp->axcache = CACHE_WB_NO_ALLOC;
	else
		sp->axcache = CACHE_NONE;

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(48));
	if (ret) {
		dev_err(dev, "dma_set_mask_and_coherent failed (%d)\n", ret);
		goto e_err;
	}

	ret = sp_get_irqs(sp);
	if (ret)
		goto e_err;

	dev_set_drvdata(dev, sp);

	ret = sp_init(sp);
	if (ret)
		goto e_err;

	dev_notice(dev, "enabled\n");

	return 0;

e_err:
	dev_notice(dev, "initialization failed\n");
	return ret;
}