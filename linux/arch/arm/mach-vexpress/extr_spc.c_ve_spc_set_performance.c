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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  sem; scalar_t__ cur_rsp_mask; scalar_t__ baseaddr; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int CA15_DVFS ; 
 int CA7_DVFS ; 
 int ETIME ; 
 scalar_t__ PERF_LVL_A15 ; 
 scalar_t__ PERF_LVL_A7 ; 
 scalar_t__ RESPONSE_MASK (int) ; 
 int /*<<< orphan*/  TIMEOUT_US ; 
 scalar_t__ cluster_is_a15 (int) ; 
 scalar_t__ down_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* info ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int ve_spc_find_performance_index (int,scalar_t__) ; 
 int ve_spc_waitforcompletion (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ve_spc_set_performance(int cluster, u32 freq)
{
	u32 perf_cfg_reg;
	int ret, perf, req_type;

	if (cluster_is_a15(cluster)) {
		req_type = CA15_DVFS;
		perf_cfg_reg = PERF_LVL_A15;
	} else {
		req_type = CA7_DVFS;
		perf_cfg_reg = PERF_LVL_A7;
	}

	perf = ve_spc_find_performance_index(cluster, freq);

	if (perf < 0)
		return perf;

	if (down_timeout(&info->sem, usecs_to_jiffies(TIMEOUT_US)))
		return -ETIME;

	init_completion(&info->done);
	info->cur_rsp_mask = RESPONSE_MASK(req_type);

	writel(perf, info->baseaddr + perf_cfg_reg);
	ret = ve_spc_waitforcompletion(req_type);

	info->cur_rsp_mask = 0;
	up(&info->sem);

	return ret;
}