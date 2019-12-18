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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct dpp_authentication {TYPE_3__* curve; int /*<<< orphan*/  ke; TYPE_2__* peer_bi; TYPE_1__* own_bi; scalar_t__ waiting_auth_conf; scalar_t__ initiator; } ;
struct TYPE_6__ {scalar_t__ hash_len; } ;
struct TYPE_5__ {scalar_t__* pubkey_hash; } ;
struct TYPE_4__ {scalar_t__* pubkey_hash; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DPP_ATTR_I_AUTH_TAG ; 
 int /*<<< orphan*/  DPP_ATTR_I_BOOTSTRAP_KEY_HASH ; 
 int /*<<< orphan*/  DPP_ATTR_R_BOOTSTRAP_KEY_HASH ; 
 int /*<<< orphan*/  DPP_ATTR_STATUS ; 
 int /*<<< orphan*/  DPP_ATTR_WRAPPED_DATA ; 
 size_t DPP_HDR_LEN ; 
 int DPP_MAX_HASH_LEN ; 
 scalar_t__ const DPP_STATUS_AUTH_FAILURE ; 
 scalar_t__ const DPP_STATUS_NOT_COMPATIBLE ; 
 scalar_t__ const DPP_STATUS_OK ; 
 scalar_t__ DPP_TEST_STOP_AT_AUTH_CONF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ SHA256_MAC_LEN ; 
 scalar_t__ aes_siv_decrypt (int /*<<< orphan*/ ,scalar_t__,scalar_t__ const*,scalar_t__,int,scalar_t__ const**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  bin_clear_free (scalar_t__*,size_t) ; 
 int dpp_auth_conf_rx_failure (struct dpp_authentication*,scalar_t__ const*,scalar_t__ const*,size_t,scalar_t__ const*,scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  dpp_auth_fail (struct dpp_authentication*,char*) ; 
 int /*<<< orphan*/  dpp_auth_success (struct dpp_authentication*) ; 
 scalar_t__ dpp_check_attrs (scalar_t__*,size_t) ; 
 scalar_t__ dpp_gen_i_auth (struct dpp_authentication*,scalar_t__*) ; 
 scalar_t__* dpp_get_attr (scalar_t__ const*,size_t,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ dpp_test ; 
 scalar_t__* os_malloc (size_t) ; 
 scalar_t__ os_memcmp (scalar_t__ const*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int dpp_auth_conf_rx(struct dpp_authentication *auth, const u8 *hdr,
		     const u8 *attr_start, size_t attr_len)
{
	const u8 *r_bootstrap, *i_bootstrap, *wrapped_data, *status, *i_auth;
	u16 r_bootstrap_len, i_bootstrap_len, wrapped_data_len, status_len,
		i_auth_len;
	const u8 *addr[2];
	size_t len[2];
	u8 *unwrapped = NULL;
	size_t unwrapped_len = 0;
	u8 i_auth2[DPP_MAX_HASH_LEN];

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_STOP_AT_AUTH_CONF) {
		wpa_printf(MSG_INFO,
			   "DPP: TESTING - stop at Authentication Confirm");
		return -1;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	if (auth->initiator || !auth->own_bi) {
		dpp_auth_fail(auth, "Unexpected Authentication Confirm");
		return -1;
	}

	auth->waiting_auth_conf = 0;

	wrapped_data = dpp_get_attr(attr_start, attr_len, DPP_ATTR_WRAPPED_DATA,
				    &wrapped_data_len);
	if (!wrapped_data || wrapped_data_len < AES_BLOCK_SIZE) {
		dpp_auth_fail(auth,
			      "Missing or invalid required Wrapped Data attribute");
		return -1;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: Wrapped data",
		    wrapped_data, wrapped_data_len);

	attr_len = wrapped_data - 4 - attr_start;

	r_bootstrap = dpp_get_attr(attr_start, attr_len,
				   DPP_ATTR_R_BOOTSTRAP_KEY_HASH,
				   &r_bootstrap_len);
	if (!r_bootstrap || r_bootstrap_len != SHA256_MAC_LEN) {
		dpp_auth_fail(auth,
			      "Missing or invalid required Responder Bootstrapping Key Hash attribute");
		return -1;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: Responder Bootstrapping Key Hash",
		    r_bootstrap, r_bootstrap_len);
	if (os_memcmp(r_bootstrap, auth->own_bi->pubkey_hash,
		      SHA256_MAC_LEN) != 0) {
		wpa_hexdump(MSG_DEBUG,
			    "DPP: Expected Responder Bootstrapping Key Hash",
			    auth->peer_bi->pubkey_hash, SHA256_MAC_LEN);
		dpp_auth_fail(auth,
			      "Responder Bootstrapping Key Hash mismatch");
		return -1;
	}

	i_bootstrap = dpp_get_attr(attr_start, attr_len,
				   DPP_ATTR_I_BOOTSTRAP_KEY_HASH,
				   &i_bootstrap_len);
	if (i_bootstrap) {
		if (i_bootstrap_len != SHA256_MAC_LEN) {
			dpp_auth_fail(auth,
				      "Invalid Initiator Bootstrapping Key Hash attribute");
			return -1;
		}
		wpa_hexdump(MSG_MSGDUMP,
			    "DPP: Initiator Bootstrapping Key Hash",
			    i_bootstrap, i_bootstrap_len);
		if (!auth->peer_bi ||
		    os_memcmp(i_bootstrap, auth->peer_bi->pubkey_hash,
			      SHA256_MAC_LEN) != 0) {
			dpp_auth_fail(auth,
				      "Initiator Bootstrapping Key Hash mismatch");
			return -1;
		}
	} else if (auth->peer_bi) {
		/* Mutual authentication and peer did not include its
		 * Bootstrapping Key Hash attribute. */
		dpp_auth_fail(auth,
			      "Missing Initiator Bootstrapping Key Hash attribute");
		return -1;
	}

	status = dpp_get_attr(attr_start, attr_len, DPP_ATTR_STATUS,
			      &status_len);
	if (!status || status_len < 1) {
		dpp_auth_fail(auth,
			      "Missing or invalid required DPP Status attribute");
		return -1;
	}
	wpa_printf(MSG_DEBUG, "DPP: Status %u", status[0]);
	if (status[0] == DPP_STATUS_NOT_COMPATIBLE ||
	    status[0] == DPP_STATUS_AUTH_FAILURE)
		return dpp_auth_conf_rx_failure(auth, hdr, attr_start,
						attr_len, wrapped_data,
						wrapped_data_len, status[0]);

	if (status[0] != DPP_STATUS_OK) {
		dpp_auth_fail(auth, "Authentication failed");
		return -1;
	}

	addr[0] = hdr;
	len[0] = DPP_HDR_LEN;
	addr[1] = attr_start;
	len[1] = attr_len;
	wpa_hexdump(MSG_DEBUG, "DDP: AES-SIV AD[0]", addr[0], len[0]);
	wpa_hexdump(MSG_DEBUG, "DDP: AES-SIV AD[1]", addr[1], len[1]);
	wpa_hexdump(MSG_DEBUG, "DPP: AES-SIV ciphertext",
		    wrapped_data, wrapped_data_len);
	unwrapped_len = wrapped_data_len - AES_BLOCK_SIZE;
	unwrapped = os_malloc(unwrapped_len);
	if (!unwrapped)
		return -1;
	if (aes_siv_decrypt(auth->ke, auth->curve->hash_len,
			    wrapped_data, wrapped_data_len,
			    2, addr, len, unwrapped) < 0) {
		dpp_auth_fail(auth, "AES-SIV decryption failed");
		goto fail;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: AES-SIV cleartext",
		    unwrapped, unwrapped_len);

	if (dpp_check_attrs(unwrapped, unwrapped_len) < 0) {
		dpp_auth_fail(auth, "Invalid attribute in unwrapped data");
		goto fail;
	}

	i_auth = dpp_get_attr(unwrapped, unwrapped_len, DPP_ATTR_I_AUTH_TAG,
			      &i_auth_len);
	if (!i_auth || i_auth_len != auth->curve->hash_len) {
		dpp_auth_fail(auth,
			      "Missing or invalid Initiator Authenticating Tag");
		goto fail;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: Received Initiator Authenticating Tag",
		    i_auth, i_auth_len);
	/* I-auth' = H(R-nonce | I-nonce | PR.x | PI.x | BR.x | [BI.x |] 1) */
	if (dpp_gen_i_auth(auth, i_auth2) < 0)
		goto fail;
	wpa_hexdump(MSG_DEBUG, "DPP: Calculated Initiator Authenticating Tag",
		    i_auth2, i_auth_len);
	if (os_memcmp(i_auth, i_auth2, i_auth_len) != 0) {
		dpp_auth_fail(auth, "Mismatching Initiator Authenticating Tag");
		goto fail;
	}

	bin_clear_free(unwrapped, unwrapped_len);
	dpp_auth_success(auth);
	return 0;
fail:
	bin_clear_free(unwrapped, unwrapped_len);
	return -1;
}