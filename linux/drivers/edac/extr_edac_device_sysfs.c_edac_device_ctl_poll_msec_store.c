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
struct edac_device_ctl_info {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  edac_device_reset_delay_period (struct edac_device_ctl_info*,unsigned long) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t edac_device_ctl_poll_msec_store(struct edac_device_ctl_info
					*ctl_info, const char *data,
					size_t count)
{
	unsigned long value;

	/* get the value and enforce that it is non-zero, must be at least
	 * one millisecond for the delay period, between scans
	 * Then cancel last outstanding delay for the work request
	 * and set a new one.
	 */
	value = simple_strtoul(data, NULL, 0);
	edac_device_reset_delay_period(ctl_info, value);

	return count;
}