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
typedef  size_t u32 ;
struct ecore_ptt {int dummy; } ;
struct dbg_tools_data {size_t chip_id; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct block_defs {size_t reset_reg; int reset_bit_offset; int /*<<< orphan*/  has_reset_bit; } ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;
struct TYPE_2__ {int /*<<< orphan*/  addr; scalar_t__* exists; } ;

/* Variables and functions */
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 struct block_defs** s_block_defs ; 
 TYPE_1__* s_reset_regs_defs ; 

bool ecore_is_block_in_reset(struct ecore_hwfn *p_hwfn,
							 struct ecore_ptt *p_ptt,
							 enum block_id block_id)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct block_defs *block = s_block_defs[block_id];
	u32 reset_reg;

	if (!block->has_reset_bit)
		return false;

	reset_reg = block->reset_reg;

	return s_reset_regs_defs[reset_reg].exists[dev_data->chip_id] ?
		!(ecore_rd(p_hwfn, p_ptt, s_reset_regs_defs[reset_reg].addr) & (1 << block->reset_bit_offset)) :	true;
}