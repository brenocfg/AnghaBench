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
struct TYPE_4__ {void* hi; void* lo; } ;
struct set_timesync_ramrod_data {TYPE_2__ offset_delta; int /*<<< orphan*/  drift_adjust_period; int /*<<< orphan*/  drift_adjust_value; int /*<<< orphan*/  add_sub_drift_adjust_value; int /*<<< orphan*/  offset_cmd; int /*<<< orphan*/  drift_adjust_cmd; } ;
struct ecore_func_set_timesync_params {int /*<<< orphan*/  offset_delta; int /*<<< orphan*/  drift_adjust_period; int /*<<< orphan*/  drift_adjust_value; int /*<<< orphan*/  add_sub_drift_adjust_value; int /*<<< orphan*/  offset_cmd; int /*<<< orphan*/  drift_adjust_cmd; } ;
struct TYPE_3__ {struct ecore_func_set_timesync_params set_timesync; } ;
struct ecore_func_state_params {TYPE_1__ params; struct ecore_func_sp_obj* f_obj; } ;
struct ecore_func_sp_obj {int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 void* ECORE_CPU_TO_LE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_MEMSET (struct set_timesync_ramrod_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_SET_TIMESYNC ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int ecore_sp_post (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ecore_func_send_set_timesync(struct bxe_softc *sc,
					struct ecore_func_state_params *params)
{
	struct ecore_func_sp_obj *o = params->f_obj;
	struct set_timesync_ramrod_data *rdata =
		(struct set_timesync_ramrod_data *)o->rdata;
	ecore_dma_addr_t data_mapping = o->rdata_mapping;
	struct ecore_func_set_timesync_params *set_timesync_params =
		&params->params.set_timesync;

	ECORE_MEMSET(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->drift_adjust_cmd = set_timesync_params->drift_adjust_cmd;
	rdata->offset_cmd = set_timesync_params->offset_cmd;
	rdata->add_sub_drift_adjust_value =
		set_timesync_params->add_sub_drift_adjust_value;
	rdata->drift_adjust_value = set_timesync_params->drift_adjust_value;
	rdata->drift_adjust_period = set_timesync_params->drift_adjust_period;
	rdata->offset_delta.lo =
		ECORE_CPU_TO_LE32(U64_LO(set_timesync_params->offset_delta));
	rdata->offset_delta.hi =
		ECORE_CPU_TO_LE32(U64_HI(set_timesync_params->offset_delta));

	ECORE_MSG(sc, "Set timesync command params: drift_cmd = %d, offset_cmd = %d, add_sub_drift = %d, drift_val = %d, drift_period = %d, offset_lo = %d, offset_hi = %d\n",
	   rdata->drift_adjust_cmd, rdata->offset_cmd,
	   rdata->add_sub_drift_adjust_value, rdata->drift_adjust_value,
	   rdata->drift_adjust_period, rdata->offset_delta.lo,
	   rdata->offset_delta.hi);

	return ecore_sp_post(sc, RAMROD_CMD_ID_COMMON_SET_TIMESYNC, 0,
			     data_mapping, NONE_CONNECTION_TYPE);
}