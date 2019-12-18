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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 scalar_t__ ifnum_to_use ; 
 int /*<<< orphan*/  ipmi_register_watchdog (scalar_t__) ; 
 int /*<<< orphan*/  ipmi_unregister_watchdog (scalar_t__) ; 
 int param_set_int (char const*,struct kernel_param const*) ; 
 scalar_t__ watchdog_ifnum ; 

__attribute__((used)) static int set_param_wdog_ifnum(const char *val, const struct kernel_param *kp)
{
	int rv = param_set_int(val, kp);
	if (rv)
		return rv;
	if ((ifnum_to_use < 0) || (ifnum_to_use == watchdog_ifnum))
		return 0;

	ipmi_unregister_watchdog(watchdog_ifnum);
	ipmi_register_watchdog(ifnum_to_use);
	return 0;
}