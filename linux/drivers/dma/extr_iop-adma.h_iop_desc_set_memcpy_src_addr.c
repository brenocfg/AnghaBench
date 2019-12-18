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
struct iop_adma_desc_slot {struct iop3xx_desc_dma* hw_desc; } ;
struct iop3xx_desc_dma {int /*<<< orphan*/  src_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline void iop_desc_set_memcpy_src_addr(struct iop_adma_desc_slot *desc,
					dma_addr_t addr)
{
	struct iop3xx_desc_dma *hw_desc = desc->hw_desc;
	hw_desc->src_addr = addr;
}