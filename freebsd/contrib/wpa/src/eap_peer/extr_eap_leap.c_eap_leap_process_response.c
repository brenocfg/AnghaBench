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
typedef  scalar_t__ u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {void* leap_done; } ;
struct eap_method_ret {int /*<<< orphan*/  decision; int /*<<< orphan*/  allowNotifications; int /*<<< orphan*/  methodState; void* ignore; } ;
struct eap_leap_data {int /*<<< orphan*/  state; int /*<<< orphan*/  ap_challenge; int /*<<< orphan*/  ap_response; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  DECISION_UNCOND_SUCC ; 
 int /*<<< orphan*/  EAP_TYPE_LEAP ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LEAP_DONE ; 
 int LEAP_RESPONSE_LEN ; 
 scalar_t__ const LEAP_VERSION ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 void* TRUE ; 
 scalar_t__ challenge_response (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__* eap_get_config_password2 (struct eap_sm*,size_t*,int*) ; 
 scalar_t__* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf const*,size_t*) ; 
 scalar_t__ hash_nt_password_hash (scalar_t__ const*,scalar_t__*) ; 
 scalar_t__ nt_password_hash (scalar_t__ const*,size_t,scalar_t__*) ; 
 scalar_t__ os_memcmp_const (scalar_t__ const*,scalar_t__*,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static struct wpabuf * eap_leap_process_response(struct eap_sm *sm, void *priv,
						 struct eap_method_ret *ret,
						 const struct wpabuf *reqData)
{
	struct eap_leap_data *data = priv;
	const u8 *pos, *password;
	u8 response_len, pw_hash[16], pw_hash_hash[16],
		expected[LEAP_RESPONSE_LEN];
	size_t password_len, len;
	int pwhash;

	wpa_printf(MSG_DEBUG, "EAP-LEAP: Processing EAP-Response");

	password = eap_get_config_password2(sm, &password_len, &pwhash);
	if (password == NULL)
		return NULL;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_LEAP, reqData, &len);
	if (pos == NULL || len < 3) {
		wpa_printf(MSG_INFO, "EAP-LEAP: Invalid EAP-Response frame");
		ret->ignore = TRUE;
		return NULL;
	}

	if (*pos != LEAP_VERSION) {
		wpa_printf(MSG_WARNING, "EAP-LEAP: Unsupported LEAP version "
			   "%d", *pos);
		ret->ignore = TRUE;
		return NULL;
	}
	pos++;

	pos++; /* skip unused byte */

	response_len = *pos++;
	if (response_len != LEAP_RESPONSE_LEN || response_len > len - 3) {
		wpa_printf(MSG_INFO, "EAP-LEAP: Invalid response "
			   "(response_len=%d reqDataLen=%lu)",
			   response_len, (unsigned long) wpabuf_len(reqData));
		ret->ignore = TRUE;
		return NULL;
	}

	wpa_hexdump(MSG_DEBUG, "EAP-LEAP: Response from AP",
		    pos, LEAP_RESPONSE_LEN);
	os_memcpy(data->ap_response, pos, LEAP_RESPONSE_LEN);

	if (pwhash) {
		if (hash_nt_password_hash(password, pw_hash_hash)) {
			ret->ignore = TRUE;
			return NULL;
		}
	} else {
		if (nt_password_hash(password, password_len, pw_hash) ||
		    hash_nt_password_hash(pw_hash, pw_hash_hash)) {
			ret->ignore = TRUE;
			return NULL;
		}
	}
	if (challenge_response(data->ap_challenge, pw_hash_hash, expected)) {
		ret->ignore = TRUE;
		return NULL;
	}

	ret->methodState = METHOD_DONE;
	ret->allowNotifications = FALSE;

	if (os_memcmp_const(pos, expected, LEAP_RESPONSE_LEN) != 0) {
		wpa_printf(MSG_WARNING, "EAP-LEAP: AP sent an invalid "
			   "response - authentication failed");
		wpa_hexdump(MSG_DEBUG, "EAP-LEAP: Expected response from AP",
			    expected, LEAP_RESPONSE_LEN);
		ret->decision = DECISION_FAIL;
		return NULL;
	}

	ret->decision = DECISION_UNCOND_SUCC;

	/* LEAP is somewhat odd method since it sends EAP-Success in the middle
	 * of the authentication. Use special variable to transit EAP state
	 * machine to SUCCESS state. */
	sm->leap_done = TRUE;
	data->state = LEAP_DONE;

	/* No more authentication messages expected; AP will send EAPOL-Key
	 * frames if encryption is enabled. */
	return NULL;
}