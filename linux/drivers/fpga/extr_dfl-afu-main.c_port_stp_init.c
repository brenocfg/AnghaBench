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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; struct resource* resource; } ;
struct dfl_feature {size_t resource_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFL_PORT_REGION_INDEX_STP ; 
 int DFL_PORT_REGION_MMAP ; 
 int DFL_PORT_REGION_READ ; 
 int DFL_PORT_REGION_WRITE ; 
 int afu_mmio_region_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int port_stp_init(struct platform_device *pdev,
			 struct dfl_feature *feature)
{
	struct resource *res = &pdev->resource[feature->resource_index];

	return afu_mmio_region_add(dev_get_platdata(&pdev->dev),
				   DFL_PORT_REGION_INDEX_STP,
				   resource_size(res), res->start,
				   DFL_PORT_REGION_MMAP | DFL_PORT_REGION_READ |
				   DFL_PORT_REGION_WRITE);
}