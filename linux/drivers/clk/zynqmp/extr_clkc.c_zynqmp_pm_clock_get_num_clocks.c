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
struct zynqmp_pm_query_data {int /*<<< orphan*/  qid; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int (* query_data ) (struct zynqmp_pm_query_data,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int PAYLOAD_ARG_CNT ; 
 int /*<<< orphan*/  PM_QID_CLOCK_GET_NUM_CLOCKS ; 
 TYPE_1__* eemi_ops ; 
 int stub1 (struct zynqmp_pm_query_data,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zynqmp_pm_clock_get_num_clocks(u32 *nclocks)
{
	struct zynqmp_pm_query_data qdata = {0};
	u32 ret_payload[PAYLOAD_ARG_CNT];
	int ret;

	qdata.qid = PM_QID_CLOCK_GET_NUM_CLOCKS;

	ret = eemi_ops->query_data(qdata, ret_payload);
	*nclocks = ret_payload[1];

	return ret;
}