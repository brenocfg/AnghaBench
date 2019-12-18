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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  num_enabled_blocks; struct dbg_bus_block_data* blocks; int /*<<< orphan*/  unify_inputs; } ;
struct dbg_tools_data {size_t chip_id; TYPE_1__ bus; scalar_t__* block_in_reset; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_block_data {int /*<<< orphan*/  data; scalar_t__ line_num; } ;
struct dbg_bus_block {int dummy; } ;
struct block_defs {scalar_t__* dbg_client_id; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_ENABLE_MASK ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_FORCE_FRAME_MASK ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_FORCE_VALID_MASK ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_RIGHT_SHIFT ; 
 scalar_t__ DBG_BUS_STATE_READY ; 
 int DBG_STATUS_BLOCK_ALREADY_ENABLED ; 
 int DBG_STATUS_BLOCK_IN_RESET ; 
 int DBG_STATUS_DBG_BLOCK_NOT_RESET ; 
 int DBG_STATUS_INPUT_OVERLAP ; 
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_OK ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 scalar_t__ GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_BLOCK_ID ; 
 scalar_t__ MAX_CYCLE_VALUES_MASK ; 
 scalar_t__ MAX_DBG_BUS_CLIENTS ; 
 scalar_t__ NUM_DBG_LINES (struct dbg_bus_block*) ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int VALUES_PER_CYCLE ; 
 scalar_t__ ecore_is_overlapping_enable_mask (struct ecore_hwfn*,scalar_t__,scalar_t__) ; 
 struct dbg_bus_block* get_dbg_bus_block_desc (struct ecore_hwfn*,int) ; 
 struct block_defs** s_block_defs ; 

enum dbg_status ecore_dbg_bus_enable_block(struct ecore_hwfn *p_hwfn,
										   enum block_id block_id,
										   u8 line_num,
										   u8 enable_mask,
										   u8 right_shift,
										   u8 force_valid_mask,
										   u8 force_frame_mask)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct block_defs *block = s_block_defs[block_id];
	struct dbg_bus_block_data *block_bus;
	struct dbg_bus_block *block_desc;

	block_bus = &dev_data->bus.blocks[block_id];
	block_desc = get_dbg_bus_block_desc(p_hwfn, block_id);

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_enable_block: block = %d, line_num = %d, enable_mask = 0x%x, right_shift = %d, force_valid_mask = 0x%x, force_frame_mask = 0x%x\n", block_id, line_num, enable_mask, right_shift, force_valid_mask, force_frame_mask);

	if (dev_data->bus.state != DBG_BUS_STATE_READY)
		return DBG_STATUS_DBG_BLOCK_NOT_RESET;
	if (block_id >= MAX_BLOCK_ID)
		return DBG_STATUS_INVALID_ARGS;
	if (GET_FIELD(block_bus->data, DBG_BUS_BLOCK_DATA_ENABLE_MASK))
		return DBG_STATUS_BLOCK_ALREADY_ENABLED;
	if (block->dbg_client_id[dev_data->chip_id] == MAX_DBG_BUS_CLIENTS ||
		line_num >= NUM_DBG_LINES(block_desc) ||
		!enable_mask ||
		enable_mask > MAX_CYCLE_VALUES_MASK ||
		force_valid_mask > MAX_CYCLE_VALUES_MASK ||
		force_frame_mask > MAX_CYCLE_VALUES_MASK ||
		right_shift > VALUES_PER_CYCLE - 1)
		return DBG_STATUS_INVALID_ARGS;
	if (dev_data->block_in_reset[block_id])
		return DBG_STATUS_BLOCK_IN_RESET;
	if (!dev_data->bus.unify_inputs && ecore_is_overlapping_enable_mask(p_hwfn, enable_mask, right_shift))
		return DBG_STATUS_INPUT_OVERLAP;

	dev_data->bus.blocks[block_id].line_num = line_num;
	SET_FIELD(block_bus->data, DBG_BUS_BLOCK_DATA_ENABLE_MASK, enable_mask);
	SET_FIELD(block_bus->data, DBG_BUS_BLOCK_DATA_RIGHT_SHIFT, right_shift);
	SET_FIELD(block_bus->data, DBG_BUS_BLOCK_DATA_FORCE_VALID_MASK, force_valid_mask);
	SET_FIELD(block_bus->data, DBG_BUS_BLOCK_DATA_FORCE_FRAME_MASK, force_frame_mask);

	dev_data->bus.num_enabled_blocks++;

	return DBG_STATUS_OK;
}