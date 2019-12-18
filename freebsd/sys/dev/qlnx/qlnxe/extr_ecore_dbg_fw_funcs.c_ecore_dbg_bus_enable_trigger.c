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
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct dbg_bus_data {scalar_t__ state; int trigger_en; int filter_pre_trigger; int filter_post_trigger; } ;
struct dbg_tools_data {struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
typedef  enum dbg_bus_pre_trigger_types { ____Placeholder_dbg_bus_pre_trigger_types } dbg_bus_pre_trigger_types ;
typedef  enum dbg_bus_post_trigger_types { ____Placeholder_dbg_bus_post_trigger_types } dbg_bus_post_trigger_types ;

/* Variables and functions */
 int DBG_BUS_POST_TRIGGER_DROP ; 
 int DBG_BUS_POST_TRIGGER_RECORD ; 
 int DBG_BUS_PRE_TRIGGER_DROP ; 
 int DBG_BUS_PRE_TRIGGER_NUM_CHUNKS ; 
 int DBG_BUS_PRE_TRIGGER_START_FROM_ZERO ; 
 scalar_t__ DBG_BUS_STATE_READY ; 
 int /*<<< orphan*/  DBG_REG_RCRD_ON_WINDOW_POST_NUM_CYCLES ; 
 int /*<<< orphan*/  DBG_REG_RCRD_ON_WINDOW_POST_TRGR_EVNT_MODE ; 
 int /*<<< orphan*/  DBG_REG_RCRD_ON_WINDOW_PRE_NUM_CHUNKS ; 
 int /*<<< orphan*/  DBG_REG_RCRD_ON_WINDOW_PRE_TRGR_EVNT_MODE ; 
 int /*<<< orphan*/  DBG_REG_TRIGGER_ENABLE ; 
 int DBG_STATUS_DBG_BLOCK_NOT_RESET ; 
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_TRIGGER_ALREADY_ENABLED ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 scalar_t__ INT_BUF_SIZE_IN_CHUNKS ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum dbg_status ecore_dbg_bus_enable_trigger(struct ecore_hwfn *p_hwfn,
											 struct ecore_ptt *p_ptt,
											 bool rec_pre_trigger,
											 u8 pre_chunks,
											 bool rec_post_trigger,
											 u32 post_cycles,
											 bool filter_pre_trigger,
											 bool filter_post_trigger)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	enum dbg_bus_post_trigger_types post_trigger_type;
	enum dbg_bus_pre_trigger_types pre_trigger_type;
	struct dbg_bus_data *bus = &dev_data->bus;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_enable_trigger: rec_pre_trigger = %d, pre_chunks = %d, rec_post_trigger = %d, post_cycles = %d, filter_pre_trigger = %d, filter_post_trigger = %d\n", rec_pre_trigger, pre_chunks, rec_post_trigger, post_cycles, filter_pre_trigger, filter_post_trigger);

	if (bus->state != DBG_BUS_STATE_READY)
		return DBG_STATUS_DBG_BLOCK_NOT_RESET;
	if (bus->trigger_en)
		return DBG_STATUS_TRIGGER_ALREADY_ENABLED;
	if (rec_pre_trigger && pre_chunks >= INT_BUF_SIZE_IN_CHUNKS)
		return DBG_STATUS_INVALID_ARGS;

	bus->trigger_en = true;
	bus->filter_pre_trigger = filter_pre_trigger;
	bus->filter_post_trigger = filter_post_trigger;

	if (rec_pre_trigger) {
		pre_trigger_type = pre_chunks ? DBG_BUS_PRE_TRIGGER_NUM_CHUNKS : DBG_BUS_PRE_TRIGGER_START_FROM_ZERO;
		ecore_wr(p_hwfn, p_ptt, DBG_REG_RCRD_ON_WINDOW_PRE_NUM_CHUNKS, pre_chunks);
	}
	else {
		pre_trigger_type = DBG_BUS_PRE_TRIGGER_DROP;
	}

	if (rec_post_trigger) {
		post_trigger_type = DBG_BUS_POST_TRIGGER_RECORD;
		ecore_wr(p_hwfn, p_ptt, DBG_REG_RCRD_ON_WINDOW_POST_NUM_CYCLES, post_cycles ? post_cycles : 0xffffffff);
	}
	else {
		post_trigger_type = DBG_BUS_POST_TRIGGER_DROP;
	}

	ecore_wr(p_hwfn, p_ptt, DBG_REG_RCRD_ON_WINDOW_PRE_TRGR_EVNT_MODE, pre_trigger_type);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_RCRD_ON_WINDOW_POST_TRGR_EVNT_MODE, post_trigger_type);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_TRIGGER_ENABLE, 1);

	return DBG_STATUS_OK;
}