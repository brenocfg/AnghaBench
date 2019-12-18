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

/* Variables and functions */
 int EINVAL ; 
 int PAYLOAD_ARG_CNT ; 
 int /*<<< orphan*/  PM_GET_TRUSTZONE_VERSION ; 
 scalar_t__ pm_tz_version ; 
 int zynqmp_pm_invoke_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int zynqmp_pm_get_trustzone_version(u32 *version)
{
	u32 ret_payload[PAYLOAD_ARG_CNT];
	int ret;

	if (!version)
		return -EINVAL;

	/* Check is PM trustzone version already verified */
	if (pm_tz_version > 0) {
		*version = pm_tz_version;
		return 0;
	}
	ret = zynqmp_pm_invoke_fn(PM_GET_TRUSTZONE_VERSION, 0, 0,
				  0, 0, ret_payload);
	*version = ret_payload[1];

	return ret;
}