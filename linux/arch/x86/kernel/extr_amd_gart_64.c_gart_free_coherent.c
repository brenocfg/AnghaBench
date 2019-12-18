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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_direct_free_pages (struct device*,size_t,void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  gart_unmap_page (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gart_free_coherent(struct device *dev, size_t size, void *vaddr,
		   dma_addr_t dma_addr, unsigned long attrs)
{
	gart_unmap_page(dev, dma_addr, size, DMA_BIDIRECTIONAL, 0);
	dma_direct_free_pages(dev, size, vaddr, dma_addr, attrs);
}