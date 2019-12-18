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
typedef  scalar_t__ u8 ;
struct wpa_driver_nl80211_data {size_t num_filter_ssids; TYPE_1__* filter_ssids; } ;
struct TYPE_2__ {scalar_t__ const ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_SSID ; 
 scalar_t__* get_ie (scalar_t__ const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (scalar_t__ const*,int /*<<< orphan*/ ,scalar_t__ const) ; 

__attribute__((used)) static int nl80211_scan_filtered(struct wpa_driver_nl80211_data *drv,
				 const u8 *ie, size_t ie_len)
{
	const u8 *ssid;
	size_t i;

	if (drv->filter_ssids == NULL)
		return 0;

	ssid = get_ie(ie, ie_len, WLAN_EID_SSID);
	if (ssid == NULL)
		return 1;

	for (i = 0; i < drv->num_filter_ssids; i++) {
		if (ssid[1] == drv->filter_ssids[i].ssid_len &&
		    os_memcmp(ssid + 2, drv->filter_ssids[i].ssid, ssid[1]) ==
		    0)
			return 0;
	}

	return 1;
}