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
struct wps_registrar {TYPE_1__* wps; } ;
struct wps_credential {int encr_type; int auth_type; } ;
struct TYPE_2__ {int (* cred_cb ) (int /*<<< orphan*/ ,struct wps_credential*) ;int /*<<< orphan*/  cb_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPS_AUTH_WPA2PSK ; 
 int WPS_AUTH_WPAPSK ; 
 int WPS_ENCR_AES ; 
 int WPS_ENCR_NONE ; 
 int WPS_ENCR_TKIP ; 
 int WPS_ENCR_WEP ; 
 int stub1 (int /*<<< orphan*/ ,struct wps_credential*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int wps_registrar_config_ap(struct wps_registrar *reg,
			    struct wps_credential *cred)
{
	wpa_printf(MSG_DEBUG, "WPS: encr_type=0x%x", cred->encr_type);
	if (!(cred->encr_type & (WPS_ENCR_NONE | WPS_ENCR_TKIP |
				 WPS_ENCR_AES))) {
		if (cred->encr_type & WPS_ENCR_WEP) {
			wpa_printf(MSG_INFO, "WPS: Reject new AP settings "
				   "due to WEP configuration");
			return -1;
		}

		wpa_printf(MSG_INFO, "WPS: Reject new AP settings due to "
			   "invalid encr_type 0x%x", cred->encr_type);
		return -1;
	}

	if ((cred->encr_type & (WPS_ENCR_TKIP | WPS_ENCR_AES)) ==
	    WPS_ENCR_TKIP) {
		wpa_printf(MSG_DEBUG, "WPS: Upgrade encr_type TKIP -> "
			   "TKIP+AES");
		cred->encr_type |= WPS_ENCR_AES;
	}

	if ((cred->auth_type & (WPS_AUTH_WPAPSK | WPS_AUTH_WPA2PSK)) ==
	    WPS_AUTH_WPAPSK) {
		wpa_printf(MSG_DEBUG, "WPS: Upgrade auth_type WPAPSK -> "
			   "WPAPSK+WPA2PSK");
		cred->auth_type |= WPS_AUTH_WPA2PSK;
	}

	if (reg->wps->cred_cb)
		return reg->wps->cred_cb(reg->wps->cb_ctx, cred);

	return -1;
}