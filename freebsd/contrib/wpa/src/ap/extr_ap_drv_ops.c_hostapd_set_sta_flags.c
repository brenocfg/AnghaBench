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
struct sta_info {int flags; scalar_t__ auth_alg; int /*<<< orphan*/  addr; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  wpa; int /*<<< orphan*/  ieee802_1x; } ;

/* Variables and functions */
 scalar_t__ WLAN_AUTH_FT ; 
 int WLAN_STA_AUTHORIZED ; 
 int WPA_STA_AUTHORIZED ; 
 int WPA_STA_MFP ; 
 int WPA_STA_SHORT_PREAMBLE ; 
 int WPA_STA_WMM ; 
 int hostapd_sta_flags_to_drv (int) ; 
 int hostapd_sta_set_flags (struct hostapd_data*,int /*<<< orphan*/ ,int,int,int) ; 

int hostapd_set_sta_flags(struct hostapd_data *hapd, struct sta_info *sta)
{
	int set_flags, total_flags, flags_and, flags_or;
	total_flags = hostapd_sta_flags_to_drv(sta->flags);
	set_flags = WPA_STA_SHORT_PREAMBLE | WPA_STA_WMM | WPA_STA_MFP;
	if (((!hapd->conf->ieee802_1x && !hapd->conf->wpa) ||
	     sta->auth_alg == WLAN_AUTH_FT) &&
	    sta->flags & WLAN_STA_AUTHORIZED)
		set_flags |= WPA_STA_AUTHORIZED;
	flags_or = total_flags & set_flags;
	flags_and = total_flags | ~set_flags;
	return hostapd_sta_set_flags(hapd, sta->addr, total_flags,
				     flags_or, flags_and);
}