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
typedef  char u8 ;
struct eap_ttls_data {int mschapv2_resp_ok; char mschapv2_ident; int /*<<< orphan*/  mschapv2_auth_response; } ;
struct eap_sm {char* identity; size_t identity_len; TYPE_1__* user; } ;
struct TYPE_2__ {int ttls_auth; int /*<<< orphan*/  password_len; int /*<<< orphan*/  password; scalar_t__ password_hash; } ;

/* Variables and functions */
 int EAP_TTLS_AUTH_MSCHAPV2 ; 
 size_t EAP_TTLS_MSCHAPV2_CHALLENGE_LEN ; 
 size_t EAP_TTLS_MSCHAPV2_RESPONSE_LEN ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  PHASE2_MSCHAPV2_RESP ; 
 scalar_t__ challenge_hash (char*,char*,char*,size_t,char*) ; 
 int /*<<< orphan*/  eap_server_mschap_rx_callback (struct eap_sm*,char*,char*,size_t,char*,char*) ; 
 char* eap_ttls_implicit_challenge (struct eap_sm*,struct eap_ttls_data*,size_t) ; 
 int /*<<< orphan*/  eap_ttls_state (struct eap_ttls_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_authenticator_response (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_authenticator_response_pwhash (int /*<<< orphan*/ ,char*,char*,char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_nt_response (char*,char*,char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  generate_nt_response_pwhash (char*,char*,char*,size_t,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_memcmp_const (char*,char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,char*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_ttls_process_phase2_mschapv2(struct eap_sm *sm,
					     struct eap_ttls_data *data,
					     u8 *challenge,
					     size_t challenge_len,
					     u8 *response, size_t response_len)
{
	u8 *chal, *username, nt_response[24], *rx_resp, *peer_challenge,
		*auth_challenge;
	size_t username_len, i;

	if (challenge == NULL || response == NULL ||
	    challenge_len != EAP_TTLS_MSCHAPV2_CHALLENGE_LEN ||
	    response_len != EAP_TTLS_MSCHAPV2_RESPONSE_LEN) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAPV2: Invalid MS-CHAP2 "
			   "attributes (challenge len %lu response len %lu)",
			   (unsigned long) challenge_len,
			   (unsigned long) response_len);
		eap_ttls_state(data, FAILURE);
		return;
	}

	if (!sm->user || !sm->user->password ||
	    !(sm->user->ttls_auth & EAP_TTLS_AUTH_MSCHAPV2)) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAPV2: No user password "
			   "configured");
		eap_ttls_state(data, FAILURE);
		return;
	}

	if (sm->identity == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAPV2: No user identity "
			   "known");
		eap_ttls_state(data, FAILURE);
		return;
	}

	/* MSCHAPv2 does not include optional domain name in the
	 * challenge-response calculation, so remove domain prefix
	 * (if present). */
	username = sm->identity;
	username_len = sm->identity_len;
	for (i = 0; i < username_len; i++) {
		if (username[i] == '\\') {
			username_len -= i + 1;
			username += i + 1;
			break;
		}
	}

	chal = eap_ttls_implicit_challenge(
		sm, data, EAP_TTLS_MSCHAPV2_CHALLENGE_LEN + 1);
	if (chal == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAPV2: Failed to generate "
			   "challenge from TLS data");
		eap_ttls_state(data, FAILURE);
		return;
	}

	if (os_memcmp_const(challenge, chal, EAP_TTLS_MSCHAPV2_CHALLENGE_LEN)
	    != 0 ||
	    response[0] != chal[EAP_TTLS_MSCHAPV2_CHALLENGE_LEN]) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAPV2: Challenge mismatch");
		os_free(chal);
		eap_ttls_state(data, FAILURE);
		return;
	}
	os_free(chal);

	auth_challenge = challenge;
	peer_challenge = response + 2;

	wpa_hexdump_ascii(MSG_MSGDUMP, "EAP-TTLS/MSCHAPV2: User",
			  username, username_len);
	wpa_hexdump(MSG_MSGDUMP, "EAP-TTLS/MSCHAPV2: auth_challenge",
		    auth_challenge, EAP_TTLS_MSCHAPV2_CHALLENGE_LEN);
	wpa_hexdump(MSG_MSGDUMP, "EAP-TTLS/MSCHAPV2: peer_challenge",
		    peer_challenge, EAP_TTLS_MSCHAPV2_CHALLENGE_LEN);

	if (sm->user->password_hash) {
		generate_nt_response_pwhash(auth_challenge, peer_challenge,
					    username, username_len,
					    sm->user->password,
					    nt_response);
	} else {
		generate_nt_response(auth_challenge, peer_challenge,
				     username, username_len,
				     sm->user->password,
				     sm->user->password_len,
				     nt_response);
	}

	rx_resp = response + 2 + EAP_TTLS_MSCHAPV2_CHALLENGE_LEN + 8;
#ifdef CONFIG_TESTING_OPTIONS
	{
		u8 challenge2[8];

		if (challenge_hash(peer_challenge, auth_challenge,
				   username, username_len, challenge2) == 0) {
			eap_server_mschap_rx_callback(sm, "TTLS-MSCHAPV2",
						      username, username_len,
						      challenge2, rx_resp);
		}
	}
#endif /* CONFIG_TESTING_OPTIONS */
	if (os_memcmp_const(nt_response, rx_resp, 24) == 0) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAPV2: Correct "
			   "NT-Response");
		data->mschapv2_resp_ok = 1;

		if (sm->user->password_hash) {
			generate_authenticator_response_pwhash(
				sm->user->password,
				peer_challenge, auth_challenge,
				username, username_len, nt_response,
				data->mschapv2_auth_response);
		} else {
			generate_authenticator_response(
				sm->user->password, sm->user->password_len,
				peer_challenge, auth_challenge,
				username, username_len, nt_response,
				data->mschapv2_auth_response);
		}
	} else {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAPV2: Invalid "
			   "NT-Response");
		wpa_hexdump(MSG_MSGDUMP, "EAP-TTLS/MSCHAPV2: Received",
			    rx_resp, 24);
		wpa_hexdump(MSG_MSGDUMP, "EAP-TTLS/MSCHAPV2: Expected",
			    nt_response, 24);
		data->mschapv2_resp_ok = 0;
	}
	eap_ttls_state(data, PHASE2_MSCHAPV2_RESP);
	data->mschapv2_ident = response[0];
}