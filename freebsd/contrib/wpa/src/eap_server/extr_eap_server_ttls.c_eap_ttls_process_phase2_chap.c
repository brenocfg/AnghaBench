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
typedef  scalar_t__ const u8 ;
struct eap_ttls_data {int dummy; } ;
struct eap_sm {TYPE_1__* user; } ;
struct TYPE_2__ {int ttls_auth; int /*<<< orphan*/  password_len; int /*<<< orphan*/  password; scalar_t__ password_hash; } ;

/* Variables and functions */
 int CHAP_MD5_LEN ; 
 int EAP_TTLS_AUTH_CHAP ; 
 size_t EAP_TTLS_CHAP_CHALLENGE_LEN ; 
 int EAP_TTLS_CHAP_PASSWORD_LEN ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  chap_md5 (scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*,size_t,scalar_t__ const*) ; 
 scalar_t__* eap_ttls_implicit_challenge (struct eap_sm*,struct eap_ttls_data*,size_t) ; 
 int /*<<< orphan*/  eap_ttls_state (struct eap_ttls_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_ttls_valid_session (struct eap_sm*,struct eap_ttls_data*) ; 
 int /*<<< orphan*/  os_free (scalar_t__ const*) ; 
 scalar_t__ os_memcmp_const (scalar_t__ const*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_ttls_process_phase2_chap(struct eap_sm *sm,
					 struct eap_ttls_data *data,
					 const u8 *challenge,
					 size_t challenge_len,
					 const u8 *password,
					 size_t password_len)
{
	u8 *chal, hash[CHAP_MD5_LEN];

	if (challenge == NULL || password == NULL ||
	    challenge_len != EAP_TTLS_CHAP_CHALLENGE_LEN ||
	    password_len != 1 + EAP_TTLS_CHAP_PASSWORD_LEN) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/CHAP: Invalid CHAP attributes "
			   "(challenge len %lu password len %lu)",
			   (unsigned long) challenge_len,
			   (unsigned long) password_len);
		eap_ttls_state(data, FAILURE);
		return;
	}

	if (!sm->user || !sm->user->password || sm->user->password_hash ||
	    !(sm->user->ttls_auth & EAP_TTLS_AUTH_CHAP)) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/CHAP: No plaintext user "
			   "password configured");
		eap_ttls_state(data, FAILURE);
		return;
	}

	chal = eap_ttls_implicit_challenge(sm, data,
					   EAP_TTLS_CHAP_CHALLENGE_LEN + 1);
	if (chal == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/CHAP: Failed to generate "
			   "challenge from TLS data");
		eap_ttls_state(data, FAILURE);
		return;
	}

	if (os_memcmp_const(challenge, chal, EAP_TTLS_CHAP_CHALLENGE_LEN)
	    != 0 ||
	    password[0] != chal[EAP_TTLS_CHAP_CHALLENGE_LEN]) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/CHAP: Challenge mismatch");
		os_free(chal);
		eap_ttls_state(data, FAILURE);
		return;
	}
	os_free(chal);

	/* MD5(Ident + Password + Challenge) */
	chap_md5(password[0], sm->user->password, sm->user->password_len,
		 challenge, challenge_len, hash);

	if (os_memcmp_const(hash, password + 1, EAP_TTLS_CHAP_PASSWORD_LEN) ==
	    0) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/CHAP: Correct user password");
		eap_ttls_state(data, SUCCESS);
		eap_ttls_valid_session(sm, data);
	} else {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/CHAP: Invalid user password");
		eap_ttls_state(data, FAILURE);
	}
}