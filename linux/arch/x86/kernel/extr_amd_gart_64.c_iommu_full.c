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

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,size_t) ; 
 int /*<<< orphan*/  dump_leak () ; 

__attribute__((used)) static void iommu_full(struct device *dev, size_t size, int dir)
{
	/*
	 * Ran out of IOMMU space for this operation. This is very bad.
	 * Unfortunately the drivers cannot handle this operation properly.
	 * Return some non mapped prereserved space in the aperture and
	 * let the Northbridge deal with it. This will result in garbage
	 * in the IO operation. When the size exceeds the prereserved space
	 * memory corruption will occur or random memory will be DMAed
	 * out. Hopefully no network devices use single mappings that big.
	 */

	dev_err(dev, "PCI-DMA: Out of IOMMU space for %lu bytes\n", size);
#ifdef CONFIG_IOMMU_LEAK
	dump_leak();
#endif
}