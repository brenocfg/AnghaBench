#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hostapd_iface {TYPE_1__* conf; } ;
struct TYPE_2__ {unsigned int airtime_update_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int get_airtime_policy_update_timeout(struct hostapd_iface *iface,
					     unsigned int *sec,
					     unsigned int *usec)
{
	unsigned int update_int = iface->conf->airtime_update_interval;

	if (!update_int) {
		wpa_printf(MSG_ERROR,
			   "Airtime policy: Invalid airtime policy update interval %u",
			   update_int);
		return -1;
	}

	*sec = update_int / 1000;
	*usec = (update_int % 1000) * 1000;

	return 0;
}