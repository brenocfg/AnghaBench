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
struct pwmbus_ivars {int /*<<< orphan*/  pi_channel; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pwmbus_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwmbus_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  resource_int_value (char const*,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pwmbus_hinted_child(device_t dev, const char *dname, int dunit)
{
	struct pwmbus_ivars *ivars;
	device_t child;

	child = pwmbus_add_child(dev, 0, dname, dunit);

	/*
	 * If there is a channel hint, use it.  Otherwise pi_channel was
	 * initialized to zero, so that's the channel we'll use.
	 */
	ivars = device_get_ivars(child);
	resource_int_value(dname, dunit, "channel", &ivars->pi_channel);
}