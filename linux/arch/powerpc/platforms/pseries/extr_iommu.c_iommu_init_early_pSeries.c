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
struct TYPE_2__ {int /*<<< orphan*/  dma_dev_setup; int /*<<< orphan*/  dma_bus_setup; int /*<<< orphan*/  iommu_bypass_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_LPAR ; 
 int /*<<< orphan*/  disable_ddw ; 
 int /*<<< orphan*/  dma_iommu_ops ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_bypass_supported_pSeriesLP ; 
 int /*<<< orphan*/  iommu_mem_nb ; 
 int /*<<< orphan*/  iommu_reconfig_nb ; 
 int /*<<< orphan*/  is_secure_guest () ; 
 scalar_t__ of_chosen ; 
 scalar_t__ of_get_property (scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_reconfig_notifier_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dma_bus_setup_pSeries ; 
 int /*<<< orphan*/  pci_dma_bus_setup_pSeriesLP ; 
 int /*<<< orphan*/  pci_dma_dev_setup_pSeries ; 
 int /*<<< orphan*/  pci_dma_dev_setup_pSeriesLP ; 
 TYPE_1__ pseries_pci_controller_ops ; 
 int /*<<< orphan*/  register_memory_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pci_dma_ops (int /*<<< orphan*/ *) ; 

void iommu_init_early_pSeries(void)
{
	if (of_chosen && of_get_property(of_chosen, "linux,iommu-off", NULL))
		return;

	if (firmware_has_feature(FW_FEATURE_LPAR)) {
		pseries_pci_controller_ops.dma_bus_setup = pci_dma_bus_setup_pSeriesLP;
		pseries_pci_controller_ops.dma_dev_setup = pci_dma_dev_setup_pSeriesLP;
		if (!disable_ddw)
			pseries_pci_controller_ops.iommu_bypass_supported =
				iommu_bypass_supported_pSeriesLP;
	} else {
		pseries_pci_controller_ops.dma_bus_setup = pci_dma_bus_setup_pSeries;
		pseries_pci_controller_ops.dma_dev_setup = pci_dma_dev_setup_pSeries;
	}


	of_reconfig_notifier_register(&iommu_reconfig_nb);
	register_memory_notifier(&iommu_mem_nb);

	/*
	 * Secure guest memory is inacessible to devices so regular DMA isn't
	 * possible.
	 *
	 * In that case keep devices' dma_map_ops as NULL so that the generic
	 * DMA code path will use SWIOTLB to bounce buffers for DMA.
	 */
	if (!is_secure_guest())
		set_pci_dma_ops(&dma_iommu_ops);
}