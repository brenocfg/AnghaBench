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
typedef  scalar_t__ u64 ;
struct wpa_driver_nl80211_data {scalar_t__ scan_vendor_cmd_avail; } ;
struct i802_bss {struct wpa_driver_nl80211_data* drv; } ;

/* Variables and functions */
 int nl80211_abort_scan (struct i802_bss*) ; 
 int nl80211_abort_vendor_scan (struct wpa_driver_nl80211_data*,scalar_t__) ; 

int wpa_driver_nl80211_abort_scan(void *priv, u64 scan_cookie)
{
	struct i802_bss *bss = priv;
#ifdef CONFIG_DRIVER_NL80211_QCA
	struct wpa_driver_nl80211_data *drv = bss->drv;

	/*
	 * If scan_cookie is zero, a normal scan through kernel (cfg80211)
	 * was triggered, hence abort the cfg80211 scan instead of the vendor
	 * scan.
	 */
	if (drv->scan_vendor_cmd_avail && scan_cookie)
		return nl80211_abort_vendor_scan(drv, scan_cookie);
#endif /* CONFIG_DRIVER_NL80211_QCA */
	return nl80211_abort_scan(bss);
}