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
typedef  void* u32 ;
struct zynqmp_pm_query_data {void* arg2; void* arg1; int /*<<< orphan*/  qid; int /*<<< orphan*/  member_0; } ;
struct parents_resp {int dummy; } ;
struct TYPE_2__ {int (* query_data ) (struct zynqmp_pm_query_data,void**) ;} ;

/* Variables and functions */
 int PAYLOAD_ARG_CNT ; 
 int /*<<< orphan*/  PM_QID_CLOCK_GET_PARENTS ; 
 TYPE_1__* eemi_ops ; 
 int /*<<< orphan*/  memcpy (struct parents_resp*,void**,int) ; 
 int stub1 (struct zynqmp_pm_query_data,void**) ; 

__attribute__((used)) static int zynqmp_pm_clock_get_parents(u32 clock_id, u32 index,
				       struct parents_resp *response)
{
	struct zynqmp_pm_query_data qdata = {0};
	u32 ret_payload[PAYLOAD_ARG_CNT];
	int ret;

	qdata.qid = PM_QID_CLOCK_GET_PARENTS;
	qdata.arg1 = clock_id;
	qdata.arg2 = index;

	ret = eemi_ops->query_data(qdata, ret_payload);
	memcpy(response, &ret_payload[1], sizeof(*response));

	return ret;
}