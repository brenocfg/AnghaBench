#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_1__ qlnx_host_t ;
struct TYPE_10__ {int size; int alignment; void* dma_b; scalar_t__ dma_addr; scalar_t__ dma_tag; scalar_t__ dma_map; } ;
typedef  TYPE_2__ qlnx_dma_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  QL_DPRINT5 (TYPE_1__*,char*,void*,void*,void*,void*,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qlnx_alloc_dmabuf (TYPE_1__*,TYPE_2__*) ; 

void *
qlnx_dma_alloc_coherent(void *ecore_dev, bus_addr_t *phys, uint32_t size)
{
	qlnx_dma_t	dma_buf;
	qlnx_dma_t	*dma_p;
	qlnx_host_t	*ha;
	device_t        dev;

	ha = (qlnx_host_t *)ecore_dev;
	dev = ha->pci_dev;

	size = (size + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1);

	memset(&dma_buf, 0, sizeof (qlnx_dma_t));

	dma_buf.size = size + PAGE_SIZE;
	dma_buf.alignment = 8;

	if (qlnx_alloc_dmabuf((qlnx_host_t *)ecore_dev, &dma_buf) != 0)
		return (NULL);
	bzero((uint8_t *)dma_buf.dma_b, dma_buf.size);

	*phys = dma_buf.dma_addr;

	dma_p = (qlnx_dma_t *)((uint8_t *)dma_buf.dma_b + size);

	memcpy(dma_p, &dma_buf, sizeof(qlnx_dma_t));

	QL_DPRINT5(ha, "[%p %p %p %p 0x%08x ]\n",
		(void *)dma_buf.dma_map, (void *)dma_buf.dma_tag,
		dma_buf.dma_b, (void *)dma_buf.dma_addr, size);

	return (dma_buf.dma_b);
}