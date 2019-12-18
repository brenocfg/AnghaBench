#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {struct dbg_bus_storm_data* storms; } ;
struct dbg_tools_data {TYPE_1__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct TYPE_5__ {scalar_t__ max; scalar_t__ min; } ;
struct TYPE_6__ {TYPE_2__ range; } ;
struct dbg_bus_storm_data {int eid_filter_en; int eid_range_not_mask; TYPE_3__ eid_filter_params; int /*<<< orphan*/  enabled; } ;
typedef  enum dbg_storms { ____Placeholder_dbg_storms } dbg_storms ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_STORM_NOT_ENABLED ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 int MAX_DBG_STORMS ; 

enum dbg_status ecore_dbg_bus_add_eid_range_sem_filter(struct ecore_hwfn *p_hwfn,
													   enum dbg_storms storm_id,
													   u8 min_eid,
													   u8 max_eid)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_storm_data *storm_bus;

	storm_bus = &dev_data->bus.storms[storm_id];

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_add_eid_range_sem_filter: storm = %d, min_eid = 0x%x, max_eid = 0x%x\n", storm_id, min_eid, max_eid);

	if (storm_id >= MAX_DBG_STORMS)
		return DBG_STATUS_INVALID_ARGS;
	if (min_eid > max_eid)
		return DBG_STATUS_INVALID_ARGS;
	if (!storm_bus->enabled)
		return DBG_STATUS_STORM_NOT_ENABLED;

	storm_bus->eid_filter_en = 1;
	storm_bus->eid_range_not_mask = 1;
	storm_bus->eid_filter_params.range.min = min_eid;
	storm_bus->eid_filter_params.range.max = max_eid;

	return DBG_STATUS_OK;
}