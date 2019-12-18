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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct json_token {scalar_t__ type; int /*<<< orphan*/  string; } ;
struct dpp_authentication {int /*<<< orphan*/  akm; scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 scalar_t__ JSON_OBJECT ; 
 scalar_t__ JSON_STRING ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ SSID_MAX_LEN ; 
 scalar_t__ dpp_akm_dpp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp_akm_from_str (int /*<<< orphan*/ ) ; 
 scalar_t__ dpp_akm_legacy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp_auth_fail (struct dpp_authentication*,char*) ; 
 scalar_t__ dpp_parse_cred_dpp (struct dpp_authentication*,struct json_token*) ; 
 scalar_t__ dpp_parse_cred_legacy (struct dpp_authentication*,struct json_token*) ; 
 int /*<<< orphan*/  json_free (struct json_token*) ; 
 struct json_token* json_get_member (struct json_token*,char*) ; 
 struct json_token* json_parse (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ os_strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int dpp_parse_conf_obj(struct dpp_authentication *auth,
			      const u8 *conf_obj, u16 conf_obj_len)
{
	int ret = -1;
	struct json_token *root, *token, *discovery, *cred;

	root = json_parse((const char *) conf_obj, conf_obj_len);
	if (!root)
		return -1;
	if (root->type != JSON_OBJECT) {
		dpp_auth_fail(auth, "JSON root is not an object");
		goto fail;
	}

	token = json_get_member(root, "wi-fi_tech");
	if (!token || token->type != JSON_STRING) {
		dpp_auth_fail(auth, "No wi-fi_tech string value found");
		goto fail;
	}
	if (os_strcmp(token->string, "infra") != 0) {
		wpa_printf(MSG_DEBUG, "DPP: Unsupported wi-fi_tech value: '%s'",
			   token->string);
		dpp_auth_fail(auth, "Unsupported wi-fi_tech value");
		goto fail;
	}

	discovery = json_get_member(root, "discovery");
	if (!discovery || discovery->type != JSON_OBJECT) {
		dpp_auth_fail(auth, "No discovery object in JSON");
		goto fail;
	}

	token = json_get_member(discovery, "ssid");
	if (!token || token->type != JSON_STRING) {
		dpp_auth_fail(auth, "No discovery::ssid string value found");
		goto fail;
	}
	wpa_hexdump_ascii(MSG_DEBUG, "DPP: discovery::ssid",
			  token->string, os_strlen(token->string));
	if (os_strlen(token->string) > SSID_MAX_LEN) {
		dpp_auth_fail(auth, "Too long discovery::ssid string value");
		goto fail;
	}
	auth->ssid_len = os_strlen(token->string);
	os_memcpy(auth->ssid, token->string, auth->ssid_len);

	cred = json_get_member(root, "cred");
	if (!cred || cred->type != JSON_OBJECT) {
		dpp_auth_fail(auth, "No cred object in JSON");
		goto fail;
	}

	token = json_get_member(cred, "akm");
	if (!token || token->type != JSON_STRING) {
		dpp_auth_fail(auth, "No cred::akm string value found");
		goto fail;
	}
	auth->akm = dpp_akm_from_str(token->string);

	if (dpp_akm_legacy(auth->akm)) {
		if (dpp_parse_cred_legacy(auth, cred) < 0)
			goto fail;
	} else if (dpp_akm_dpp(auth->akm)) {
		if (dpp_parse_cred_dpp(auth, cred) < 0)
			goto fail;
	} else {
		wpa_printf(MSG_DEBUG, "DPP: Unsupported akm: %s",
			   token->string);
		dpp_auth_fail(auth, "Unsupported akm");
		goto fail;
	}

	wpa_printf(MSG_DEBUG, "DPP: JSON parsing completed successfully");
	ret = 0;
fail:
	json_free(root);
	return ret;
}