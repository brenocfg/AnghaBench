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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {int next_trigger_state; } ;
struct dbg_tools_data {TYPE_1__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;

/* Variables and functions */
 int BYTES_IN_DWORD ; 
 int DBG_REG_FILTER_CNSTR_CYCLIC_0 ; 
 int DBG_REG_FILTER_CNSTR_DATA_0 ; 
 int DBG_REG_FILTER_CNSTR_DATA_MASK_0 ; 
 int DBG_REG_FILTER_CNSTR_FRAME_0 ; 
 int DBG_REG_FILTER_CNSTR_FRAME_MASK_0 ; 
 int DBG_REG_FILTER_CNSTR_MUST_0 ; 
 int DBG_REG_FILTER_CNSTR_OFFSET_0 ; 
 int DBG_REG_FILTER_CNSTR_OPRTN_0 ; 
 int DBG_REG_FILTER_CNSTR_RANGE_0 ; 
 int DBG_REG_TRIGGER_STATE_SET_CNSTR_CYCLIC_0 ; 
 int DBG_REG_TRIGGER_STATE_SET_CNSTR_DATA_0 ; 
 int DBG_REG_TRIGGER_STATE_SET_CNSTR_DATA_MASK_0 ; 
 int DBG_REG_TRIGGER_STATE_SET_CNSTR_FRAME_0 ; 
 int DBG_REG_TRIGGER_STATE_SET_CNSTR_FRAME_MASK_0 ; 
 int DBG_REG_TRIGGER_STATE_SET_CNSTR_MUST_0 ; 
 int DBG_REG_TRIGGER_STATE_SET_CNSTR_OFFSET_0 ; 
 int DBG_REG_TRIGGER_STATE_SET_CNSTR_OPRTN_0 ; 
 int DBG_REG_TRIGGER_STATE_SET_CNSTR_RANGE_0 ; 
 int MAX_CONSTRAINTS ; 
 int TRIGGER_SETS_PER_STATE ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int,int) ; 

__attribute__((used)) static void ecore_bus_set_constraint(struct ecore_hwfn *p_hwfn,
									 struct ecore_ptt *p_ptt,
									 bool is_filter,
									 u8 constraint_id,
									 u8 hw_op_val,
									 u32 data_val,
									 u32 data_mask,
									 u8 frame_bit,
									 u8 frame_mask,
									 u16 dword_offset,
									 u16 range,
									 u8 cyclic_bit,
									 u8 must_bit)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 reg_offset = constraint_id * BYTES_IN_DWORD;
	u8 curr_trigger_state;

	/* For trigger only - set register offset according to state */
	if (!is_filter) {
		curr_trigger_state = dev_data->bus.next_trigger_state - 1;
		reg_offset += curr_trigger_state * TRIGGER_SETS_PER_STATE * MAX_CONSTRAINTS * BYTES_IN_DWORD;
	}

	ecore_wr(p_hwfn, p_ptt, (is_filter ? DBG_REG_FILTER_CNSTR_OPRTN_0 : DBG_REG_TRIGGER_STATE_SET_CNSTR_OPRTN_0) + reg_offset, hw_op_val);
	ecore_wr(p_hwfn, p_ptt, (is_filter ? DBG_REG_FILTER_CNSTR_DATA_0 : DBG_REG_TRIGGER_STATE_SET_CNSTR_DATA_0) + reg_offset, data_val);
	ecore_wr(p_hwfn, p_ptt, (is_filter ? DBG_REG_FILTER_CNSTR_DATA_MASK_0 : DBG_REG_TRIGGER_STATE_SET_CNSTR_DATA_MASK_0) + reg_offset, data_mask);
	ecore_wr(p_hwfn, p_ptt, (is_filter ? DBG_REG_FILTER_CNSTR_FRAME_0 : DBG_REG_TRIGGER_STATE_SET_CNSTR_FRAME_0) + reg_offset, frame_bit);
	ecore_wr(p_hwfn, p_ptt, (is_filter ? DBG_REG_FILTER_CNSTR_FRAME_MASK_0 : DBG_REG_TRIGGER_STATE_SET_CNSTR_FRAME_MASK_0) + reg_offset, frame_mask);
	ecore_wr(p_hwfn, p_ptt, (is_filter ? DBG_REG_FILTER_CNSTR_OFFSET_0 : DBG_REG_TRIGGER_STATE_SET_CNSTR_OFFSET_0) + reg_offset, dword_offset);
	ecore_wr(p_hwfn, p_ptt, (is_filter ? DBG_REG_FILTER_CNSTR_RANGE_0 : DBG_REG_TRIGGER_STATE_SET_CNSTR_RANGE_0) + reg_offset, range);
	ecore_wr(p_hwfn, p_ptt, (is_filter ? DBG_REG_FILTER_CNSTR_CYCLIC_0 : DBG_REG_TRIGGER_STATE_SET_CNSTR_CYCLIC_0) + reg_offset, cyclic_bit);
	ecore_wr(p_hwfn, p_ptt, (is_filter ? DBG_REG_FILTER_CNSTR_MUST_0 : DBG_REG_TRIGGER_STATE_SET_CNSTR_MUST_0) + reg_offset, must_bit);
}