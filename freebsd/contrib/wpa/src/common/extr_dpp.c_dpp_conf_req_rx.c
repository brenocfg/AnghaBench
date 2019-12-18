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
typedef  int /*<<< orphan*/  const u8 ;
typedef  scalar_t__ u16 ;
struct wpabuf {int dummy; } ;
struct json_token {scalar_t__ type; int /*<<< orphan*/  string; } ;
struct dpp_authentication {int /*<<< orphan*/  e_nonce; TYPE_1__* curve; int /*<<< orphan*/  ke; } ;
struct TYPE_2__ {scalar_t__ nonce_len; int /*<<< orphan*/  hash_len; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DPP_ATTR_CONFIG_ATTR_OBJ ; 
 int /*<<< orphan*/  DPP_ATTR_ENROLLEE_NONCE ; 
 int /*<<< orphan*/  DPP_ATTR_WRAPPED_DATA ; 
 scalar_t__ DPP_TEST_STOP_AT_CONF_REQ ; 
 scalar_t__ JSON_STRING ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ aes_siv_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dpp_auth_fail (struct dpp_authentication*,char*) ; 
 struct wpabuf* dpp_build_conf_resp (struct dpp_authentication*,int /*<<< orphan*/  const*,scalar_t__,int) ; 
 scalar_t__ dpp_check_attrs (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  const* dpp_get_attr (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ dpp_test ; 
 int /*<<< orphan*/  json_free (struct json_token*) ; 
 struct json_token* json_get_member (struct json_token*,char*) ; 
 struct json_token* json_parse (char const*,scalar_t__) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

struct wpabuf *
dpp_conf_req_rx(struct dpp_authentication *auth, const u8 *attr_start,
		size_t attr_len)
{
	const u8 *wrapped_data, *e_nonce, *config_attr;
	u16 wrapped_data_len, e_nonce_len, config_attr_len;
	u8 *unwrapped = NULL;
	size_t unwrapped_len = 0;
	struct wpabuf *resp = NULL;
	struct json_token *root = NULL, *token;
	int ap;

#ifdef CONFIG_TESTING_OPTIONS
	if (dpp_test == DPP_TEST_STOP_AT_CONF_REQ) {
		wpa_printf(MSG_INFO,
			   "DPP: TESTING - stop at Config Request");
		return NULL;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	if (dpp_check_attrs(attr_start, attr_len) < 0) {
		dpp_auth_fail(auth, "Invalid attribute in config request");
		return NULL;
	}

	wrapped_data = dpp_get_attr(attr_start, attr_len, DPP_ATTR_WRAPPED_DATA,
				    &wrapped_data_len);
	if (!wrapped_data || wrapped_data_len < AES_BLOCK_SIZE) {
		dpp_auth_fail(auth,
			      "Missing or invalid required Wrapped Data attribute");
		return NULL;
	}

	wpa_hexdump(MSG_DEBUG, "DPP: AES-SIV ciphertext",
		    wrapped_data, wrapped_data_len);
	unwrapped_len = wrapped_data_len - AES_BLOCK_SIZE;
	unwrapped = os_malloc(unwrapped_len);
	if (!unwrapped)
		return NULL;
	if (aes_siv_decrypt(auth->ke, auth->curve->hash_len,
			    wrapped_data, wrapped_data_len,
			    0, NULL, NULL, unwrapped) < 0) {
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
	os_memcpy(auth->e_nonce, e_nonce, e_nonce_len);

	config_attr = dpp_get_attr(unwrapped, unwrapped_len,
				   DPP_ATTR_CONFIG_ATTR_OBJ,
				   &config_attr_len);
	if (!config_attr) {
		dpp_auth_fail(auth,
			      "Missing or invalid Config Attributes attribute");
		goto fail;
	}
	wpa_hexdump_ascii(MSG_DEBUG, "DPP: Config Attributes",
			  config_attr, config_attr_len);

	root = json_parse((const char *) config_attr, config_attr_len);
	if (!root) {
		dpp_auth_fail(auth, "Could not parse Config Attributes");
		goto fail;
	}

	token = json_get_member(root, "name");
	if (!token || token->type != JSON_STRING) {
		dpp_auth_fail(auth, "No Config Attributes - name");
		goto fail;
	}
	wpa_printf(MSG_DEBUG, "DPP: Enrollee name = '%s'", token->string);

	token = json_get_member(root, "wi-fi_tech");
	if (!token || token->type != JSON_STRING) {
		dpp_auth_fail(auth, "No Config Attributes - wi-fi_tech");
		goto fail;
	}
	wpa_printf(MSG_DEBUG, "DPP: wi-fi_tech = '%s'", token->string);
	if (os_strcmp(token->string, "infra") != 0) {
		wpa_printf(MSG_DEBUG, "DPP: Unsupported wi-fi_tech '%s'",
			   token->string);
		dpp_auth_fail(auth, "Unsupported wi-fi_tech");
		goto fail;
	}

	token = json_get_member(root, "netRole");
	if (!token || token->type != JSON_STRING) {
		dpp_auth_fail(auth, "No Config Attributes - netRole");
		goto fail;
	}
	wpa_printf(MSG_DEBUG, "DPP: netRole = '%s'", token->string);
	if (os_strcmp(token->string, "sta") == 0) {
		ap = 0;
	} else if (os_strcmp(token->string, "ap") == 0) {
		ap = 1;
	} else {
		wpa_printf(MSG_DEBUG, "DPP: Unsupported netRole '%s'",
			   token->string);
		dpp_auth_fail(auth, "Unsupported netRole");
		goto fail;
	}

	resp = dpp_build_conf_resp(auth, e_nonce, e_nonce_len, ap);

fail:
	json_free(root);
	os_free(unwrapped);
	return resp;
}