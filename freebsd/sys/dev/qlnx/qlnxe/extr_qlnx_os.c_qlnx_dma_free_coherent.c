#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  qlnxr_debug; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_1__ qlnx_host_t ;
struct TYPE_7__ {scalar_t__ dma_addr; int /*<<< orphan*/  dma_b; scalar_t__ dma_tag; scalar_t__ dma_map; } ;
typedef  TYPE_2__ qlnx_dma_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  QL_DPRINT5 (TYPE_1__*,char*,void*,void*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  qlnx_free_dmabuf (TYPE_1__*,TYPE_2__*) ; 

void
qlnx_dma_free_coherent(void *ecore_dev, void *v_addr, bus_addr_t phys,
	uint32_t size)
{
	qlnx_dma_t dma_buf, *dma_p;
	qlnx_host_t	*ha;
	device_t        dev;

	ha = (qlnx_host_t *)ecore_dev;
	dev = ha->pci_dev;

	if (v_addr == NULL)
		return;

	size = (size + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1);

	dma_p = (qlnx_dma_t *)((uint8_t *)v_addr + size);

	QL_DPRINT5(ha, "[%p %p %p %p 0x%08x ]\n",
		(void *)dma_p->dma_map, (void *)dma_p->dma_tag,
		dma_p->dma_b, (void *)dma_p->dma_addr, size);

	dma_buf = *dma_p;

	if (!ha->qlnxr_debug)
	qlnx_free_dmabuf((qlnx_host_t *)ecore_dev, &dma_buf);
	return;
}