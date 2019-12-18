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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_hwfn {int dummy; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
typedef  enum dbg_grc_params { ____Placeholder_dbg_grc_params } dbg_grc_params ;
struct TYPE_2__ {int /*<<< orphan*/  crash_preset_val; int /*<<< orphan*/  exclude_all_preset_val; scalar_t__ is_preset; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int DBG_GRC_PARAM_CRASH ; 
 int DBG_GRC_PARAM_EXCLUDE_ALL ; 
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_OK ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 int MAX_DBG_GRC_PARAMS ; 
 int /*<<< orphan*/  ecore_dbg_grc_init_params (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_grc_set_param (struct ecore_hwfn*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* s_grc_param_defs ; 

enum dbg_status ecore_dbg_grc_config(struct ecore_hwfn *p_hwfn,
									 enum dbg_grc_params grc_param,
									 u32 val)
{
	int i;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_grc_config: paramId = %d, val = %d\n", grc_param, val);

	/* Initializes the GRC parameters (if not initialized). Needed in order
	 * to set the default parameter values for the first time.
	 */
	ecore_dbg_grc_init_params(p_hwfn);

	if (grc_param >= MAX_DBG_GRC_PARAMS)
		return DBG_STATUS_INVALID_ARGS;
	if (val < s_grc_param_defs[grc_param].min ||
		val > s_grc_param_defs[grc_param].max)
		return DBG_STATUS_INVALID_ARGS;

	if (s_grc_param_defs[grc_param].is_preset) {

		/* Preset param */

		/* Disabling a preset is not allowed. Call
		 * dbg_grc_set_params_default instead.
		 */
		if (!val)
			return DBG_STATUS_INVALID_ARGS;

		/* Update all params with the preset values */
		for (i = 0; i < MAX_DBG_GRC_PARAMS; i++) {
			u32 preset_val;

			if (grc_param == DBG_GRC_PARAM_EXCLUDE_ALL)
				preset_val = s_grc_param_defs[i].exclude_all_preset_val;
			else if (grc_param == DBG_GRC_PARAM_CRASH)
				preset_val = s_grc_param_defs[i].crash_preset_val;
			else
				return DBG_STATUS_INVALID_ARGS;

			ecore_grc_set_param(p_hwfn, (enum dbg_grc_params)i, preset_val);
		}
	}
	else {

		/* Regular param - set its value */
		ecore_grc_set_param(p_hwfn, grc_param, val);
	}

	return DBG_STATUS_OK;
}