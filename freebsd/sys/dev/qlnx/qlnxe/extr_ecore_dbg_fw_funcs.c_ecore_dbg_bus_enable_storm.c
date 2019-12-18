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
typedef  scalar_t__ u8 ;
struct storm_defs {size_t block_id; } ;
struct dbg_bus_data {scalar_t__ state; int hw_dwords; int /*<<< orphan*/  num_enabled_storms; struct dbg_bus_storm_data* storms; scalar_t__ unify_inputs; } ;
struct dbg_tools_data {scalar_t__* block_in_reset; struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_storm_data {int enabled; int /*<<< orphan*/  hw_id; scalar_t__ mode; } ;
typedef  enum dbg_storms { ____Placeholder_dbg_storms } dbg_storms ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
typedef  enum dbg_bus_storm_modes { ____Placeholder_dbg_bus_storm_modes } dbg_bus_storm_modes ;

/* Variables and functions */
 scalar_t__ DBG_BUS_STATE_READY ; 
 int DBG_STATUS_BLOCK_IN_RESET ; 
 int DBG_STATUS_DBG_BLOCK_NOT_RESET ; 
 int DBG_STATUS_HW_ONLY_RECORDING ; 
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_STORM_ALREADY_ENABLED ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 int MAX_DBG_BUS_STORM_MODES ; 
 int MAX_DBG_STORMS ; 
 struct storm_defs* s_storm_defs ; 

enum dbg_status ecore_dbg_bus_enable_storm(struct ecore_hwfn *p_hwfn,
										   enum dbg_storms storm_id,
										   enum dbg_bus_storm_modes storm_mode)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_data *bus = &dev_data->bus;
	struct dbg_bus_storm_data *storm_bus;
	struct storm_defs *storm;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_enable_storm: storm = %d, storm_mode = %d\n", storm_id, storm_mode);

	if (bus->state != DBG_BUS_STATE_READY)
		return DBG_STATUS_DBG_BLOCK_NOT_RESET;
	if (bus->hw_dwords >= 4)
		return DBG_STATUS_HW_ONLY_RECORDING;
	if (storm_id >= MAX_DBG_STORMS)
		return DBG_STATUS_INVALID_ARGS;
	if (storm_mode >= MAX_DBG_BUS_STORM_MODES)
		return DBG_STATUS_INVALID_ARGS;
	if (bus->unify_inputs)
		return DBG_STATUS_INVALID_ARGS;
	if (bus->storms[storm_id].enabled)
		return DBG_STATUS_STORM_ALREADY_ENABLED;

	storm = &s_storm_defs[storm_id];
	storm_bus = &bus->storms[storm_id];

	if (dev_data->block_in_reset[storm->block_id])
		return DBG_STATUS_BLOCK_IN_RESET;

	storm_bus->enabled = true;
	storm_bus->mode = (u8)storm_mode;
	storm_bus->hw_id = bus->num_enabled_storms;

	bus->num_enabled_storms++;

	return DBG_STATUS_OK;
}