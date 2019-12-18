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
typedef  void* u32 ;
struct xilinx_axidma_desc_hw {void* next_desc_msb; void* next_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct xilinx_axidma_desc_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xilinx_dma_clean_hw_desc(struct xilinx_axidma_desc_hw *hw)
{
	u32 next_desc = hw->next_desc;
	u32 next_desc_msb = hw->next_desc_msb;

	memset(hw, 0, sizeof(struct xilinx_axidma_desc_hw));

	hw->next_desc = next_desc;
	hw->next_desc_msb = next_desc_msb;
}