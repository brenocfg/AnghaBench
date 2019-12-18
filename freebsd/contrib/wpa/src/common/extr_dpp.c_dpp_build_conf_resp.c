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
typedef  int u16 ;
struct wpabuf {int dummy; } ;
struct dpp_authentication {int conf_resp_status; TYPE_1__* curve; int /*<<< orphan*/  ke; } ;
typedef  enum dpp_status_error { ____Placeholder_dpp_status_error } dpp_status_error ;
struct TYPE_2__ {int /*<<< orphan*/  hash_len; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int DPP_ATTR_CONFIG_OBJ ; 
 int DPP_ATTR_ENROLLEE_NONCE ; 
 int DPP_ATTR_WRAPPED_DATA ; 
 int DPP_STATUS_CONFIGURE_FAILURE ; 
 int DPP_STATUS_OK ; 
 scalar_t__ DPP_TEST_AFTER_WRAPPED_DATA_CONF_RESP ; 
 scalar_t__ DPP_TEST_E_NONCE_MISMATCH_CONF_RESP ; 
 scalar_t__ DPP_TEST_INVALID_STATUS_CONF_RESP ; 
 scalar_t__ DPP_TEST_NO_CONFIG_OBJ_CONF_RESP ; 
 scalar_t__ DPP_TEST_NO_E_NONCE_CONF_RESP ; 
 scalar_t__ DPP_TEST_NO_STATUS_CONF_RESP ; 
 scalar_t__ DPP_TEST_NO_WRAPPED_DATA_CONF_RESP ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ aes_siv_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int const**,size_t*,int*) ; 
 int /*<<< orphan*/  dpp_build_attr_status (struct wpabuf*,int) ; 
 struct wpabuf* dpp_build_conf_obj (struct dpp_authentication*,int) ; 
 scalar_t__ dpp_test ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int* wpabuf_head (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 
 int* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int const*,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int const) ; 

__attribute__((used)) static struct wpabuf *
dpp_build_conf_resp(struct dpp_authentication *auth, const u8 *e_nonce,
		    u16 e_nonce_len, int ap)
{
	struct wpabuf *conf;
	size_t clear_len, attr_len;
	struct wpabuf *clear = NULL, *msg = NULL;
	u8 *wrapped;
	const u8 *addr[1];
	size_t len[1];
	enum dpp_status_error status;

	conf = dpp_build_conf_obj(auth, ap);
	if (conf) {
		wpa_hexdump_ascii(MSG_DEBUG, "DPP: configurationObject JSON",
				  wpabuf_head(conf), wpabuf_len(conf));
	}
	status = conf ? DPP_STATUS_OK : DPP_STATUS_CONFIGURE_FAILURE;
	auth->conf_resp_status = status;

	/* { E-nonce, configurationObject}ke */
	clear_len = 4 + e_nonce_len;
	if (conf)
		clear_len += 4 + wpabuf_len(conf);
	clear = wpabuf_alloc(clear_len);
	attr_len = 4 + 1 + 4 + clear_len + AES_BLOCK_SIZE;
#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_AFTER_WRAPPED_DATA_CONF_RESP)
		attr_len += 5;
#endif /* CONFIG_TESTING_OPTIONS */
	msg = wpabuf_alloc(attr_len);
	if (!clear || !msg)
		goto fail;

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_NO_E_NONCE_CONF_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no E-nonce");
		goto skip_e_nonce;
	}
	if (dpp_test == DPP_TEST_E_NONCE_MISMATCH_CONF_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - E-nonce mismatch");
		wpabuf_put_le16(clear, DPP_ATTR_ENROLLEE_NONCE);
		wpabuf_put_le16(clear, e_nonce_len);
		wpabuf_put_data(clear, e_nonce, e_nonce_len - 1);
		wpabuf_put_u8(clear, e_nonce[e_nonce_len - 1] ^ 0x01);
		goto skip_e_nonce;
	}
	if (dpp_test == DPP_TEST_NO_WRAPPED_DATA_CONF_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - no Wrapped Data");
		goto skip_wrapped_data;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	/* E-nonce */
	wpabuf_put_le16(clear, DPP_ATTR_ENROLLEE_NONCE);
	wpabuf_put_le16(clear, e_nonce_len);
	wpabuf_put_data(clear, e_nonce, e_nonce_len);

#ifdef CONFIG_TESTING_OPTIONS
skip_e_nonce:
	if (dpp_test == DPP_TEST_NO_CONFIG_OBJ_CONF_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - Config Object");
		goto skip_config_obj;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	if (conf) {
		wpabuf_put_le16(clear, DPP_ATTR_CONFIG_OBJ);
		wpabuf_put_le16(clear, wpabuf_len(conf));
		wpabuf_put_buf(clear, conf);
	}

#ifdef CONFIG_TESTING_OPTIONS
skip_config_obj:
	if (dpp_test == DPP_TEST_NO_STATUS_CONF_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - Status");
		goto skip_status;
	}
	if (dpp_test == DPP_TEST_INVALID_STATUS_CONF_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - invalid Status");
		status = 255;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	/* DPP Status */
	dpp_build_attr_status(msg, status);

#ifdef CONFIG_TESTING_OPTIONS
skip_status:
#endif /* CONFIG_TESTING_OPTIONS */

	addr[0] = wpabuf_head(msg);
	len[0] = wpabuf_len(msg);
	wpa_hexdump(MSG_DEBUG, "DDP: AES-SIV AD", addr[0], len[0]);

	wpabuf_put_le16(msg, DPP_ATTR_WRAPPED_DATA);
	wpabuf_put_le16(msg, wpabuf_len(clear) + AES_BLOCK_SIZE);
	wrapped = wpabuf_put(msg, wpabuf_len(clear) + AES_BLOCK_SIZE);

	wpa_hexdump_buf(MSG_DEBUG, "DPP: AES-SIV cleartext", clear);
	if (aes_siv_encrypt(auth->ke, auth->curve->hash_len,
			    wpabuf_head(clear), wpabuf_len(clear),
			    1, addr, len, wrapped) < 0)
		goto fail;
	wpa_hexdump(MSG_DEBUG, "DPP: AES-SIV ciphertext",
		    wrapped, wpabuf_len(clear) + AES_BLOCK_SIZE);

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_AFTER_WRAPPED_DATA_CONF_RESP) {
		wpa_printf(MSG_INFO, "DPP: TESTING - attr after Wrapped Data");
		dpp_build_attr_status(msg, DPP_STATUS_OK);
	}
skip_wrapped_data:
#endif /* CONFIG_TESTING_OPTIONS */

	wpa_hexdump_buf(MSG_DEBUG,
			"DPP: Configuration Response attributes", msg);
out:
	wpabuf_free(conf);
	wpabuf_free(clear);

	return msg;
fail:
	wpabuf_free(msg);
	msg = NULL;
	goto out;
}