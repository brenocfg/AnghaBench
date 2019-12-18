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
typedef  int /*<<< orphan*/  u16 ;
struct json_token {scalar_t__ type; int /*<<< orphan*/  string; struct json_token* sibling; struct json_token* child; } ;
struct dpp_curve_params {int dummy; } ;
struct dpp_authentication {scalar_t__ ignore_netaccesskey_mismatch; int /*<<< orphan*/  own_protocol_key; int /*<<< orphan*/  net_access_key_expiry; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int EVP_PKEY_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ JSON_ARRAY ; 
 scalar_t__ JSON_OBJECT ; 
 scalar_t__ JSON_STRING ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dpp_debug_print_key (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ dpp_key_expired (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dpp_parse_jwk (struct json_token*,struct dpp_curve_params const**) ; 
 int /*<<< orphan*/  json_free (struct json_token*) ; 
 struct json_token* json_get_member (struct json_token*,char*) ; 
 struct json_token* json_parse (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int dpp_parse_connector(struct dpp_authentication *auth,
			       const unsigned char *payload,
			       u16 payload_len)
{
	struct json_token *root, *groups, *netkey, *token;
	int ret = -1;
	EVP_PKEY *key = NULL;
	const struct dpp_curve_params *curve;
	unsigned int rules = 0;

	root = json_parse((const char *) payload, payload_len);
	if (!root) {
		wpa_printf(MSG_DEBUG, "DPP: JSON parsing of connector failed");
		goto fail;
	}

	groups = json_get_member(root, "groups");
	if (!groups || groups->type != JSON_ARRAY) {
		wpa_printf(MSG_DEBUG, "DPP: No groups array found");
		goto skip_groups;
	}
	for (token = groups->child; token; token = token->sibling) {
		struct json_token *id, *role;

		id = json_get_member(token, "groupId");
		if (!id || id->type != JSON_STRING) {
			wpa_printf(MSG_DEBUG, "DPP: Missing groupId string");
			goto fail;
		}

		role = json_get_member(token, "netRole");
		if (!role || role->type != JSON_STRING) {
			wpa_printf(MSG_DEBUG, "DPP: Missing netRole string");
			goto fail;
		}
		wpa_printf(MSG_DEBUG,
			   "DPP: connector group: groupId='%s' netRole='%s'",
			   id->string, role->string);
		rules++;
	}
skip_groups:

	if (!rules) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Connector includes no groups");
		goto fail;
	}

	token = json_get_member(root, "expiry");
	if (!token || token->type != JSON_STRING) {
		wpa_printf(MSG_DEBUG,
			   "DPP: No expiry string found - connector does not expire");
	} else {
		wpa_printf(MSG_DEBUG, "DPP: expiry = %s", token->string);
		if (dpp_key_expired(token->string,
				    &auth->net_access_key_expiry)) {
			wpa_printf(MSG_DEBUG,
				   "DPP: Connector (netAccessKey) has expired");
			goto fail;
		}
	}

	netkey = json_get_member(root, "netAccessKey");
	if (!netkey || netkey->type != JSON_OBJECT) {
		wpa_printf(MSG_DEBUG, "DPP: No netAccessKey object found");
		goto fail;
	}

	key = dpp_parse_jwk(netkey, &curve);
	if (!key)
		goto fail;
	dpp_debug_print_key("DPP: Received netAccessKey", key);

	if (EVP_PKEY_cmp(key, auth->own_protocol_key) != 1) {
		wpa_printf(MSG_DEBUG,
			   "DPP: netAccessKey in connector does not match own protocol key");
#ifdef CONFIG_TESTING_OPTIONS
		if (auth->ignore_netaccesskey_mismatch) {
			wpa_printf(MSG_DEBUG,
				   "DPP: TESTING - skip netAccessKey mismatch");
		} else {
			goto fail;
		}
#else /* CONFIG_TESTING_OPTIONS */
		goto fail;
#endif /* CONFIG_TESTING_OPTIONS */
	}

	ret = 0;
fail:
	EVP_PKEY_free(key);
	json_free(root);
	return ret;
}