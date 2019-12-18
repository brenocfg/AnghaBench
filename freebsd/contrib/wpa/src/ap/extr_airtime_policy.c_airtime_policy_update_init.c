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
struct TYPE_2__ {scalar_t__ airtime_mode; } ;

/* Variables and functions */
 scalar_t__ AIRTIME_MODE_DYNAMIC ; 
 int /*<<< orphan*/  eloop_register_timeout (unsigned int,unsigned int,int /*<<< orphan*/ ,struct hostapd_iface*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_airtime_policy_update_timeout (struct hostapd_iface*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  update_airtime_weights ; 

int airtime_policy_update_init(struct hostapd_iface *iface)
{
	unsigned int sec, usec;

	if (iface->conf->airtime_mode < AIRTIME_MODE_DYNAMIC)
		return 0;

	if (get_airtime_policy_update_timeout(iface, &sec, &usec) < 0)
		return -1;

	eloop_register_timeout(sec, usec, update_airtime_weights, iface, NULL);
	return 0;
}