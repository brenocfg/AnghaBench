#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct dpp_authentication {int* i_nonce; struct wpabuf* resp_msg; int /*<<< orphan*/  k1; TYPE_3__* curve; TYPE_2__* peer_bi; TYPE_1__* own_bi; } ;
typedef  enum dpp_status_error { ____Placeholder_dpp_status_error } dpp_status_error ;
struct TYPE_6__ {int /*<<< orphan*/  nonce_len; } ;
struct TYPE_5__ {int* pubkey_hash; } ;
struct TYPE_4__ {int* pubkey_hash; } ;

/* Variables and functions */
 scalar_t__ DPP_TEST_INVALID_I_BOOTSTRAP_KEY_HASH_AUTH_RESP ; 
 scalar_t__ DPP_TEST_INVALID_R_BOOTSTRAP_KEY_HASH_AUTH_RESP ; 
 scalar_t__ DPP_TEST_NO_I_BOOTSTRAP_KEY_HASH_AUTH_RESP ; 
 scalar_t__ DPP_TEST_NO_I_NONCE_AUTH_RESP ; 
 scalar_t__ DPP_TEST_NO_R_BOOTSTRAP_KEY_HASH_AUTH_RESP ; 
 scalar_t__ DPP_TEST_NO_STATUS_AUTH_RESP ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int SHA256_MAC_LEN ; 
 struct wpabuf* dpp_auth_build_resp (struct dpp_authentication*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const*,int const*,int /*<<< orphan*/ *,int const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dpp_test ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static int dpp_auth_build_resp_status(struct dpp_authentication *auth,
				      enum dpp_status_error status)
{
	struct wpabuf *msg;
	const u8 *r_pubkey_hash, *i_pubkey_hash, *i_nonce;
#ifdef CONFIG_TESTING_OPTIONS
	u8 test_hash[SHA256_MAC_LEN];
#endif /* CONFIG_TESTING_OPTIONS */

	if (!auth->own_bi)
		return -1;
	wpa_printf(MSG_DEBUG, "DPP: Build Authentication Response");

	r_pubkey_hash = auth->own_bi->pubkey_hash;
	if (auth->peer_bi)
		i_pubkey_hash = auth->peer_bi->pubkey_hash;
	else
		i_pubkey_hash = NULL;

	i_nonce = auth->i_nonce;

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_NO_R_BOOTSTRAP_KEY_HASH_AUTH_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no R-Bootstrap Key Hash");
		r_pubkey_hash = NULL;
	} else if (dpp_test ==
		   DPP_TEST_INVALID_R_BOOTSTRAP_KEY_HASH_AUTH_RESP) {
		wpa_printf(MSG_INFO,
			   "DPP: TESTING - invalid R-Bootstrap Key Hash");
		os_memcpy(test_hash, r_pubkey_hash, SHA256_MAC_LEN);
		test_hash[SHA256_MAC_LEN - 1] ^= 0x01;
		r_pubkey_hash = test_hash;
	} else if (dpp_test == DPP_TEST_NO_I_BOOTSTRAP_KEY_HASH_AUTH_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no I-Bootstrap Key Hash");
		i_pubkey_hash = NULL;
	} else if (dpp_test ==
		   DPP_TEST_INVALID_I_BOOTSTRAP_KEY_HASH_AUTH_RESP) {
		wpa_printf(MSG_INFO,
			   "DPP: TESTING - invalid I-Bootstrap Key Hash");
		if (i_pubkey_hash)
			os_memcpy(test_hash, i_pubkey_hash, SHA256_MAC_LEN);
		else
			os_memset(test_hash, 0, SHA256_MAC_LEN);
		test_hash[SHA256_MAC_LEN - 1] ^= 0x01;
		i_pubkey_hash = test_hash;
	} else if (dpp_test == DPP_TEST_NO_STATUS_AUTH_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no Status");
		status = 255;
	} else if (dpp_test == DPP_TEST_NO_I_NONCE_AUTH_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no I-nonce");
		i_nonce = NULL;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	msg = dpp_auth_build_resp(auth, status, NULL, auth->curve->nonce_len,
				  r_pubkey_hash, i_pubkey_hash,
				  NULL, i_nonce, NULL, 0, auth->k1);
	if (!msg)
		return -1;
	wpabuf_free(auth->resp_msg);
	auth->resp_msg = msg;
	return 0;
}