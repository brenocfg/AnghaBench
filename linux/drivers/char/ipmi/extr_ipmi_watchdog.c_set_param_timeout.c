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
 int /*<<< orphan*/  IPMI_SET_TIMEOUT_HB_IF_NECESSARY ; 
 int ipmi_set_timeout (int /*<<< orphan*/ ) ; 
 int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ watchdog_user ; 

__attribute__((used)) static int set_param_timeout(const char *val, const struct kernel_param *kp)
{
	char *endp;
	int  l;
	int  rv = 0;

	if (!val)
		return -EINVAL;
	l = simple_strtoul(val, &endp, 0);
	if (endp == val)
		return -EINVAL;

	*((int *)kp->arg) = l;
	if (watchdog_user)
		rv = ipmi_set_timeout(IPMI_SET_TIMEOUT_HB_IF_NECESSARY);

	return rv;
}