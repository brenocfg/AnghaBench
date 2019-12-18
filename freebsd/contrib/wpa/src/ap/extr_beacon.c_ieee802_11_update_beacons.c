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
struct hostapd_iface {size_t num_bss; TYPE_1__** bss; } ;
struct TYPE_2__ {scalar_t__ started; scalar_t__ beacon_set_done; } ;

/* Variables and functions */
 scalar_t__ ieee802_11_set_beacon (TYPE_1__*) ; 

int ieee802_11_update_beacons(struct hostapd_iface *iface)
{
	size_t i;
	int ret = 0;

	for (i = 0; i < iface->num_bss; i++) {
		if (iface->bss[i]->beacon_set_done && iface->bss[i]->started &&
		    ieee802_11_set_beacon(iface->bss[i]) < 0)
			ret = -1;
	}

	return ret;
}