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
struct page {int dummy; } ;
struct device {int dummy; } ;
struct arm_dma_free_args {void* cpu_addr; int want_vaddr; struct page* page; int /*<<< orphan*/  size; struct device* dev; } ;
struct arm_dma_buffer {TYPE_1__* allocator; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* free ) (struct arm_dma_free_args*) ;} ;

/* Variables and functions */
 unsigned long DMA_ATTR_NO_KERNEL_MAPPING ; 
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 scalar_t__ WARN (int,char*,void*) ; 
 struct arm_dma_buffer* arm_dma_buffer_find (void*) ; 
 int /*<<< orphan*/  dma_to_pfn (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct arm_dma_buffer*) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct arm_dma_free_args*) ; 

__attribute__((used)) static void __arm_dma_free(struct device *dev, size_t size, void *cpu_addr,
			   dma_addr_t handle, unsigned long attrs,
			   bool is_coherent)
{
	struct page *page = pfn_to_page(dma_to_pfn(dev, handle));
	struct arm_dma_buffer *buf;
	struct arm_dma_free_args args = {
		.dev = dev,
		.size = PAGE_ALIGN(size),
		.cpu_addr = cpu_addr,
		.page = page,
		.want_vaddr = ((attrs & DMA_ATTR_NO_KERNEL_MAPPING) == 0),
	};

	buf = arm_dma_buffer_find(cpu_addr);
	if (WARN(!buf, "Freeing invalid buffer %p\n", cpu_addr))
		return;

	buf->allocator->free(&args);
	kfree(buf);
}