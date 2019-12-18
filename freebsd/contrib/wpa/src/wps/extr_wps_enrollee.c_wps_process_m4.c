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
struct wps_parse_attr {int /*<<< orphan*/  r_snonce1; int /*<<< orphan*/  key_wrap_auth; int /*<<< orphan*/ * version2; int /*<<< orphan*/  encr_settings_len; int /*<<< orphan*/  encr_settings; int /*<<< orphan*/  r_hash2; int /*<<< orphan*/  r_hash1; int /*<<< orphan*/  authenticator; int /*<<< orphan*/  enrollee_nonce; } ;
struct wps_data {scalar_t__ state; } ;
struct wpabuf {int dummy; } ;
typedef  enum wps_process_res { ____Placeholder_wps_process_res } wps_process_res ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ RECV_M4 ; 
 scalar_t__ SEND_M5 ; 
 void* SEND_WSC_NACK ; 
 int WPS_CONTINUE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 struct wpabuf* wps_decrypt_encr_settings (struct wps_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_parse_msg (struct wpabuf*,struct wps_parse_attr*) ; 
 scalar_t__ wps_process_authenticator (struct wps_data*,int /*<<< orphan*/ ,struct wpabuf const*) ; 
 scalar_t__ wps_process_enrollee_nonce (struct wps_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_key_wrap_auth (struct wps_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_r_hash1 (struct wps_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_r_hash2 (struct wps_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_process_r_snonce1 (struct wps_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_validate_m4_encr (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum wps_process_res wps_process_m4(struct wps_data *wps,
					   const struct wpabuf *msg,
					   struct wps_parse_attr *attr)
{
	struct wpabuf *decrypted;
	struct wps_parse_attr eattr;

	wpa_printf(MSG_DEBUG, "WPS: Received M4");

	if (wps->state != RECV_M4) {
		wpa_printf(MSG_DEBUG, "WPS: Unexpected state (%d) for "
			   "receiving M4", wps->state);
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}

	if (wps_process_enrollee_nonce(wps, attr->enrollee_nonce) ||
	    wps_process_authenticator(wps, attr->authenticator, msg) ||
	    wps_process_r_hash1(wps, attr->r_hash1) ||
	    wps_process_r_hash2(wps, attr->r_hash2)) {
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}

	decrypted = wps_decrypt_encr_settings(wps, attr->encr_settings,
					      attr->encr_settings_len);
	if (decrypted == NULL) {
		wpa_printf(MSG_DEBUG, "WPS: Failed to decrypted Encrypted "
			   "Settings attribute");
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}

	if (wps_validate_m4_encr(decrypted, attr->version2 != NULL) < 0) {
		wpabuf_clear_free(decrypted);
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}

	wpa_printf(MSG_DEBUG, "WPS: Processing decrypted Encrypted Settings "
		   "attribute");
	if (wps_parse_msg(decrypted, &eattr) < 0 ||
	    wps_process_key_wrap_auth(wps, decrypted, eattr.key_wrap_auth) ||
	    wps_process_r_snonce1(wps, eattr.r_snonce1)) {
		wpabuf_clear_free(decrypted);
		wps->state = SEND_WSC_NACK;
		return WPS_CONTINUE;
	}
	wpabuf_clear_free(decrypted);

	wps->state = SEND_M5;
	return WPS_CONTINUE;
}