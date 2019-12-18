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
struct wpabuf {int dummy; } ;
struct hostapd_data {scalar_t__ beacon_set_done; struct wpabuf* wps_probe_resp_ie; struct wpabuf* wps_beacon_ie; } ;

/* Variables and functions */
 int hostapd_set_ap_wps_ie (struct hostapd_data*) ; 
 int /*<<< orphan*/  ieee802_11_set_beacon (struct hostapd_data*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static int hostapd_wps_set_ie_cb(void *ctx, struct wpabuf *beacon_ie,
				 struct wpabuf *probe_resp_ie)
{
	struct hostapd_data *hapd = ctx;
	wpabuf_free(hapd->wps_beacon_ie);
	hapd->wps_beacon_ie = beacon_ie;
	wpabuf_free(hapd->wps_probe_resp_ie);
	hapd->wps_probe_resp_ie = probe_resp_ie;
	if (hapd->beacon_set_done)
		ieee802_11_set_beacon(hapd);
	return hostapd_set_ap_wps_ie(hapd);
}