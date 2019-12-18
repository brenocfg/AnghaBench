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
 int EINVAL ; 
 int /*<<< orphan*/  PM_IOCTL ; 
 int /*<<< orphan*/  zynqmp_is_valid_ioctl (int /*<<< orphan*/ ) ; 
 int zynqmp_pm_invoke_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zynqmp_pm_ioctl(u32 node_id, u32 ioctl_id, u32 arg1, u32 arg2,
			   u32 *out)
{
	if (!zynqmp_is_valid_ioctl(ioctl_id))
		return -EINVAL;

	return zynqmp_pm_invoke_fn(PM_IOCTL, node_id, ioctl_id,
				   arg1, arg2, out);
}