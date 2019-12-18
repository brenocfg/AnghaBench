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
struct zynqmp_pm_query_data {int /*<<< orphan*/  arg1; int /*<<< orphan*/  qid; int /*<<< orphan*/  member_0; } ;
struct attr_resp {int dummy; } ;
struct TYPE_2__ {int (* query_data ) (struct zynqmp_pm_query_data,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int PAYLOAD_ARG_CNT ; 
 int /*<<< orphan*/  PM_QID_CLOCK_GET_ATTRIBUTES ; 
 TYPE_1__* eemi_ops ; 
 int /*<<< orphan*/  memcpy (struct attr_resp*,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct zynqmp_pm_query_data,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zynqmp_pm_clock_get_attributes(u32 clock_id,
					  struct attr_resp *response)
{
	struct zynqmp_pm_query_data qdata = {0};
	u32 ret_payload[PAYLOAD_ARG_CNT];
	int ret;

	qdata.qid = PM_QID_CLOCK_GET_ATTRIBUTES;
	qdata.arg1 = clock_id;

	ret = eemi_ops->query_data(qdata, ret_payload);
	memcpy(response, &ret_payload[1], sizeof(*response));

	return ret;
}