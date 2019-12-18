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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct wpabuf {int dummy; } ;
struct dpp_authentication {int conf_resp_status; int /*<<< orphan*/  e_nonce; TYPE_1__* curve; int /*<<< orphan*/  ke; } ;
struct TYPE_2__ {scalar_t__ nonce_len; int /*<<< orphan*/  hash_len; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DPP_ATTR_CONFIG_OBJ ; 
 int /*<<< orphan*/  DPP_ATTR_ENROLLEE_NONCE ; 
 int /*<<< orphan*/  DPP_ATTR_STATUS ; 
 int /*<<< orphan*/  DPP_ATTR_WRAPPED_DATA ; 
 scalar_t__ const DPP_STATUS_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ aes_siv_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__ const*,scalar_t__,int,scalar_t__ const**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  dpp_auth_fail (struct dpp_authentication*,char*) ; 
 scalar_t__ dpp_check_attrs (scalar_t__*,size_t) ; 
 scalar_t__* dpp_get_attr (scalar_t__*,size_t,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ dpp_parse_conf_obj (struct dpp_authentication*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  os_free (scalar_t__*) ; 
 scalar_t__* os_malloc (size_t) ; 
 scalar_t__ os_memcmp (scalar_t__ const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__ const) ; 
 scalar_t__* wpabuf_head (struct wpabuf const*) ; 
 size_t wpabuf_len (struct wpabuf const*) ; 

int dpp_conf_resp_rx(struct dpp_authentication *auth,
		     const struct wpabuf *resp)
{
	const u8 *wrapped_data, *e_nonce, *status, *conf_obj;
	u16 wrapped_data_len, e_nonce_len, status_len, conf_obj_len;
	const u8 *addr[1];
	size_t len[1];
	u8 *unwrapped = NULL;
	size_t unwrapped_len = 0;
	int ret = -1;

	auth->conf_resp_status = 255;

	if (dpp_check_attrs(wpabuf_head(resp), wpabuf_len(resp)) < 0) {
		dpp_auth_fail(auth, "Invalid attribute in config response");
		return -1;
	}

	wrapped_data = dpp_get_attr(wpabuf_head(resp), wpabuf_len(resp),
				    DPP_ATTR_WRAPPED_DATA,
				    &wrapped_data_len);
	if (!wrapped_data || wrapped_data_len < AES_BLOCK_SIZE) {
		dpp_auth_fail(auth,
			      "Missing or invalid required Wrapped Data attribute");
		return -1;
	}

	wpa_hexdump(MSG_DEBUG, "DPP: AES-SIV ciphertext",
		    wrapped_data, wrapped_data_len);
	unwrapped_len = wrapped_data_len - AES_BLOCK_SIZE;
	unwrapped = os_malloc(unwrapped_len);
	if (!unwrapped)
		return -1;

	addr[0] = wpabuf_head(resp);
	len[0] = wrapped_data - 4 - (const u8 *) wpabuf_head(resp);
	wpa_hexdump(MSG_DEBUG, "DDP: AES-SIV AD", addr[0], len[0]);

	if (aes_siv_decrypt(auth->ke, auth->curve->hash_len,
			    wrapped_data, wrapped_data_len,
			    1, addr, len, unwrapped) < 0) {
		dpp_auth_fail(auth, "AES-SIV decryption failed");
		goto fail;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: AES-SIV cleartext",
		    unwrapped, unwrapped_len);

	if (dpp_check_attrs(unwrapped, unwrapped_len) < 0) {
		dpp_auth_fail(auth, "Invalid attribute in unwrapped data");
		goto fail;
	}

	e_nonce = dpp_get_attr(unwrapped, unwrapped_len,
			       DPP_ATTR_ENROLLEE_NONCE,
			       &e_nonce_len);
	if (!e_nonce || e_nonce_len != auth->curve->nonce_len) {
		dpp_auth_fail(auth,
			      "Missing or invalid Enrollee Nonce attribute");
		goto fail;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: Enrollee Nonce", e_nonce, e_nonce_len);
	if (os_memcmp(e_nonce, auth->e_nonce, e_nonce_len) != 0) {
		dpp_auth_fail(auth, "Enrollee Nonce mismatch");
		goto fail;
	}

	status = dpp_get_attr(wpabuf_head(resp), wpabuf_len(resp),
			      DPP_ATTR_STATUS, &status_len);
	if (!status || status_len < 1) {
		dpp_auth_fail(auth,
			      "Missing or invalid required DPP Status attribute");
		goto fail;
	}
	auth->conf_resp_status = status[0];
	wpa_printf(MSG_DEBUG, "DPP: Status %u", status[0]);
	if (status[0] != DPP_STATUS_OK) {
		dpp_auth_fail(auth, "Configurator rejected configuration");
		goto fail;
	}

	conf_obj = dpp_get_attr(unwrapped, unwrapped_len,
				DPP_ATTR_CONFIG_OBJ, &conf_obj_len);
	if (!conf_obj) {
		dpp_auth_fail(auth,
			      "Missing required Configuration Object attribute");
		goto fail;
	}
	wpa_hexdump_ascii(MSG_DEBUG, "DPP: configurationObject JSON",
			  conf_obj, conf_obj_len);
	if (dpp_parse_conf_obj(auth, conf_obj, conf_obj_len) < 0)
		goto fail;

	ret = 0;

fail:
	os_free(unwrapped);
	return ret;
}