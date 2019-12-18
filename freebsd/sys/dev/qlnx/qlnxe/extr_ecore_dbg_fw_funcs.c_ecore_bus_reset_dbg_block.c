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
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct block_defs {size_t reset_reg; int reset_bit_offset; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 size_t BLOCK_DBG ; 
 int ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int,int) ; 
 struct block_defs** s_block_defs ; 
 TYPE_1__* s_reset_regs_defs ; 

__attribute__((used)) static void ecore_bus_reset_dbg_block(struct ecore_hwfn *p_hwfn,
									  struct ecore_ptt *p_ptt)
{
	u32 dbg_reset_reg_addr, old_reset_reg_val, new_reset_reg_val;
	struct block_defs *dbg_block = s_block_defs[BLOCK_DBG];

	dbg_reset_reg_addr = s_reset_regs_defs[dbg_block->reset_reg].addr;
	old_reset_reg_val = ecore_rd(p_hwfn, p_ptt, dbg_reset_reg_addr);
	new_reset_reg_val = old_reset_reg_val & ~(1 << dbg_block->reset_bit_offset);

	ecore_wr(p_hwfn, p_ptt, dbg_reset_reg_addr, new_reset_reg_val);
	ecore_wr(p_hwfn, p_ptt, dbg_reset_reg_addr, old_reset_reg_val);
}