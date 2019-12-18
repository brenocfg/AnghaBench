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
struct wpa_priv_interface {int /*<<< orphan*/ * drv_priv; TYPE_1__* driver; } ;
struct wpa_driver_auth_params {scalar_t__ ssid_len; size_t ie_len; size_t auth_data_len; int /*<<< orphan*/ * auth_data; int /*<<< orphan*/ * ie; int /*<<< orphan*/  p2p; int /*<<< orphan*/  local_state_change; int /*<<< orphan*/  wep_tx_keyidx; scalar_t__* wep_key_len; int /*<<< orphan*/ * wep_key; int /*<<< orphan*/  auth_alg; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; int /*<<< orphan*/  freq; } ;
struct privsep_cmd_authenticate {int ie_len; int auth_data_len; scalar_t__ ssid_len; int /*<<< orphan*/  p2p; int /*<<< orphan*/  local_state_change; int /*<<< orphan*/  wep_tx_keyidx; scalar_t__* wep_key_len; int /*<<< orphan*/ * wep_key; int /*<<< orphan*/  auth_alg; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_2__ {int (* authenticate ) (int /*<<< orphan*/ *,struct wpa_driver_auth_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ SSID_MAX_LEN ; 
 int /*<<< orphan*/  os_memset (struct wpa_driver_auth_params*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ *,struct wpa_driver_auth_params*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void wpa_priv_cmd_authenticate(struct wpa_priv_interface *iface,
				      void *buf, size_t len)
{
	struct wpa_driver_auth_params params;
	struct privsep_cmd_authenticate *auth;
	int res, i;

	if (iface->drv_priv == NULL || iface->driver->authenticate == NULL)
		return;

	if (len < sizeof(*auth)) {
		wpa_printf(MSG_DEBUG, "Invalid authentication request");
		return;
	}

	auth = buf;
	if (sizeof(*auth) + auth->ie_len + auth->auth_data_len > len) {
		wpa_printf(MSG_DEBUG, "Authentication request overflow");
		return;
	}

	os_memset(&params, 0, sizeof(params));
	params.freq = auth->freq;
	params.bssid = auth->bssid;
	params.ssid = auth->ssid;
	if (auth->ssid_len > SSID_MAX_LEN)
		return;
	params.ssid_len = auth->ssid_len;
	params.auth_alg = auth->auth_alg;
	for (i = 0; i < 4; i++) {
		if (auth->wep_key_len[i]) {
			params.wep_key[i] = auth->wep_key[i];
			params.wep_key_len[i] = auth->wep_key_len[i];
		}
	}
	params.wep_tx_keyidx = auth->wep_tx_keyidx;
	params.local_state_change = auth->local_state_change;
	params.p2p = auth->p2p;
	if (auth->ie_len) {
		params.ie = (u8 *) (auth + 1);
		params.ie_len = auth->ie_len;
	}
	if (auth->auth_data_len) {
		params.auth_data = ((u8 *) (auth + 1)) + auth->ie_len;
		params.auth_data_len = auth->auth_data_len;
	}

	res = iface->driver->authenticate(iface->drv_priv, &params);
	wpa_printf(MSG_DEBUG, "drv->authenticate: res=%d", res);
}