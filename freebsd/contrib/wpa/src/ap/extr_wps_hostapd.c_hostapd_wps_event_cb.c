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
union wps_event_data {int /*<<< orphan*/  pwd_auth_fail; int /*<<< orphan*/  success; int /*<<< orphan*/  fail; } ;
struct hostapd_data {int /*<<< orphan*/  wps_event_cb_ctx; int /*<<< orphan*/  (* wps_event_cb ) (int /*<<< orphan*/ ,int,union wps_event_data*) ;int /*<<< orphan*/  msg_ctx; } ;
typedef  enum wps_event { ____Placeholder_wps_event } wps_event ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPS_EVENT_ACTIVE ; 
 int /*<<< orphan*/  WPS_EVENT_DISABLE ; 
 int /*<<< orphan*/  WPS_EVENT_M2D ; 
 int /*<<< orphan*/  WPS_EVENT_OVERLAP ; 
 int /*<<< orphan*/  WPS_EVENT_SUCCESS ; 
 int /*<<< orphan*/  WPS_EVENT_TIMEOUT ; 
#define  WPS_EV_AP_PIN_SUCCESS 142 
#define  WPS_EV_ER_AP_ADD 141 
#define  WPS_EV_ER_AP_REMOVE 140 
#define  WPS_EV_ER_AP_SETTINGS 139 
#define  WPS_EV_ER_ENROLLEE_ADD 138 
#define  WPS_EV_ER_ENROLLEE_REMOVE 137 
#define  WPS_EV_ER_SET_SELECTED_REGISTRAR 136 
#define  WPS_EV_FAIL 135 
#define  WPS_EV_M2D 134 
#define  WPS_EV_PBC_ACTIVE 133 
#define  WPS_EV_PBC_DISABLE 132 
#define  WPS_EV_PBC_OVERLAP 131 
#define  WPS_EV_PBC_TIMEOUT 130 
#define  WPS_EV_PWD_AUTH_FAIL 129 
#define  WPS_EV_SUCCESS 128 
 int /*<<< orphan*/  hostapd_pwd_auth_fail (struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_wps_ap_pin_success (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_wps_event_fail (struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_wps_event_pbc_active (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_wps_event_pbc_disable (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_wps_event_pbc_overlap (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_wps_event_pbc_timeout (struct hostapd_data*) ; 
 int /*<<< orphan*/  hostapd_wps_event_success (struct hostapd_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,union wps_event_data*) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_wps_event_cb(void *ctx, enum wps_event event,
				 union wps_event_data *data)
{
	struct hostapd_data *hapd = ctx;

	switch (event) {
	case WPS_EV_M2D:
		wpa_msg(hapd->msg_ctx, MSG_INFO, WPS_EVENT_M2D);
		break;
	case WPS_EV_FAIL:
		hostapd_wps_event_fail(hapd, &data->fail);
		break;
	case WPS_EV_SUCCESS:
		hostapd_wps_event_success(hapd, &data->success);
		wpa_msg(hapd->msg_ctx, MSG_INFO, WPS_EVENT_SUCCESS);
		break;
	case WPS_EV_PWD_AUTH_FAIL:
		hostapd_pwd_auth_fail(hapd, &data->pwd_auth_fail);
		break;
	case WPS_EV_PBC_OVERLAP:
		hostapd_wps_event_pbc_overlap(hapd);
		wpa_msg(hapd->msg_ctx, MSG_INFO, WPS_EVENT_OVERLAP);
		break;
	case WPS_EV_PBC_TIMEOUT:
		hostapd_wps_event_pbc_timeout(hapd);
		wpa_msg(hapd->msg_ctx, MSG_INFO, WPS_EVENT_TIMEOUT);
		break;
	case WPS_EV_PBC_ACTIVE:
		hostapd_wps_event_pbc_active(hapd);
		wpa_msg(hapd->msg_ctx, MSG_INFO, WPS_EVENT_ACTIVE);
		break;
	case WPS_EV_PBC_DISABLE:
		hostapd_wps_event_pbc_disable(hapd);
		wpa_msg(hapd->msg_ctx, MSG_INFO, WPS_EVENT_DISABLE);
		break;
	case WPS_EV_ER_AP_ADD:
		break;
	case WPS_EV_ER_AP_REMOVE:
		break;
	case WPS_EV_ER_ENROLLEE_ADD:
		break;
	case WPS_EV_ER_ENROLLEE_REMOVE:
		break;
	case WPS_EV_ER_AP_SETTINGS:
		break;
	case WPS_EV_ER_SET_SELECTED_REGISTRAR:
		break;
	case WPS_EV_AP_PIN_SUCCESS:
		hostapd_wps_ap_pin_success(hapd);
		break;
	}
	if (hapd->wps_event_cb)
		hapd->wps_event_cb(hapd->wps_event_cb_ctx, event, data);
}