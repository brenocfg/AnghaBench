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
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_register_timeout (unsigned int,unsigned int,int /*<<< orphan*/ ,struct hostapd_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_bss_load_update_timeout (struct hostapd_data*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  update_channel_utilization ; 

int bss_load_update_init(struct hostapd_data *hapd)
{
	unsigned int sec, usec;

	if (get_bss_load_update_timeout(hapd, &sec, &usec) < 0)
		return -1;

	eloop_register_timeout(sec, usec, update_channel_utilization, hapd,
			       NULL);
	return 0;
}