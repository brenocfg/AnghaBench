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
struct TYPE_2__ {struct device* dev; } ;
struct dw_dma {TYPE_1__ dma; } ;
struct device {int dummy; } ;
struct acpi_dma_filter_info {int /*<<< orphan*/  filter_fn; int /*<<< orphan*/  dma_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SLAVE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int acpi_dma_controller_register (struct device*,int /*<<< orphan*/ ,struct acpi_dma_filter_info*) ; 
 int /*<<< orphan*/  acpi_dma_simple_xlate ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct acpi_dma_filter_info* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_dma_acpi_filter ; 
 int /*<<< orphan*/  has_acpi_companion (struct device*) ; 

void dw_dma_acpi_controller_register(struct dw_dma *dw)
{
	struct device *dev = dw->dma.dev;
	struct acpi_dma_filter_info *info;
	int ret;

	if (!has_acpi_companion(dev))
		return;

	info = devm_kzalloc(dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return;

	dma_cap_zero(info->dma_cap);
	dma_cap_set(DMA_SLAVE, info->dma_cap);
	info->filter_fn = dw_dma_acpi_filter;

	ret = acpi_dma_controller_register(dev, acpi_dma_simple_xlate, info);
	if (ret)
		dev_err(dev, "could not register acpi_dma_controller\n");
}