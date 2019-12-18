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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  mac_addr; } ;
struct wps_data {TYPE_2__* wps; int /*<<< orphan*/  p2p_dev_addr; TYPE_1__ peer_dev; scalar_t__ new_psk_len; } ;
struct wpabuf {int dummy; } ;
typedef  int /*<<< orphan*/  psk ;
typedef  int /*<<< orphan*/  hex ;
struct TYPE_4__ {int ap_auth_type; int network_key_len; char* network_key; scalar_t__ registrar; } ;

/* Variables and functions */
 int ATTR_NETWORK_KEY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPS_AUTH_WPA2PSK ; 
 int WPS_AUTH_WPAPSK ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,int) ; 
 int random_pool_ready () ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_snprintf_hex (char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char*,int) ; 
 int /*<<< orphan*/  wps_cb_new_psk (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wps_build_cred_network_key(struct wps_data *wps, struct wpabuf *msg)
{
	if ((wps->wps->ap_auth_type & (WPS_AUTH_WPAPSK | WPS_AUTH_WPA2PSK)) &&
	    wps->wps->network_key_len == 0) {
		char hex[65];
		u8 psk[32];
		/* Generate a random per-device PSK */
		if (random_pool_ready() != 1 ||
		    random_get_bytes(psk, sizeof(psk)) < 0) {
			wpa_printf(MSG_INFO,
				   "WPS: Could not generate random PSK");
			return -1;
		}
		wpa_hexdump_key(MSG_DEBUG, "WPS: Generated per-device PSK",
				psk, sizeof(psk));
		wpa_printf(MSG_DEBUG, "WPS:  * Network Key (len=%u)",
			   (unsigned int) wps->new_psk_len * 2);
		wpa_snprintf_hex(hex, sizeof(hex), psk, sizeof(psk));
		wpabuf_put_be16(msg, ATTR_NETWORK_KEY);
		wpabuf_put_be16(msg, sizeof(psk) * 2);
		wpabuf_put_data(msg, hex, sizeof(psk) * 2);
		if (wps->wps->registrar) {
			wps_cb_new_psk(wps->wps->registrar,
				       wps->peer_dev.mac_addr,
				       wps->p2p_dev_addr, psk, sizeof(psk));
		}
		return 0;
	}

	wpa_printf(MSG_DEBUG, "WPS:  * Network Key (len=%u)",
		   (unsigned int) wps->wps->network_key_len);
	wpabuf_put_be16(msg, ATTR_NETWORK_KEY);
	wpabuf_put_be16(msg, wps->wps->network_key_len);
	wpabuf_put_data(msg, wps->wps->network_key, wps->wps->network_key_len);
	return 0;
}