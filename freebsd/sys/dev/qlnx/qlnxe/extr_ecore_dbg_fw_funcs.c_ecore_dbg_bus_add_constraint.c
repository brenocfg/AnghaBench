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
struct dbg_bus_data {int next_trigger_state; int next_constraint_id; scalar_t__ adding_filter; struct dbg_bus_trigger_state_data* trigger_states; scalar_t__ trigger_en; int /*<<< orphan*/  filter_en; } ;
struct dbg_tools_data {struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_trigger_state_data {int /*<<< orphan*/  data; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
typedef  enum dbg_bus_constraint_ops { ____Placeholder_dbg_bus_constraint_ops } dbg_bus_constraint_ops ;
struct TYPE_2__ {int hw_op_val; scalar_t__ is_cyclic; } ;

/* Variables and functions */
 int DBG_BUS_CONSTRAINT_OP_EQ ; 
 int DBG_BUS_CONSTRAINT_OP_NE ; 
 int /*<<< orphan*/  DBG_BUS_TRIGGER_STATE_DATA_BLOCK_SHIFTED_ENABLE_MASK ; 
 int /*<<< orphan*/  DBG_BUS_TRIGGER_STATE_DATA_CONSTRAINT_DWORD_MASK ; 
 int DBG_STATUS_CANT_ADD_CONSTRAINT ; 
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_INVALID_TRIGGER_DWORD_OFFSET ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_TOO_MANY_CONSTRAINTS ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 int GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_CONSTRAINTS ; 
 int MAX_DBG_BUS_CONSTRAINT_OPS ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int VALUES_PER_CYCLE ; 
 int /*<<< orphan*/  ecore_bus_set_constraint (struct ecore_hwfn*,struct ecore_ptt*,int,int,int,int,int,int,int,int,int,int,int) ; 
 TYPE_1__* s_constraint_op_defs ; 

enum dbg_status ecore_dbg_bus_add_constraint(struct ecore_hwfn *p_hwfn,
											 struct ecore_ptt *p_ptt,
											 enum dbg_bus_constraint_ops constraint_op,
											 u32 data_val,
											 u32 data_mask,
											 bool compare_frame,
											 u8 frame_bit,
											 u8 cycle_offset,
											 u8 dword_offset_in_cycle,
											 bool is_mandatory)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_data *bus = &dev_data->bus;
	u16 dword_offset, range = 0;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_add_constraint: op = %d, data_val = 0x%x, data_mask = 0x%x, compare_frame = %d, frame_bit = %d, cycle_offset = %d, dword_offset_in_cycle = %d, is_mandatory = %d\n", constraint_op, data_val, data_mask, compare_frame, frame_bit, cycle_offset, dword_offset_in_cycle, is_mandatory);

	if (!bus->filter_en && !dev_data->bus.trigger_en)
		return DBG_STATUS_CANT_ADD_CONSTRAINT;
	if (bus->trigger_en && !bus->adding_filter && !bus->next_trigger_state)
		return DBG_STATUS_CANT_ADD_CONSTRAINT;
	if (bus->next_constraint_id >= MAX_CONSTRAINTS)
		return DBG_STATUS_TOO_MANY_CONSTRAINTS;
	if (constraint_op >= MAX_DBG_BUS_CONSTRAINT_OPS || frame_bit > 1 || dword_offset_in_cycle > 3 || (bus->adding_filter && cycle_offset > 3))
		return DBG_STATUS_INVALID_ARGS;
	if (compare_frame &&
		constraint_op != DBG_BUS_CONSTRAINT_OP_EQ &&
		constraint_op != DBG_BUS_CONSTRAINT_OP_NE)
		return DBG_STATUS_INVALID_ARGS;

	dword_offset = cycle_offset * VALUES_PER_CYCLE + dword_offset_in_cycle;

	if (!bus->adding_filter) {
		u8 curr_trigger_state_id = bus->next_trigger_state - 1;
		struct dbg_bus_trigger_state_data *trigger_state;

		trigger_state = &bus->trigger_states[curr_trigger_state_id];

		/* Check if the selected dword is enabled in the block */
		if (!(GET_FIELD(trigger_state->data, DBG_BUS_TRIGGER_STATE_DATA_BLOCK_SHIFTED_ENABLE_MASK) & (u8)(1 << dword_offset_in_cycle)))
			return DBG_STATUS_INVALID_TRIGGER_DWORD_OFFSET;

		/* Add selected dword to trigger state's dword mask */
		SET_FIELD(trigger_state->data, DBG_BUS_TRIGGER_STATE_DATA_CONSTRAINT_DWORD_MASK, GET_FIELD(trigger_state->data, DBG_BUS_TRIGGER_STATE_DATA_CONSTRAINT_DWORD_MASK) | (u8)(1 << dword_offset_in_cycle));
	}

	/* Prepare data mask and range */
	if (constraint_op == DBG_BUS_CONSTRAINT_OP_EQ ||
		constraint_op == DBG_BUS_CONSTRAINT_OP_NE) {
		data_mask = ~data_mask;
	}
	else {
		u8 lsb, width;

		/* Extract lsb and width from mask */
		if (!data_mask)
			return DBG_STATUS_INVALID_ARGS;

		for (lsb = 0; lsb < 32 && !(data_mask & 1); lsb++, data_mask >>= 1);
		for (width = 0; width < 32 - lsb && (data_mask & 1); width++, data_mask >>= 1);
		if (data_mask)
			return DBG_STATUS_INVALID_ARGS;
		range = (lsb << 5) | (width - 1);
	}

	/* Add constraint */
	ecore_bus_set_constraint(p_hwfn, p_ptt, dev_data->bus.adding_filter ? 1 : 0,
		dev_data->bus.next_constraint_id,
		s_constraint_op_defs[constraint_op].hw_op_val,
		data_val, data_mask, frame_bit,
		compare_frame ? 0 : 1, dword_offset, range,
		s_constraint_op_defs[constraint_op].is_cyclic ? 1 : 0,
		is_mandatory ? 1 : 0);

	/* If first constraint, fill other 3 constraints with dummy constraints
	 * that always match (using the same offset).
	 */
	if (!dev_data->bus.next_constraint_id) {
		u8 i;

		for (i = 1; i < MAX_CONSTRAINTS; i++)
			ecore_bus_set_constraint(p_hwfn, p_ptt, bus->adding_filter ? 1 : 0,
				i, DBG_BUS_CONSTRAINT_OP_EQ, 0, 0xffffffff,
				0, 1, dword_offset, 0, 0, 1);
	}

	bus->next_constraint_id++;

	return DBG_STATUS_OK;
}