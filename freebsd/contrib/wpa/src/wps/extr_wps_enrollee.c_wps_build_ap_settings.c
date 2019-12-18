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
struct wps_data {TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ap_settings_len; scalar_t__ ap_settings; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_cred_auth_type (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_cred_encr_type (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_cred_mac_addr (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_cred_network_key (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_cred_ssid (struct wps_data*,struct wpabuf*) ; 

__attribute__((used)) static int wps_build_ap_settings(struct wps_data *wps, struct wpabuf *plain)
{
	const u8 *start, *end;
	int ret;

	if (wps->wps->ap_settings) {
		wpa_printf(MSG_DEBUG, "WPS:  * AP Settings (pre-configured)");
		wpabuf_put_data(plain, wps->wps->ap_settings,
				wps->wps->ap_settings_len);
		return 0;
	}

	wpa_printf(MSG_DEBUG, "WPS:  * AP Settings based on current configuration");
	start = wpabuf_put(plain, 0);
	ret = wps_build_cred_ssid(wps, plain) ||
		wps_build_cred_mac_addr(wps, plain) ||
		wps_build_cred_auth_type(wps, plain) ||
		wps_build_cred_encr_type(wps, plain) ||
		wps_build_cred_network_key(wps, plain);
	end = wpabuf_put(plain, 0);

	wpa_hexdump_key(MSG_DEBUG, "WPS: Plaintext AP Settings",
			start, end - start);

	return ret;
}