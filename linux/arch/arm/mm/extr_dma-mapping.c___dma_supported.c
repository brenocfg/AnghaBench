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
typedef  int /*<<< orphan*/  u64 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_dma_pfn_limit ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int,int,unsigned long) ; 
 int dma_to_pfn (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_pfn ; 
 unsigned long min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dma_supported(struct device *dev, u64 mask, bool warn)
{
	unsigned long max_dma_pfn = min(max_pfn, arm_dma_pfn_limit);

	/*
	 * Translate the device's DMA mask to a PFN limit.  This
	 * PFN number includes the page which we can DMA to.
	 */
	if (dma_to_pfn(dev, mask) < max_dma_pfn) {
		if (warn)
			dev_warn(dev, "Coherent DMA mask %#llx (pfn %#lx-%#lx) covers a smaller range of system memory than the DMA zone pfn 0x0-%#lx\n",
				 mask,
				 dma_to_pfn(dev, 0), dma_to_pfn(dev, mask) + 1,
				 max_dma_pfn + 1);
		return 0;
	}

	return 1;
}