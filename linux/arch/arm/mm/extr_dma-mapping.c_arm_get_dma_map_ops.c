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
struct dma_map_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARM_LPAE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct dma_map_ops const arm_coherent_dma_ops ; 
 struct dma_map_ops const arm_dma_ops ; 

__attribute__((used)) static const struct dma_map_ops *arm_get_dma_map_ops(bool coherent)
{
	/*
	 * When CONFIG_ARM_LPAE is set, physical address can extend above
	 * 32-bits, which then can't be addressed by devices that only support
	 * 32-bit DMA.
	 * Use the generic dma-direct / swiotlb ops code in that case, as that
	 * handles bounce buffering for us.
	 */
	if (IS_ENABLED(CONFIG_ARM_LPAE))
		return NULL;
	return coherent ? &arm_coherent_dma_ops : &arm_dma_ops;
}