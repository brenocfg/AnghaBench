#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct TYPE_7__ {void** params; int /*<<< orphan*/  usec_ts; void* num_params; void* fmtstr_idx; } ;
typedef  TYPE_2__ qla_sp_log_entry_t ;
struct TYPE_6__ {size_t sp_log_index; int sp_log_num_entries; scalar_t__ sp_log_stop; TYPE_2__* sp_log; } ;
struct TYPE_8__ {int /*<<< orphan*/  sp_log_lock; TYPE_1__ hw; } ;
typedef  TYPE_3__ qla_host_t ;

/* Variables and functions */
 int NUM_LOG_ENTRIES ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla_get_usec_timestamp () ; 

void
ql_sp_log(qla_host_t *ha, uint16_t fmtstr_idx, uint16_t num_params,
	uint32_t param0, uint32_t param1, uint32_t param2, uint32_t param3,
	uint32_t param4)
{
	qla_sp_log_entry_t *sp_e, *sp_log;

	if (((sp_log = ha->hw.sp_log) == NULL) || ha->hw.sp_log_stop)
		return;

	mtx_lock(&ha->sp_log_lock);

	sp_e = &sp_log[ha->hw.sp_log_index];

	bzero(sp_e, sizeof (qla_sp_log_entry_t));

	sp_e->fmtstr_idx = fmtstr_idx;
	sp_e->num_params = num_params;

	sp_e->usec_ts = qla_get_usec_timestamp();

	sp_e->params[0] = param0;
	sp_e->params[1] = param1;
	sp_e->params[2] = param2;
	sp_e->params[3] = param3;
	sp_e->params[4] = param4;

	ha->hw.sp_log_index = (ha->hw.sp_log_index + 1) & (NUM_LOG_ENTRIES - 1);

	if (ha->hw.sp_log_num_entries < NUM_LOG_ENTRIES)
		ha->hw.sp_log_num_entries++;

	mtx_unlock(&ha->sp_log_lock);

	return;
}