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
struct hostapd_iface {size_t num_bss; struct hostapd_data** bss; } ;
struct hostapd_data {int /*<<< orphan*/  started; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_list_timer (struct hostapd_iface*) ; 
 int /*<<< orphan*/  hostapd_acl_expire (struct hostapd_data*) ; 

void hostapd_periodic_iface(struct hostapd_iface *iface)
{
	size_t i;

	ap_list_timer(iface);

	for (i = 0; i < iface->num_bss; i++) {
		struct hostapd_data *hapd = iface->bss[i];

		if (!hapd->started)
			continue;

#ifndef CONFIG_NO_RADIUS
		hostapd_acl_expire(hapd);
#endif /* CONFIG_NO_RADIUS */
	}
}