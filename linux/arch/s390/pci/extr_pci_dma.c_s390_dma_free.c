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
struct zpci_dev {int /*<<< orphan*/  allocated_pages; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  atomic64_sub (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  s390_dma_unmap_pages (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 struct zpci_dev* to_zpci (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s390_dma_free(struct device *dev, size_t size,
			  void *pa, dma_addr_t dma_handle,
			  unsigned long attrs)
{
	struct zpci_dev *zdev = to_zpci(to_pci_dev(dev));

	size = PAGE_ALIGN(size);
	atomic64_sub(size / PAGE_SIZE, &zdev->allocated_pages);
	s390_dma_unmap_pages(dev, dma_handle, size, DMA_BIDIRECTIONAL, 0);
	free_pages((unsigned long) pa, get_order(size));
}