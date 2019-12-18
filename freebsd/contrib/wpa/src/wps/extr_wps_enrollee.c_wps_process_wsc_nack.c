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
typedef  scalar_t__ u16 ;
struct wps_parse_attr {scalar_t__* msg_type; int /*<<< orphan*/ * config_error; int /*<<< orphan*/ * enrollee_nonce; int /*<<< orphan*/ * registrar_nonce; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_addr; } ;
struct wps_data {int state; TYPE_1__ peer_dev; int /*<<< orphan*/  error_indication; int /*<<< orphan*/  wps; int /*<<< orphan*/ * nonce_e; int /*<<< orphan*/ * nonce_r; } ;
struct wpabuf {int dummy; } ;
typedef  enum wps_process_res { ____Placeholder_wps_process_res } wps_process_res ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  RECV_M4 130 
#define  RECV_M6 129 
#define  RECV_M8 128 
 int SEND_WSC_NACK ; 
 scalar_t__ WPA_GET_BE16 (int /*<<< orphan*/ *) ; 
 int WPS_FAILURE ; 
 int /*<<< orphan*/  WPS_M3 ; 
 int /*<<< orphan*/  WPS_M5 ; 
 int /*<<< orphan*/  WPS_M7 ; 
 int /*<<< orphan*/  WPS_NONCE_LEN ; 
 scalar_t__ WPS_WSC_NACK ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wps_fail_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_parse_msg (struct wpabuf const*,struct wps_parse_attr*) ; 

__attribute__((used)) static enum wps_process_res wps_process_wsc_nack(struct wps_data *wps,
						 const struct wpabuf *msg)
{
	struct wps_parse_attr attr;
	u16 config_error;

	wpa_printf(MSG_DEBUG, "WPS: Received WSC_NACK");

	if (wps_parse_msg(msg, &attr) < 0)
		return WPS_FAILURE;

	if (attr.msg_type == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No Message Type attribute");
		return WPS_FAILURE;
	}

	if (*attr.msg_type != WPS_WSC_NACK) {
		wpa_printf(MSG_DEBUG, "WPS: Invalid Message Type %d",
			   *attr.msg_type);
		return WPS_FAILURE;
	}

	if (attr.registrar_nonce == NULL ||
	    os_memcmp(wps->nonce_r, attr.registrar_nonce, WPS_NONCE_LEN) != 0)
	{
		wpa_printf(MSG_DEBUG, "WPS: Mismatch in registrar nonce");
		wpa_hexdump(MSG_DEBUG, "WPS: Received Registrar Nonce",
			    attr.registrar_nonce, WPS_NONCE_LEN);
		wpa_hexdump(MSG_DEBUG, "WPS: Expected Registrar Nonce",
			    wps->nonce_r, WPS_NONCE_LEN);
		return WPS_FAILURE;
	}

	if (attr.enrollee_nonce == NULL ||
	    os_memcmp(wps->nonce_e, attr.enrollee_nonce, WPS_NONCE_LEN) != 0) {
		wpa_printf(MSG_DEBUG, "WPS: Mismatch in enrollee nonce");
		wpa_hexdump(MSG_DEBUG, "WPS: Received Enrollee Nonce",
			    attr.enrollee_nonce, WPS_NONCE_LEN);
		wpa_hexdump(MSG_DEBUG, "WPS: Expected Enrollee Nonce",
			    wps->nonce_e, WPS_NONCE_LEN);
		return WPS_FAILURE;
	}

	if (attr.config_error == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: No Configuration Error attribute "
			   "in WSC_NACK");
		return WPS_FAILURE;
	}

	config_error = WPA_GET_BE16(attr.config_error);
	wpa_printf(MSG_DEBUG, "WPS: Registrar terminated negotiation with "
		   "Configuration Error %d", config_error);

	switch (wps->state) {
	case RECV_M4:
		wps_fail_event(wps->wps, WPS_M3, config_error,
			       wps->error_indication, wps->peer_dev.mac_addr);
		break;
	case RECV_M6:
		wps_fail_event(wps->wps, WPS_M5, config_error,
			       wps->error_indication, wps->peer_dev.mac_addr);
		break;
	case RECV_M8:
		wps_fail_event(wps->wps, WPS_M7, config_error,
			       wps->error_indication, wps->peer_dev.mac_addr);
		break;
	default:
		break;
	}

	/* Followed by NACK if Enrollee is Supplicant or EAP-Failure if
	 * Enrollee is Authenticator */
	wps->state = SEND_WSC_NACK;

	return WPS_FAILURE;
}