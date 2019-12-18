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
struct wps_data {int /*<<< orphan*/  state; scalar_t__ er; TYPE_1__* wps; } ;
struct wpabuf {int dummy; } ;
struct TYPE_2__ {scalar_t__ ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  RECV_DONE ; 
 int /*<<< orphan*/  WPS_M8 ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_build_ap_settings (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_authenticator (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_cred (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_encr_settings (struct wps_data*,struct wpabuf*,struct wpabuf*) ; 
 scalar_t__ wps_build_enrollee_nonce (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_key_wrap_auth (struct wps_data*,struct wpabuf*) ; 
 scalar_t__ wps_build_msg_type (struct wpabuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_version (struct wpabuf*) ; 
 scalar_t__ wps_build_wfa_ext (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * wps_build_m8(struct wps_data *wps)
{
	struct wpabuf *msg, *plain;

	wpa_printf(MSG_DEBUG, "WPS: Building Message M8");

	plain = wpabuf_alloc(500);
	if (plain == NULL)
		return NULL;

	msg = wpabuf_alloc(1000);
	if (msg == NULL) {
		wpabuf_free(plain);
		return NULL;
	}

	if (wps_build_version(msg) ||
	    wps_build_msg_type(msg, WPS_M8) ||
	    wps_build_enrollee_nonce(wps, msg) ||
	    ((wps->wps->ap || wps->er) && wps_build_cred(wps, plain)) ||
	    (!wps->wps->ap && !wps->er && wps_build_ap_settings(wps, plain)) ||
	    wps_build_key_wrap_auth(wps, plain) ||
	    wps_build_encr_settings(wps, msg, plain) ||
	    wps_build_wfa_ext(msg, 0, NULL, 0, 0) ||
	    wps_build_authenticator(wps, msg)) {
		wpabuf_clear_free(plain);
		wpabuf_clear_free(msg);
		return NULL;
	}
	wpabuf_clear_free(plain);

	wps->state = RECV_DONE;
	return msg;
}