#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hostapd_data {TYPE_2__* iconf; TYPE_1__* conf; } ;
struct TYPE_4__ {unsigned int beacon_int; } ;
struct TYPE_3__ {unsigned int bss_load_update_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int get_bss_load_update_timeout(struct hostapd_data *hapd,
				       unsigned int *sec, unsigned int *usec)
{
	unsigned int update_period = hapd->conf->bss_load_update_period;
	unsigned int beacon_int = hapd->iconf->beacon_int;
	unsigned int update_timeout;

	if (!update_period || !beacon_int) {
		wpa_printf(MSG_ERROR,
			   "BSS Load: Invalid BSS load update configuration (period=%u beacon_int=%u)",
			   update_period, beacon_int);
		return -1;
	}

	update_timeout = update_period * beacon_int;

	*sec = ((update_timeout / 1000) * 1024) / 1000;
	*usec = (update_timeout % 1000) * 1024;

	return 0;
}