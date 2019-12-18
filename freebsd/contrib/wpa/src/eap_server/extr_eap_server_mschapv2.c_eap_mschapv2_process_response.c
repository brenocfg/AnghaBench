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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int* identity; size_t identity_len; TYPE_1__* user; } ;
struct eap_mschapv2_hdr {scalar_t__ op_code; int /*<<< orphan*/  mschapv2_id; } ;
struct eap_mschapv2_data {int* peer_challenge; int master_key_valid; void* state; int /*<<< orphan*/  master_key; int /*<<< orphan*/  auth_response; int /*<<< orphan*/  auth_challenge; int /*<<< orphan*/  resp_mschapv2_id; } ;
struct TYPE_2__ {int* password; int /*<<< orphan*/  password_len; scalar_t__ password_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_MSCHAPV2 ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FAILURE ; 
 void* FAILURE_REQ ; 
 int /*<<< orphan*/  MSCHAPV2_KEY_LEN ; 
 scalar_t__ MSCHAPV2_OP_RESPONSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 void* SUCCESS_REQ ; 
 scalar_t__ challenge_hash (int const*,int /*<<< orphan*/ ,int const*,size_t,int*) ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  eap_log_msg (struct eap_sm*,char*,char*) ; 
 int /*<<< orphan*/  eap_server_mschap_rx_callback (struct eap_sm*,char*,int const*,size_t,int*,int const*) ; 
 scalar_t__ generate_authenticator_response_pwhash (int const*,int const*,int /*<<< orphan*/ ,int const*,size_t,int const*,int /*<<< orphan*/ ) ; 
 int generate_nt_response (int /*<<< orphan*/ ,int const*,int const*,size_t,int*,int /*<<< orphan*/ ,int*) ; 
 int generate_nt_response_pwhash (int /*<<< orphan*/ ,int const*,int const*,size_t,int*,int*) ; 
 scalar_t__ get_master_key (int*,int const*,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_nt_password_hash (int const*,int*) ; 
 scalar_t__ nt_password_hash (int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (size_t) ; 
 scalar_t__ os_memcmp (int const*,int const*,size_t) ; 
 scalar_t__ os_memcmp_const (int const*,int*,int) ; 
 int /*<<< orphan*/  printf_encode (char*,size_t,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_mschapv2_process_response(struct eap_sm *sm,
					  struct eap_mschapv2_data *data,
					  struct wpabuf *respData)
{
	struct eap_mschapv2_hdr *resp;
	const u8 *pos, *end, *peer_challenge, *nt_response, *name;
	u8 flags;
	size_t len, name_len, i;
	u8 expected[24];
	const u8 *username, *user;
	size_t username_len, user_len;
	int res;
	char *buf;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_MSCHAPV2, respData,
			       &len);
	if (pos == NULL || len < 1)
		return; /* Should not happen - frame already validated */

	end = pos + len;
	resp = (struct eap_mschapv2_hdr *) pos;
	pos = (u8 *) (resp + 1);

	if (len < sizeof(*resp) + 1 + 49 ||
	    resp->op_code != MSCHAPV2_OP_RESPONSE ||
	    pos[0] != 49) {
		wpa_hexdump_buf(MSG_DEBUG, "EAP-MSCHAPV2: Invalid response",
				respData);
		data->state = FAILURE;
		return;
	}
	data->resp_mschapv2_id = resp->mschapv2_id;
	pos++;
	peer_challenge = pos;
	pos += 16 + 8;
	nt_response = pos;
	pos += 24;
	flags = *pos++;
	name = pos;
	name_len = end - name;

	if (data->peer_challenge) {
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Using pre-configured "
			   "Peer-Challenge");
		peer_challenge = data->peer_challenge;
	}
	wpa_hexdump(MSG_MSGDUMP, "EAP-MSCHAPV2: Peer-Challenge",
		    peer_challenge, 16);
	wpa_hexdump(MSG_MSGDUMP, "EAP-MSCHAPV2: NT-Response", nt_response, 24);
	wpa_printf(MSG_MSGDUMP, "EAP-MSCHAPV2: Flags 0x%x", flags);
	wpa_hexdump_ascii(MSG_MSGDUMP, "EAP-MSCHAPV2: Name", name, name_len);

	buf = os_malloc(name_len * 4 + 1);
	if (buf) {
		printf_encode(buf, name_len * 4 + 1, name, name_len);
		eap_log_msg(sm, "EAP-MSCHAPV2 Name '%s'", buf);
		os_free(buf);
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

	user = name;
	user_len = name_len;
	for (i = 0; i < user_len; i++) {
		if (user[i] == '\\') {
			user_len -= i + 1;
			user += i + 1;
			break;
		}
	}

#ifdef CONFIG_TESTING_OPTIONS
	{
		u8 challenge[8];

		if (challenge_hash(peer_challenge, data->auth_challenge,
				   username, username_len, challenge) == 0) {
			eap_server_mschap_rx_callback(sm, "EAP-MSCHAPV2",
						      username, username_len,
						      challenge, nt_response);
		}
	}
#endif /* CONFIG_TESTING_OPTIONS */

	if (username_len != user_len ||
	    os_memcmp(username, user, username_len) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Mismatch in user names");
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-MSCHAPV2: Expected user "
				  "name", username, username_len);
		wpa_hexdump_ascii(MSG_DEBUG, "EAP-MSCHAPV2: Received user "
				  "name", user, user_len);
		data->state = FAILURE;
		return;
	}

	wpa_hexdump_ascii(MSG_MSGDUMP, "EAP-MSCHAPV2: User name",
			  username, username_len);

	if (sm->user->password_hash) {
		res = generate_nt_response_pwhash(data->auth_challenge,
						  peer_challenge,
						  username, username_len,
						  sm->user->password,
						  expected);
	} else {
		res = generate_nt_response(data->auth_challenge,
					   peer_challenge,
					   username, username_len,
					   sm->user->password,
					   sm->user->password_len,
					   expected);
	}
	if (res) {
		data->state = FAILURE;
		return;
	}

	if (os_memcmp_const(nt_response, expected, 24) == 0) {
		const u8 *pw_hash;
		u8 pw_hash_buf[16], pw_hash_hash[16];

		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Correct NT-Response");
		data->state = SUCCESS_REQ;

		/* Authenticator response is not really needed yet, but
		 * calculate it here so that peer_challenge and username need
		 * not be saved. */
		if (sm->user->password_hash) {
			pw_hash = sm->user->password;
		} else {
			if (nt_password_hash(sm->user->password,
					     sm->user->password_len,
					     pw_hash_buf) < 0) {
				data->state = FAILURE;
				return;
			}
			pw_hash = pw_hash_buf;
		}
		if (generate_authenticator_response_pwhash(
			    pw_hash, peer_challenge, data->auth_challenge,
			    username, username_len, nt_response,
			    data->auth_response) < 0 ||
		    hash_nt_password_hash(pw_hash, pw_hash_hash) < 0 ||
		    get_master_key(pw_hash_hash, nt_response,
				   data->master_key)) {
			data->state = FAILURE;
			return;
		}
		data->master_key_valid = 1;
		wpa_hexdump_key(MSG_DEBUG, "EAP-MSCHAPV2: Derived Master Key",
				data->master_key, MSCHAPV2_KEY_LEN);
	} else {
		wpa_hexdump(MSG_MSGDUMP, "EAP-MSCHAPV2: Expected NT-Response",
			    expected, 24);
		wpa_printf(MSG_DEBUG, "EAP-MSCHAPV2: Invalid NT-Response");
		data->state = FAILURE_REQ;
	}
}