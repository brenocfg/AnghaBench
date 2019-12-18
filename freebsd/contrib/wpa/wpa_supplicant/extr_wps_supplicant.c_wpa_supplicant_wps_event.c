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
struct TYPE_2__ {int /*<<< orphan*/  enrollee; } ;
union wps_event_data {int /*<<< orphan*/  set_sel_reg; int /*<<< orphan*/  ap_settings; int /*<<< orphan*/  enrollee; int /*<<< orphan*/  ap; TYPE_1__ pwd_auth_fail; int /*<<< orphan*/  fail; int /*<<< orphan*/  m2d; } ;
struct wpa_supplicant {int /*<<< orphan*/  ap_iface; } ;
typedef  enum wps_event { ____Placeholder_wps_event } wps_event ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPS_EVENT_ACTIVE ; 
 int /*<<< orphan*/  WPS_EVENT_DISABLE ; 
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
 int /*<<< orphan*/  wpa_msg (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_ap_pwd_auth_fail (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event_er_ap_add (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event_er_ap_remove (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event_er_ap_settings (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event_er_enrollee_add (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event_er_enrollee_remove (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event_er_set_sel_reg (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event_fail (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event_m2d (struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_wps_event_success (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpa_supplicant_wps_event(void *ctx, enum wps_event event,
				     union wps_event_data *data)
{
	struct wpa_supplicant *wpa_s = ctx;
	switch (event) {
	case WPS_EV_M2D:
		wpa_supplicant_wps_event_m2d(wpa_s, &data->m2d);
		break;
	case WPS_EV_FAIL:
		wpa_supplicant_wps_event_fail(wpa_s, &data->fail);
		break;
	case WPS_EV_SUCCESS:
		wpa_supplicant_wps_event_success(wpa_s);
		break;
	case WPS_EV_PWD_AUTH_FAIL:
#ifdef CONFIG_AP
		if (wpa_s->ap_iface && data->pwd_auth_fail.enrollee)
			wpa_supplicant_ap_pwd_auth_fail(wpa_s);
#endif /* CONFIG_AP */
		break;
	case WPS_EV_PBC_OVERLAP:
		break;
	case WPS_EV_PBC_TIMEOUT:
		break;
	case WPS_EV_PBC_ACTIVE:
		wpa_msg(wpa_s, MSG_INFO, WPS_EVENT_ACTIVE);
		break;
	case WPS_EV_PBC_DISABLE:
		wpa_msg(wpa_s, MSG_INFO, WPS_EVENT_DISABLE);
		break;
	case WPS_EV_ER_AP_ADD:
		wpa_supplicant_wps_event_er_ap_add(wpa_s, &data->ap);
		break;
	case WPS_EV_ER_AP_REMOVE:
		wpa_supplicant_wps_event_er_ap_remove(wpa_s, &data->ap);
		break;
	case WPS_EV_ER_ENROLLEE_ADD:
		wpa_supplicant_wps_event_er_enrollee_add(wpa_s,
							 &data->enrollee);
		break;
	case WPS_EV_ER_ENROLLEE_REMOVE:
		wpa_supplicant_wps_event_er_enrollee_remove(wpa_s,
							    &data->enrollee);
		break;
	case WPS_EV_ER_AP_SETTINGS:
		wpa_supplicant_wps_event_er_ap_settings(wpa_s,
							&data->ap_settings);
		break;
	case WPS_EV_ER_SET_SELECTED_REGISTRAR:
		wpa_supplicant_wps_event_er_set_sel_reg(wpa_s,
							&data->set_sel_reg);
		break;
	case WPS_EV_AP_PIN_SUCCESS:
		break;
	}
}