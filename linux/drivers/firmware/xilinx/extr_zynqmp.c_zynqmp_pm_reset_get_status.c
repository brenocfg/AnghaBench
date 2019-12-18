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
typedef  enum zynqmp_pm_reset { ____Placeholder_zynqmp_pm_reset } zynqmp_pm_reset ;

/* Variables and functions */
 int EINVAL ; 
 int PAYLOAD_ARG_CNT ; 
 int /*<<< orphan*/  PM_RESET_GET_STATUS ; 
 int zynqmp_pm_invoke_fn (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zynqmp_pm_reset_get_status(const enum zynqmp_pm_reset reset,
				      u32 *status)
{
	u32 ret_payload[PAYLOAD_ARG_CNT];
	int ret;

	if (!status)
		return -EINVAL;

	ret = zynqmp_pm_invoke_fn(PM_RESET_GET_STATUS, reset, 0,
				  0, 0, ret_payload);
	*status = ret_payload[1];

	return ret;
}