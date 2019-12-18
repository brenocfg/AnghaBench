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
struct kernel_param {scalar_t__ arg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  edac_mc_reset_delay_period (unsigned int) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int edac_set_poll_msec(const char *val, const struct kernel_param *kp)
{
	unsigned int i;
	int ret;

	if (!val)
		return -EINVAL;

	ret = kstrtouint(val, 0, &i);
	if (ret)
		return ret;

	if (i < 1000)
		return -EINVAL;

	*((unsigned int *)kp->arg) = i;

	/* notify edac_mc engine to reset the poll period */
	edac_mc_reset_delay_period(i);

	return 0;
}