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
struct ena_host_attribute {TYPE_1__* host_info; int /*<<< orphan*/  host_info_dma_handle; int /*<<< orphan*/  host_info_dma_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; struct ena_host_attribute host_attr; } ;
struct TYPE_2__ {int ena_spec_version; } ;

/* Variables and functions */
 int ENA_COMMON_SPEC_VERSION_MAJOR ; 
 int ENA_COMMON_SPEC_VERSION_MINOR ; 
 int ENA_COM_NO_MEM ; 
 int /*<<< orphan*/  ENA_MEM_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENA_REGS_VERSION_MAJOR_VERSION_SHIFT ; 
 int /*<<< orphan*/  SZ_4K ; 
 scalar_t__ unlikely (int) ; 

int ena_com_allocate_host_info(struct ena_com_dev *ena_dev)
{
	struct ena_host_attribute *host_attr = &ena_dev->host_attr;

	ENA_MEM_ALLOC_COHERENT(ena_dev->dmadev,
			       SZ_4K,
			       host_attr->host_info,
			       host_attr->host_info_dma_addr,
			       host_attr->host_info_dma_handle);
	if (unlikely(!host_attr->host_info))
		return ENA_COM_NO_MEM;

	host_attr->host_info->ena_spec_version = ((ENA_COMMON_SPEC_VERSION_MAJOR <<
		ENA_REGS_VERSION_MAJOR_VERSION_SHIFT) |
		(ENA_COMMON_SPEC_VERSION_MINOR));

	return 0;
}