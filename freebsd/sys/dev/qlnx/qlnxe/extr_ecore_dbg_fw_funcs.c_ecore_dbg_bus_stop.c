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
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct dbg_bus_data {scalar_t__ state; scalar_t__ trigger_en; } ;
struct dbg_tools_data {struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 scalar_t__ DBG_BUS_STATE_RECORDING ; 
 scalar_t__ DBG_BUS_STATE_STOPPED ; 
 int /*<<< orphan*/  DBG_REG_CPU_TIMEOUT ; 
 int /*<<< orphan*/  DBG_REG_TRIGGER_STATUS_CUR_STATE ; 
 int DBG_STATUS_DATA_DIDNT_TRIGGER ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_RECORDING_NOT_STARTED ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 int /*<<< orphan*/  FLUSH_DELAY_MS ; 
 scalar_t__ MAX_TRIGGER_STATES ; 
 int /*<<< orphan*/  OSAL_MSLEEP (int /*<<< orphan*/ ) ; 
 int ecore_bus_disable_inputs (struct ecore_hwfn*,struct ecore_ptt*,int) ; 
 int /*<<< orphan*/  ecore_bus_enable_dbg_block (struct ecore_hwfn*,struct ecore_ptt*,int) ; 
 scalar_t__ ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum dbg_status ecore_dbg_bus_stop(struct ecore_hwfn *p_hwfn,
								   struct ecore_ptt *p_ptt)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_data *bus = &dev_data->bus;
	enum dbg_status status = DBG_STATUS_OK;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_stop\n");

	if (bus->state != DBG_BUS_STATE_RECORDING)
		return DBG_STATUS_RECORDING_NOT_STARTED;

	status = ecore_bus_disable_inputs(p_hwfn, p_ptt, true);
	if (status != DBG_STATUS_OK)
		return status;

	ecore_wr(p_hwfn, p_ptt, DBG_REG_CPU_TIMEOUT, 1);

	OSAL_MSLEEP(FLUSH_DELAY_MS);

	ecore_bus_enable_dbg_block(p_hwfn, p_ptt, false);

	/* Check if trigger worked */
	if (bus->trigger_en) {
		u32 trigger_state = ecore_rd(p_hwfn, p_ptt, DBG_REG_TRIGGER_STATUS_CUR_STATE);

		if (trigger_state != MAX_TRIGGER_STATES)
			return DBG_STATUS_DATA_DIDNT_TRIGGER;
	}

	bus->state = DBG_BUS_STATE_STOPPED;

	return status;
}