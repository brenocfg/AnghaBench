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
struct wps_parse_attr {int* msg_type; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/ * registrar_nonce; } ;
struct wps_data {int /*<<< orphan*/  last_msg; int /*<<< orphan*/  mac_addr_e; int /*<<< orphan*/  error_indication; int /*<<< orphan*/  config_error; TYPE_1__* wps; int /*<<< orphan*/  state; int /*<<< orphan*/  nonce_r; } ;
struct wpabuf {int dummy; } ;
typedef  enum wps_process_res { ____Placeholder_wps_process_res } wps_process_res ;
struct TYPE_2__ {int /*<<< orphan*/  wps_upnp; int /*<<< orphan*/ * upnp_msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SEND_WSC_NACK ; 
 int /*<<< orphan*/  UPNP_WPS_WLANEVENT_TYPE_EAP ; 
 int WPS_CONTINUE ; 
 int WPS_FAILURE ; 
#define  WPS_M1 131 
#define  WPS_M3 130 
#define  WPS_M5 129 
#define  WPS_M7 128 
 int /*<<< orphan*/  WPS_NONCE_LEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upnp_wps_device_send_wlan_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_dup (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_fail_event (TYPE_1__*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_free_pending_msgs (int /*<<< orphan*/ *) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 
 int wps_process_m1 (struct wps_data*,struct wps_parse_attr*) ; 
 int wps_process_m3 (struct wps_data*,struct wpabuf const*,struct wps_parse_attr*) ; 
 int wps_process_m5 (struct wps_data*,struct wpabuf const*,struct wps_parse_attr*) ; 
 int wps_process_m7 (struct wps_data*,struct wpabuf const*,struct wps_parse_attr*) ; 
 int /*<<< orphan*/  wps_validate_m1 (struct wpabuf const*) ; 
 int /*<<< orphan*/  wps_validate_m3 (struct wpabuf const*) ; 
 int /*<<< orphan*/  wps_validate_m5 (struct wpabuf const*) ; 
 int /*<<< orphan*/  wps_validate_m7 (struct wpabuf const*) ; 

__attribute__((used)) static enum wps_process_res wps_process_wsc_msg(struct wps_data *wps,
						const struct wpabuf *msg)
{
	struct wps_parse_attr attr;
	enum wps_process_res ret = WPS_CONTINUE;

	wpa_printf(MSG_DEBUG, "WPS: Received WSC_MSG");

	if (wps_parse_msg(msg, &attr) < 0)
		return WPS_FAILURE;

	if (attr.msg_type == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No Message Type attribute");
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}

	if (*attr.msg_type != WPS_M1 &&
	    (attr.registrar_nonce == NULL ||
	     os_memcmp(wps->nonce_r, attr.registrar_nonce,
		       WPS_NONCE_LEN) != 0)) {
		wpa_printf(MSG_DEBUG, "WPS: Mismatch in registrar nonce");
		return WPS_FAILURE;
	}

	switch (*attr.msg_type) {
	case WPS_M1:
		if (wps_validate_m1(msg) < 0)
			return WPS_FAILURE;
#ifdef CONFIG_WPS_UPNP
		if (wps->wps->wps_upnp && attr.mac_addr) {
			/* Remove old pending messages when starting new run */
			wps_free_pending_msgs(wps->wps->upnp_msgs);
			wps->wps->upnp_msgs = NULL;

			upnp_wps_device_send_wlan_event(
				wps->wps->wps_upnp, attr.mac_addr,
				UPNP_WPS_WLANEVENT_TYPE_EAP, msg);
		}
#endif /* CONFIG_WPS_UPNP */
		ret = wps_process_m1(wps, &attr);
		break;
	case WPS_M3:
		if (wps_validate_m3(msg) < 0)
			return WPS_FAILURE;
		ret = wps_process_m3(wps, msg, &attr);
		if (ret == WPS_FAILURE || wps->state == SEND_WSC_NACK)
			wps_fail_event(wps->wps, WPS_M3, wps->config_error,
				       wps->error_indication, wps->mac_addr_e);
		break;
	case WPS_M5:
		if (wps_validate_m5(msg) < 0)
			return WPS_FAILURE;
		ret = wps_process_m5(wps, msg, &attr);
		if (ret == WPS_FAILURE || wps->state == SEND_WSC_NACK)
			wps_fail_event(wps->wps, WPS_M5, wps->config_error,
				       wps->error_indication, wps->mac_addr_e);
		break;
	case WPS_M7:
		if (wps_validate_m7(msg) < 0)
			return WPS_FAILURE;
		ret = wps_process_m7(wps, msg, &attr);
		if (ret == WPS_FAILURE || wps->state == SEND_WSC_NACK)
			wps_fail_event(wps->wps, WPS_M7, wps->config_error,
				       wps->error_indication, wps->mac_addr_e);
		break;
	default:
		wpa_printf(MSG_DEBUG, "WPS: Unsupported Message Type %d",
			   *attr.msg_type);
		return WPS_FAILURE;
	}

	if (ret == WPS_CONTINUE) {
		/* Save a copy of the last message for Authenticator derivation
		 */
		wpabuf_free(wps->last_msg);
		wps->last_msg = wpabuf_dup(msg);
	}

	return ret;
}