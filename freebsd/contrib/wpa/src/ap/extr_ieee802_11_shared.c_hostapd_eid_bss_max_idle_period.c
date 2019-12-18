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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ ap_max_inactivity; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_BSS_MAX_IDLE_PERIOD ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (int /*<<< orphan*/ *,unsigned int) ; 

u8 * hostapd_eid_bss_max_idle_period(struct hostapd_data *hapd, u8 *eid)
{
	u8 *pos = eid;

#ifdef CONFIG_WNM_AP
	if (hapd->conf->ap_max_inactivity > 0) {
		unsigned int val;
		*pos++ = WLAN_EID_BSS_MAX_IDLE_PERIOD;
		*pos++ = 3;
		val = hapd->conf->ap_max_inactivity;
		if (val > 68000)
			val = 68000;
		val *= 1000;
		val /= 1024;
		if (val == 0)
			val = 1;
		if (val > 65535)
			val = 65535;
		WPA_PUT_LE16(pos, val);
		pos += 2;
		*pos++ = 0x00; /* TODO: Protected Keep-Alive Required */
	}
#endif /* CONFIG_WNM_AP */

	return pos;
}