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
struct iop3xx_desc_aau {TYPE_1__* src_edc; void** src; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {void* src_addr; } ;

/* Variables and functions */
 size_t __desc_idx (int) ; 

__attribute__((used)) static inline void iop3xx_aau_desc_set_src_addr(struct iop3xx_desc_aau *hw_desc,
					int src_idx, dma_addr_t addr)
{
	if (src_idx < 4)
		hw_desc->src[src_idx] = addr;
	else
		hw_desc->src_edc[__desc_idx(src_idx)].src_addr = addr;
}