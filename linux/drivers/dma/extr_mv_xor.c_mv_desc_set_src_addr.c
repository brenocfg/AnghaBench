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
struct mv_xor_desc_slot {scalar_t__ type; struct mv_xor_desc* hw_desc; } ;
struct mv_xor_desc {int desc_command; int /*<<< orphan*/ * phy_src_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ DMA_XOR ; 
 size_t mv_phy_src_idx (int) ; 

__attribute__((used)) static void mv_desc_set_src_addr(struct mv_xor_desc_slot *desc,
				 int index, dma_addr_t addr)
{
	struct mv_xor_desc *hw_desc = desc->hw_desc;
	hw_desc->phy_src_addr[mv_phy_src_idx(index)] = addr;
	if (desc->type == DMA_XOR)
		hw_desc->desc_command |= (1 << index);
}