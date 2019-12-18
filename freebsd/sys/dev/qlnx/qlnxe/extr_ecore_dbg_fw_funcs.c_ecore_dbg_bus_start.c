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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct ecore_ptt {int dummy; } ;
struct dbg_bus_data {scalar_t__ state; TYPE_2__* storms; scalar_t__ num_enabled_storms; TYPE_1__* blocks; scalar_t__ num_enabled_blocks; scalar_t__ filter_post_trigger; scalar_t__ filter_pre_trigger; scalar_t__ trigger_en; scalar_t__ filter_en; int /*<<< orphan*/  rcv_from_other_engine; } ;
struct dbg_tools_data {struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum dbg_storms { ____Placeholder_dbg_storms } dbg_storms ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
typedef  enum dbg_bus_filter_types { ____Placeholder_dbg_bus_filter_types } dbg_bus_filter_types ;
typedef  enum block_id { ____Placeholder_block_id } block_id ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; int /*<<< orphan*/  line_num; } ;

/* Variables and functions */
 size_t BLOCK_DBG ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_ENABLE_MASK ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_FORCE_FRAME_MASK ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_FORCE_VALID_MASK ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_RIGHT_SHIFT ; 
 int DBG_BUS_FILTER_TYPE_OFF ; 
 int DBG_BUS_FILTER_TYPE_ON ; 
 int DBG_BUS_FILTER_TYPE_POST ; 
 int DBG_BUS_FILTER_TYPE_PRE ; 
 scalar_t__ DBG_BUS_STATE_READY ; 
 scalar_t__ DBG_BUS_STATE_RECORDING ; 
 int /*<<< orphan*/  DBG_REG_FILTER_ENABLE ; 
 int /*<<< orphan*/  DBG_REG_TIMESTAMP ; 
 int DBG_STATUS_DBG_BLOCK_NOT_RESET ; 
 int DBG_STATUS_NO_INPUT_ENABLED ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_TOO_MANY_INPUTS ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 int /*<<< orphan*/  GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MAX_BLOCK_ID ; 
 size_t MAX_DBG_STORMS ; 
 int /*<<< orphan*/  ecore_bus_enable_dbg_block (struct ecore_hwfn*,struct ecore_ptt*,int) ; 
 int /*<<< orphan*/  ecore_bus_enable_storm (struct ecore_hwfn*,struct ecore_ptt*,int) ; 
 int /*<<< orphan*/  ecore_config_block_inputs (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_config_dbg_block_client_mask (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int ecore_config_dbg_block_framing_mode (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_config_dbg_line (struct ecore_hwfn*,struct ecore_ptt*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_config_storm_inputs (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum dbg_status ecore_dbg_bus_start(struct ecore_hwfn *p_hwfn,
									struct ecore_ptt *p_ptt)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_data *bus = &dev_data->bus;
	enum dbg_bus_filter_types filter_type;
	enum dbg_status status;
	u32 block_id;
	u8 storm_id;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_start\n");

	if (bus->state != DBG_BUS_STATE_READY)
		return DBG_STATUS_DBG_BLOCK_NOT_RESET;

	/* Check if any input was enabled */
	if (!bus->num_enabled_storms &&
		!bus->num_enabled_blocks &&
		!bus->rcv_from_other_engine)
		return DBG_STATUS_NO_INPUT_ENABLED;

	/* Check if too many input types were enabled (storm+dbgmux) */
	if (bus->num_enabled_storms && bus->num_enabled_blocks)
		return DBG_STATUS_TOO_MANY_INPUTS;

	/* Configure framing mode */
	if ((status = ecore_config_dbg_block_framing_mode(p_hwfn, p_ptt)) != DBG_STATUS_OK)
		return status;

	/* Configure DBG block for Storm inputs */
	if (bus->num_enabled_storms)
		if ((status = ecore_config_storm_inputs(p_hwfn, p_ptt)) != DBG_STATUS_OK)
			return status;

	/* Configure DBG block for block inputs */
	if (bus->num_enabled_blocks)
		ecore_config_block_inputs(p_hwfn, p_ptt);

	/* Configure filter type */
	if (bus->filter_en) {
		if (bus->trigger_en) {
			if (bus->filter_pre_trigger)
				filter_type = bus->filter_post_trigger ? DBG_BUS_FILTER_TYPE_ON : DBG_BUS_FILTER_TYPE_PRE;
			else
				filter_type = bus->filter_post_trigger ? DBG_BUS_FILTER_TYPE_POST : DBG_BUS_FILTER_TYPE_OFF;
		}
		else {
			filter_type = DBG_BUS_FILTER_TYPE_ON;
		}
	}
	else {
		filter_type = DBG_BUS_FILTER_TYPE_OFF;
	}
	ecore_wr(p_hwfn, p_ptt, DBG_REG_FILTER_ENABLE, filter_type);

	/* Restart timestamp */
	ecore_wr(p_hwfn, p_ptt, DBG_REG_TIMESTAMP, 0);

	/* Enable debug block */
	ecore_bus_enable_dbg_block(p_hwfn, p_ptt, 1);

	/* Configure enabled blocks - must be done before the DBG block is
	 * enabled.
	 */
	if (dev_data->bus.num_enabled_blocks) {
		for (block_id = 0; block_id < MAX_BLOCK_ID; block_id++) {
			if (!GET_FIELD(dev_data->bus.blocks[block_id].data, DBG_BUS_BLOCK_DATA_ENABLE_MASK) || block_id == BLOCK_DBG)
				continue;

			ecore_config_dbg_line(p_hwfn, p_ptt, (enum block_id)block_id,
				dev_data->bus.blocks[block_id].line_num,
				GET_FIELD(dev_data->bus.blocks[block_id].data, DBG_BUS_BLOCK_DATA_ENABLE_MASK),
				GET_FIELD(dev_data->bus.blocks[block_id].data, DBG_BUS_BLOCK_DATA_RIGHT_SHIFT),
				GET_FIELD(dev_data->bus.blocks[block_id].data, DBG_BUS_BLOCK_DATA_FORCE_VALID_MASK),
				GET_FIELD(dev_data->bus.blocks[block_id].data, DBG_BUS_BLOCK_DATA_FORCE_FRAME_MASK));
		}
	}

	/* Configure client mask */
	ecore_config_dbg_block_client_mask(p_hwfn, p_ptt);

	/* Configure enabled Storms - must be done after the DBG block is
	 * enabled.
	 */
	if (dev_data->bus.num_enabled_storms)
		for (storm_id = 0; storm_id < MAX_DBG_STORMS; storm_id++)
			if (dev_data->bus.storms[storm_id].enabled)
				ecore_bus_enable_storm(p_hwfn, p_ptt, (enum dbg_storms)storm_id);

	dev_data->bus.state = DBG_BUS_STATE_RECORDING;

	return DBG_STATUS_OK;
}