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
struct wpabuf {int dummy; } ;
struct json_token {scalar_t__ type; int /*<<< orphan*/  string; } ;
struct dpp_curve_params {char* jws_alg; } ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_sha256 () ; 
 int /*<<< orphan*/ * EVP_sha384 () ; 
 int /*<<< orphan*/ * EVP_sha512 () ; 
 scalar_t__ JSON_OBJECT ; 
 scalar_t__ JSON_STRING ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  json_free (struct json_token*) ; 
 struct json_token* json_get_member (struct json_token*,char*) ; 
 struct wpabuf* json_get_member_base64url (struct json_token*,char*) ; 
 struct json_token* json_parse (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf *
dpp_parse_jws_prot_hdr(const struct dpp_curve_params *curve,
		       const u8 *prot_hdr, u16 prot_hdr_len,
		       const EVP_MD **ret_md)
{
	struct json_token *root, *token;
	struct wpabuf *kid = NULL;

	root = json_parse((const char *) prot_hdr, prot_hdr_len);
	if (!root) {
		wpa_printf(MSG_DEBUG,
			   "DPP: JSON parsing failed for JWS Protected Header");
		goto fail;
	}

	if (root->type != JSON_OBJECT) {
		wpa_printf(MSG_DEBUG,
			   "DPP: JWS Protected Header root is not an object");
		goto fail;
	}

	token = json_get_member(root, "typ");
	if (!token || token->type != JSON_STRING) {
		wpa_printf(MSG_DEBUG, "DPP: No typ string value found");
		goto fail;
	}
	wpa_printf(MSG_DEBUG, "DPP: JWS Protected Header typ=%s",
		   token->string);
	if (os_strcmp(token->string, "dppCon") != 0) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Unsupported JWS Protected Header typ=%s",
			   token->string);
		goto fail;
	}

	token = json_get_member(root, "alg");
	if (!token || token->type != JSON_STRING) {
		wpa_printf(MSG_DEBUG, "DPP: No alg string value found");
		goto fail;
	}
	wpa_printf(MSG_DEBUG, "DPP: JWS Protected Header alg=%s",
		   token->string);
	if (os_strcmp(token->string, curve->jws_alg) != 0) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Unexpected JWS Protected Header alg=%s (expected %s based on C-sign-key)",
			   token->string, curve->jws_alg);
		goto fail;
	}
	if (os_strcmp(token->string, "ES256") == 0 ||
	    os_strcmp(token->string, "BS256") == 0)
		*ret_md = EVP_sha256();
	else if (os_strcmp(token->string, "ES384") == 0 ||
		 os_strcmp(token->string, "BS384") == 0)
		*ret_md = EVP_sha384();
	else if (os_strcmp(token->string, "ES512") == 0 ||
		 os_strcmp(token->string, "BS512") == 0)
		*ret_md = EVP_sha512();
	else
		*ret_md = NULL;
	if (!*ret_md) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Unsupported JWS Protected Header alg=%s",
			   token->string);
		goto fail;
	}

	kid = json_get_member_base64url(root, "kid");
	if (!kid) {
		wpa_printf(MSG_DEBUG, "DPP: No kid string value found");
		goto fail;
	}
	wpa_hexdump_buf(MSG_DEBUG, "DPP: JWS Protected Header kid (decoded)",
			kid);

fail:
	json_free(root);
	return kid;
}