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
 struct dma_map_ops const* pci_dma_ops ; 

void set_pci_dma_ops(const struct dma_map_ops *dma_ops)
{
	pci_dma_ops = dma_ops;
}