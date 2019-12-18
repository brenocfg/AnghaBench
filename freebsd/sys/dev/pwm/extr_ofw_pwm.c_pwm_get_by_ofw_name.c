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
typedef  int /*<<< orphan*/  pwm_channel_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ofw_bus_find_string_index (int /*<<< orphan*/ ,char*,char const*,int*) ; 
 int pwm_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
pwm_get_by_ofw_name(device_t consumer, phandle_t node, const char *name,
    pwm_channel_t *out_channel)
{
	int rv, idx;

	rv = ofw_bus_find_string_index(node, "pwm-names", name, &idx);
	if (rv != 0)
		return (rv);

	return (pwm_get_by_ofw_idx(consumer, node, idx, out_channel));
}