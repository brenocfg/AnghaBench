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
struct powernow_k8_data {scalar_t__ currfid; scalar_t__ currvid; } ;

/* Variables and functions */
 scalar_t__ core_frequency_transition (struct powernow_k8_data*,scalar_t__) ; 
 scalar_t__ core_voltage_post_transition (struct powernow_k8_data*,scalar_t__) ; 
 scalar_t__ core_voltage_pre_transition (struct powernow_k8_data*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ query_current_values_with_pending_wait (struct powernow_k8_data*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static int transition_fid_vid(struct powernow_k8_data *data,
		u32 reqfid, u32 reqvid)
{
	if (core_voltage_pre_transition(data, reqvid, reqfid))
		return 1;

	if (core_frequency_transition(data, reqfid))
		return 1;

	if (core_voltage_post_transition(data, reqvid))
		return 1;

	if (query_current_values_with_pending_wait(data))
		return 1;

	if ((reqfid != data->currfid) || (reqvid != data->currvid)) {
		pr_err("failed (cpu%d): req 0x%x 0x%x, curr 0x%x 0x%x\n",
				smp_processor_id(),
				reqfid, reqvid, data->currfid, data->currvid);
		return 1;
	}

	pr_debug("transitioned (cpu%d): new fid 0x%x, vid 0x%x\n",
		smp_processor_id(), data->currfid, data->currvid);

	return 0;
}