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

/* Variables and functions */
 int PAYLOAD_ARG_CNT ; 
 int /*<<< orphan*/  PM_CLOCK_GETSTATE ; 
 int zynqmp_pm_invoke_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zynqmp_pm_clock_getstate(u32 clock_id, u32 *state)
{
	u32 ret_payload[PAYLOAD_ARG_CNT];
	int ret;

	ret = zynqmp_pm_invoke_fn(PM_CLOCK_GETSTATE, clock_id, 0,
				  0, 0, ret_payload);
	*state = ret_payload[1];

	return ret;
}