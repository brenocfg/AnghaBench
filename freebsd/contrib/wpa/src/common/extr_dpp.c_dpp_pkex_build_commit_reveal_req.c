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
typedef  struct wpabuf const wpabuf ;
struct dpp_pkex {int /*<<< orphan*/  z; TYPE_1__* own_bi; } ;
struct dpp_curve_params {int prime_len; int hash_len; } ;
typedef  int /*<<< orphan*/  octet ;
struct TYPE_2__ {struct dpp_curve_params* curve; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int DPP_ATTR_BOOTSTRAP_KEY ; 
 int DPP_ATTR_I_AUTH_TAG ; 
 int DPP_ATTR_WRAPPED_DATA ; 
 size_t DPP_HDR_LEN ; 
 int /*<<< orphan*/  DPP_PA_PKEX_COMMIT_REVEAL_REQ ; 
 int /*<<< orphan*/  DPP_STATUS_OK ; 
 scalar_t__ DPP_TEST_AFTER_WRAPPED_DATA_PKEX_CR_REQ ; 
 scalar_t__ DPP_TEST_INVALID_BOOTSTRAP_KEY_PKEX_CR_REQ ; 
 scalar_t__ DPP_TEST_I_AUTH_TAG_MISMATCH_PKEX_CR_REQ ; 
 scalar_t__ DPP_TEST_NO_BOOTSTRAP_KEY_PKEX_CR_REQ ; 
 scalar_t__ DPP_TEST_NO_I_AUTH_TAG_PKEX_CR_REQ ; 
 scalar_t__ DPP_TEST_NO_WRAPPED_DATA_PKEX_CR_REQ ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ aes_siv_encrypt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int const**,size_t*,int*) ; 
 struct wpabuf const* dpp_alloc_msg (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dpp_build_attr_status (struct wpabuf const*,int /*<<< orphan*/ ) ; 
 scalar_t__ dpp_test ; 
 scalar_t__ dpp_test_gen_invalid_key (struct wpabuf const*,struct dpp_curve_params const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf const* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int* wpabuf_head_u8 (struct wpabuf const*) ; 
 int wpabuf_len (struct wpabuf const*) ; 
 int* wpabuf_put (struct wpabuf const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf const*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf const*,int const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf const*,int const) ; 

__attribute__((used)) static struct wpabuf *
dpp_pkex_build_commit_reveal_req(struct dpp_pkex *pkex,
				 const struct wpabuf *A_pub, const u8 *u)
{
	const struct dpp_curve_params *curve = pkex->own_bi->curve;
	struct wpabuf *msg = NULL;
	size_t clear_len, attr_len;
	struct wpabuf *clear = NULL;
	u8 *wrapped;
	u8 octet;
	const u8 *addr[2];
	size_t len[2];

	/* {A, u, [bootstrapping info]}z */
	clear_len = 4 + 2 * curve->prime_len + 4 + curve->hash_len;
	clear = wpabuf_alloc(clear_len);
	attr_len = 4 + clear_len + AES_BLOCK_SIZE;
#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_AFTER_WRAPPED_DATA_PKEX_CR_REQ)
		attr_len += 5;
#endif /* CONFIG_TESTING_OPTIONS */
	msg = dpp_alloc_msg(DPP_PA_PKEX_COMMIT_REVEAL_REQ, attr_len);
	if (!clear || !msg)
		goto fail;

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_NO_BOOTSTRAP_KEY_PKEX_CR_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no Bootstrap Key");
		goto skip_bootstrap_key;
	}
	if (dpp_test == DPP_TEST_INVALID_BOOTSTRAP_KEY_PKEX_CR_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - invalid Bootstrap Key");
		wpabuf_put_le16(clear, DPP_ATTR_BOOTSTRAP_KEY);
		wpabuf_put_le16(clear, 2 * curve->prime_len);
		if (dpp_test_gen_invalid_key(clear, curve) < 0)
			goto fail;
		goto skip_bootstrap_key;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	/* A in Bootstrap Key attribute */
	wpabuf_put_le16(clear, DPP_ATTR_BOOTSTRAP_KEY);
	wpabuf_put_le16(clear, wpabuf_len(A_pub));
	wpabuf_put_buf(clear, A_pub);

#ifdef CONFIG_TESTING_OPTIONS
skip_bootstrap_key:
	if (dpp_test == DPP_TEST_NO_I_AUTH_TAG_PKEX_CR_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no I-Auth tag");
		goto skip_i_auth_tag;
	}
	if (dpp_test == DPP_TEST_I_AUTH_TAG_MISMATCH_PKEX_CR_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - I-Auth tag mismatch");
		wpabuf_put_le16(clear, DPP_ATTR_I_AUTH_TAG);
		wpabuf_put_le16(clear, curve->hash_len);
		wpabuf_put_data(clear, u, curve->hash_len - 1);
		wpabuf_put_u8(clear, u[curve->hash_len - 1] ^ 0x01);
		goto skip_i_auth_tag;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	/* u in I-Auth tag attribute */
	wpabuf_put_le16(clear, DPP_ATTR_I_AUTH_TAG);
	wpabuf_put_le16(clear, curve->hash_len);
	wpabuf_put_data(clear, u, curve->hash_len);

#ifdef CONFIG_TESTING_OPTIONS
skip_i_auth_tag:
	if (dpp_test == DPP_TEST_NO_WRAPPED_DATA_PKEX_CR_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no Wrapped Data");
		goto skip_wrapped_data;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	addr[0] = wpabuf_head_u8(msg) + 2;
	len[0] = DPP_HDR_LEN;
	octet = 0;
	addr[1] = &octet;
	len[1] = sizeof(octet);
	wpa_hexdump(MSG_DEBUG, "DDP: AES-SIV AD[0]", addr[0], len[0]);
	wpa_hexdump(MSG_DEBUG, "DDP: AES-SIV AD[1]", addr[1], len[1]);

	wpabuf_put_le16(msg, DPP_ATTR_WRAPPED_DATA);
	wpabuf_put_le16(msg, wpabuf_len(clear) + AES_BLOCK_SIZE);
	wrapped = wpabuf_put(msg, wpabuf_len(clear) + AES_BLOCK_SIZE);

	wpa_hexdump_buf(MSG_DEBUG, "DPP: AES-SIV cleartext", clear);
	if (aes_siv_encrypt(pkex->z, curve->hash_len,
			    wpabuf_head(clear), wpabuf_len(clear),
			    2, addr, len, wrapped) < 0)
		goto fail;
	wpa_hexdump(MSG_DEBUG, "DPP: AES-SIV ciphertext",
		    wrapped, wpabuf_len(clear) + AES_BLOCK_SIZE);

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_AFTER_WRAPPED_DATA_PKEX_CR_REQ) {
		wpa_printf(MSG_INFO, "DPP: TESTING - attr after Wrapped Data");
		dpp_build_attr_status(msg, DPP_STATUS_OK);
	}
skip_wrapped_data:
#endif /* CONFIG_TESTING_OPTIONS */

out:
	wpabuf_free(clear);
	return msg;

fail:
	wpabuf_free(msg);
	msg = NULL;
	goto out;
}