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
typedef  int /*<<< orphan*/  u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
struct block_defs {int /*<<< orphan*/  dbg_force_frame_addr; int /*<<< orphan*/  dbg_force_valid_addr; int /*<<< orphan*/  dbg_shift_addr; int /*<<< orphan*/  dbg_enable_addr; int /*<<< orphan*/  dbg_select_addr; } ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;

/* Variables and functions */
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct block_defs** s_block_defs ; 

__attribute__((used)) static void ecore_config_dbg_line(struct ecore_hwfn *p_hwfn,
								  struct ecore_ptt *p_ptt,
								  enum block_id block_id,
								  u8 line_id,
								  u8 enable_mask,
								  u8 right_shift,
								  u8 force_valid_mask,
								  u8 force_frame_mask)
{
	struct block_defs *block = s_block_defs[block_id];

	ecore_wr(p_hwfn, p_ptt, block->dbg_select_addr, line_id);
	ecore_wr(p_hwfn, p_ptt, block->dbg_enable_addr, enable_mask);
	ecore_wr(p_hwfn, p_ptt, block->dbg_shift_addr, right_shift);
	ecore_wr(p_hwfn, p_ptt, block->dbg_force_valid_addr, force_valid_mask);
	ecore_wr(p_hwfn, p_ptt, block->dbg_force_frame_addr, force_frame_mask);
}