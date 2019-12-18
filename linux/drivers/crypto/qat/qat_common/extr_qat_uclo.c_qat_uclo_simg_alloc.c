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
struct icp_qat_fw_loader_handle {TYPE_1__* pci_dev; } ;
struct icp_firml_dram_desc {unsigned int dram_size; int /*<<< orphan*/  dram_bus_addr; void* dram_base_addr_v; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_uclo_simg_alloc(struct icp_qat_fw_loader_handle *handle,
			       struct icp_firml_dram_desc *dram_desc,
			       unsigned int size)
{
	void *vptr;
	dma_addr_t ptr;

	vptr = dma_alloc_coherent(&handle->pci_dev->dev,
				  size, &ptr, GFP_KERNEL);
	if (!vptr)
		return -ENOMEM;
	dram_desc->dram_base_addr_v = vptr;
	dram_desc->dram_bus_addr = ptr;
	dram_desc->dram_size = size;
	return 0;
}