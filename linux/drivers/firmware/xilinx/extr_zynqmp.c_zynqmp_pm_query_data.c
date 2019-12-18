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
typedef  int /*<<< orphan*/  u32 ;
struct zynqmp_pm_query_data {scalar_t__ qid; int /*<<< orphan*/  arg3; int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; } ;

/* Variables and functions */
 scalar_t__ PM_QID_CLOCK_GET_NAME ; 
 int /*<<< orphan*/  PM_QUERY_DATA ; 
 int zynqmp_pm_invoke_fn (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zynqmp_pm_query_data(struct zynqmp_pm_query_data qdata, u32 *out)
{
	int ret;

	ret = zynqmp_pm_invoke_fn(PM_QUERY_DATA, qdata.qid, qdata.arg1,
				  qdata.arg2, qdata.arg3, out);

	/*
	 * For clock name query, all bytes in SMC response are clock name
	 * characters and return code is always success. For invalid clocks,
	 * clock name bytes would be zeros.
	 */
	return qdata.qid == PM_QID_CLOCK_GET_NAME ? 0 : ret;
}