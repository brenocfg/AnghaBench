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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
#define  DMA_BIDIRECTIONAL 130 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 unsigned long TCE_PCI_READ ; 
 unsigned long TCE_PCI_WRITE ; 

unsigned long iommu_direction_to_tce_perm(enum dma_data_direction dir)
{
	switch (dir) {
	case DMA_BIDIRECTIONAL:
		return TCE_PCI_READ | TCE_PCI_WRITE;
	case DMA_FROM_DEVICE:
		return TCE_PCI_WRITE;
	case DMA_TO_DEVICE:
		return TCE_PCI_READ;
	default:
		return 0;
	}
}