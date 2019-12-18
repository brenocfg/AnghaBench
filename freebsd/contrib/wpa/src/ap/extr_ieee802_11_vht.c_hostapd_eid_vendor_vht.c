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
struct ieee80211_vht_operation {int dummy; } ;
struct ieee80211_vht_capabilities {int dummy; } ;
struct hostapd_data {TYPE_1__* iface; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_mode; } ;

/* Variables and functions */
 int OUI_BROADCOM ; 
 int /*<<< orphan*/  VENDOR_VHT_SUBTYPE ; 
 int VENDOR_VHT_TYPE ; 
 int /*<<< orphan*/  WLAN_EID_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * hostapd_eid_vht_capabilities (struct hostapd_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hostapd_eid_vht_operation (struct hostapd_data*,int /*<<< orphan*/ *) ; 

u8 * hostapd_eid_vendor_vht(struct hostapd_data *hapd, u8 *eid)
{
	u8 *pos = eid;

	if (!hapd->iface->current_mode)
		return eid;

	*pos++ = WLAN_EID_VENDOR_SPECIFIC;
	*pos++ = (5 +		/* The Vendor OUI, type and subtype */
		  2 + sizeof(struct ieee80211_vht_capabilities) +
		  2 + sizeof(struct ieee80211_vht_operation));

	WPA_PUT_BE32(pos, (OUI_BROADCOM << 8) | VENDOR_VHT_TYPE);
	pos += 4;
	*pos++ = VENDOR_VHT_SUBTYPE;
	pos = hostapd_eid_vht_capabilities(hapd, pos, 0);
	pos = hostapd_eid_vht_operation(hapd, pos);

	return pos;
}