#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_4__ {scalar_t__ state; int timestamp_input_en; TYPE_1__* blocks; int /*<<< orphan*/  num_enabled_blocks; int /*<<< orphan*/  unify_inputs; } ;
struct dbg_tools_data {TYPE_2__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 size_t BLOCK_DBG ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_ENABLE_MASK ; 
 scalar_t__ DBG_BUS_STATE_READY ; 
 int /*<<< orphan*/  DBG_REG_TIMESTAMP_FRAME_EN ; 
 int /*<<< orphan*/  DBG_REG_TIMESTAMP_TICK ; 
 int /*<<< orphan*/  DBG_REG_TIMESTAMP_VALID_EN ; 
 int DBG_STATUS_DBG_BLOCK_NOT_RESET ; 
 int DBG_STATUS_INPUT_OVERLAP ; 
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_OK ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ecore_is_overlapping_enable_mask (struct ecore_hwfn*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum dbg_status ecore_dbg_bus_enable_timestamp(struct ecore_hwfn *p_hwfn,
											   struct ecore_ptt *p_ptt,
											   u8 valid_mask,
											   u8 frame_mask,
											   u32 tick_len)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_enable_timestamp: valid_mask = 0x%x, frame_mask = 0x%x, tick_len = %d\n", valid_mask, frame_mask, tick_len);

	if (dev_data->bus.state != DBG_BUS_STATE_READY)
		return DBG_STATUS_DBG_BLOCK_NOT_RESET;
	if (valid_mask > 0x7 || frame_mask > 0x7)
		return DBG_STATUS_INVALID_ARGS;
	if (!dev_data->bus.unify_inputs && ecore_is_overlapping_enable_mask(p_hwfn, 0x1, 0))
		return DBG_STATUS_INPUT_OVERLAP;

	dev_data->bus.timestamp_input_en = true;
	dev_data->bus.num_enabled_blocks++;

	SET_FIELD(dev_data->bus.blocks[BLOCK_DBG].data, DBG_BUS_BLOCK_DATA_ENABLE_MASK, 0x1);

	ecore_wr(p_hwfn, p_ptt, DBG_REG_TIMESTAMP_VALID_EN, valid_mask);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_TIMESTAMP_FRAME_EN, frame_mask);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_TIMESTAMP_TICK, tick_len);

	return DBG_STATUS_OK;
}