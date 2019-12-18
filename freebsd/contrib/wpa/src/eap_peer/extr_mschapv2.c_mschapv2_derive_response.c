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
typedef  int /*<<< orphan*/  const u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MSCHAPV2_AUTH_RESPONSE_LEN ; 
 int /*<<< orphan*/  MSCHAPV2_CHAL_LEN ; 
 size_t MSCHAPV2_MASTER_KEY_LEN ; 
 int /*<<< orphan*/  MSCHAPV2_NT_RESPONSE_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ generate_authenticator_response (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ generate_authenticator_response_pwhash (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ generate_nt_response (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ; 
 scalar_t__ generate_nt_response_pwhash (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ get_master_key (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ hash_nt_password_hash (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* mschapv2_remove_domain (int /*<<< orphan*/  const*,size_t*) ; 
 scalar_t__ nt_password_hash (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 

int mschapv2_derive_response(const u8 *identity, size_t identity_len,
			     const u8 *password, size_t password_len,
			     int pwhash,
			     const u8 *auth_challenge,
			     const u8 *peer_challenge,
			     u8 *nt_response, u8 *auth_response,
			     u8 *master_key)
{
	const u8 *username;
	size_t username_len;
	u8 password_hash[16], password_hash_hash[16];

	wpa_hexdump_ascii(MSG_DEBUG, "MSCHAPV2: Identity",
			  identity, identity_len);
	username_len = identity_len;
	username = mschapv2_remove_domain(identity, &username_len);
	wpa_hexdump_ascii(MSG_DEBUG, "MSCHAPV2: Username",
			  username, username_len);

	wpa_hexdump(MSG_DEBUG, "MSCHAPV2: auth_challenge",
		    auth_challenge, MSCHAPV2_CHAL_LEN);
	wpa_hexdump(MSG_DEBUG, "MSCHAPV2: peer_challenge",
		    peer_challenge, MSCHAPV2_CHAL_LEN);
	wpa_hexdump_ascii(MSG_DEBUG, "MSCHAPV2: username",
			  username, username_len);
	/* Authenticator response is not really needed yet, but calculate it
	 * here so that challenges need not be saved. */
	if (pwhash) {
		wpa_hexdump_key(MSG_DEBUG, "MSCHAPV2: password hash",
				password, password_len);
		if (generate_nt_response_pwhash(auth_challenge, peer_challenge,
						username, username_len,
						password, nt_response) ||
		    generate_authenticator_response_pwhash(
			    password, peer_challenge, auth_challenge,
			    username, username_len, nt_response,
			    auth_response))
			return -1;
	} else {
		wpa_hexdump_ascii_key(MSG_DEBUG, "MSCHAPV2: password",
				      password, password_len);
		if (generate_nt_response(auth_challenge, peer_challenge,
					 username, username_len,
					 password, password_len,
					 nt_response) ||
		    generate_authenticator_response(password, password_len,
						    peer_challenge,
						    auth_challenge,
						    username, username_len,
						    nt_response,
						    auth_response))
			return -1;
	}
	wpa_hexdump(MSG_DEBUG, "MSCHAPV2: NT Response",
		    nt_response, MSCHAPV2_NT_RESPONSE_LEN);
	wpa_hexdump(MSG_DEBUG, "MSCHAPV2: Auth Response",
		    auth_response, MSCHAPV2_AUTH_RESPONSE_LEN);

	/* Generate master_key here since we have the needed data available. */
	if (pwhash) {
		if (hash_nt_password_hash(password, password_hash_hash))
			return -1;
	} else {
		if (nt_password_hash(password, password_len, password_hash) ||
		    hash_nt_password_hash(password_hash, password_hash_hash))
			return -1;
	}
	if (get_master_key(password_hash_hash, nt_response, master_key))
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "MSCHAPV2: Master Key",
			master_key, MSCHAPV2_MASTER_KEY_LEN);

	return 0;
}