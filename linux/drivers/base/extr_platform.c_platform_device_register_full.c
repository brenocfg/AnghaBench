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
struct platform_device_info {int /*<<< orphan*/  properties; int /*<<< orphan*/  size_data; int /*<<< orphan*/  data; int /*<<< orphan*/  num_res; int /*<<< orphan*/  res; scalar_t__ dma_mask; int /*<<< orphan*/  of_node_reused; int /*<<< orphan*/  fwnode; int /*<<< orphan*/  parent; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__* dma_mask; scalar_t__ coherent_dma_mask; int /*<<< orphan*/  of_node_reused; int /*<<< orphan*/  fwnode; int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION_SET (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 struct platform_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_ignore (scalar_t__*) ; 
 int /*<<< orphan*/  of_node_get (int /*<<< orphan*/ ) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_device_add_properties (struct platform_device*,int /*<<< orphan*/ ) ; 
 int platform_device_add_resources (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  to_of_node (int /*<<< orphan*/ ) ; 

struct platform_device *platform_device_register_full(
		const struct platform_device_info *pdevinfo)
{
	int ret = -ENOMEM;
	struct platform_device *pdev;

	pdev = platform_device_alloc(pdevinfo->name, pdevinfo->id);
	if (!pdev)
		return ERR_PTR(-ENOMEM);

	pdev->dev.parent = pdevinfo->parent;
	pdev->dev.fwnode = pdevinfo->fwnode;
	pdev->dev.of_node = of_node_get(to_of_node(pdev->dev.fwnode));
	pdev->dev.of_node_reused = pdevinfo->of_node_reused;

	if (pdevinfo->dma_mask) {
		/*
		 * This memory isn't freed when the device is put,
		 * I don't have a nice idea for that though.  Conceptually
		 * dma_mask in struct device should not be a pointer.
		 * See http://thread.gmane.org/gmane.linux.kernel.pci/9081
		 */
		pdev->dev.dma_mask =
			kmalloc(sizeof(*pdev->dev.dma_mask), GFP_KERNEL);
		if (!pdev->dev.dma_mask)
			goto err;

		kmemleak_ignore(pdev->dev.dma_mask);

		*pdev->dev.dma_mask = pdevinfo->dma_mask;
		pdev->dev.coherent_dma_mask = pdevinfo->dma_mask;
	}

	ret = platform_device_add_resources(pdev,
			pdevinfo->res, pdevinfo->num_res);
	if (ret)
		goto err;

	ret = platform_device_add_data(pdev,
			pdevinfo->data, pdevinfo->size_data);
	if (ret)
		goto err;

	if (pdevinfo->properties) {
		ret = platform_device_add_properties(pdev,
						     pdevinfo->properties);
		if (ret)
			goto err;
	}

	ret = platform_device_add(pdev);
	if (ret) {
err:
		ACPI_COMPANION_SET(&pdev->dev, NULL);
		kfree(pdev->dev.dma_mask);
		platform_device_put(pdev);
		return ERR_PTR(ret);
	}

	return pdev;
}