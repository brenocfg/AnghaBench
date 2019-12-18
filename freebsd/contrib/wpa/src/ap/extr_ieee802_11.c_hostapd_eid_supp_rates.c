#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct hostapd_data {TYPE_3__* iconf; TYPE_2__* iface; } ;
struct TYPE_6__ {scalar_t__ require_vht; scalar_t__ ieee80211ac; scalar_t__ require_ht; scalar_t__ ieee80211n; } ;
struct TYPE_5__ {int num_rates; TYPE_1__* current_rates; } ;
struct TYPE_4__ {int rate; int flags; } ;

/* Variables and functions */
 int BSS_MEMBERSHIP_SELECTOR_HT_PHY ; 
 int BSS_MEMBERSHIP_SELECTOR_VHT_PHY ; 
 int HOSTAPD_RATE_BASIC ; 
 int /*<<< orphan*/  WLAN_EID_SUPP_RATES ; 

u8 * hostapd_eid_supp_rates(struct hostapd_data *hapd, u8 *eid)
{
	u8 *pos = eid;
	int i, num, count;

	if (hapd->iface->current_rates == NULL)
		return eid;

	*pos++ = WLAN_EID_SUPP_RATES;
	num = hapd->iface->num_rates;
	if (hapd->iconf->ieee80211n && hapd->iconf->require_ht)
		num++;
	if (hapd->iconf->ieee80211ac && hapd->iconf->require_vht)
		num++;
	if (num > 8) {
		/* rest of the rates are encoded in Extended supported
		 * rates element */
		num = 8;
	}

	*pos++ = num;
	for (i = 0, count = 0; i < hapd->iface->num_rates && count < num;
	     i++) {
		count++;
		*pos = hapd->iface->current_rates[i].rate / 5;
		if (hapd->iface->current_rates[i].flags & HOSTAPD_RATE_BASIC)
			*pos |= 0x80;
		pos++;
	}

	if (hapd->iconf->ieee80211n && hapd->iconf->require_ht && count < 8) {
		count++;
		*pos++ = 0x80 | BSS_MEMBERSHIP_SELECTOR_HT_PHY;
	}

	if (hapd->iconf->ieee80211ac && hapd->iconf->require_vht && count < 8) {
		count++;
		*pos++ = 0x80 | BSS_MEMBERSHIP_SELECTOR_VHT_PHY;
	}

	return pos;
}