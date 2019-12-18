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
struct dpp_curve_params {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int) ; 
 int /*<<< orphan*/  EC_KEY_set_asn1_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_keygen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int EVP_PKEY_keygen_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int EVP_PKEY_set1_EC_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int NID_undef ; 
 int OBJ_txt2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_EC_NAMED_CURVE ; 
 int /*<<< orphan*/  dpp_debug_print_key (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ wpa_debug_show_keys ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static EVP_PKEY * dpp_gen_keypair(const struct dpp_curve_params *curve)
{
	EVP_PKEY_CTX *kctx = NULL;
	EC_KEY *ec_params = NULL;
	EVP_PKEY *params = NULL, *key = NULL;
	int nid;

	wpa_printf(MSG_DEBUG, "DPP: Generating a keypair");

	nid = OBJ_txt2nid(curve->name);
	if (nid == NID_undef) {
		wpa_printf(MSG_INFO, "DPP: Unsupported curve %s", curve->name);
		return NULL;
	}

	ec_params = EC_KEY_new_by_curve_name(nid);
	if (!ec_params) {
		wpa_printf(MSG_ERROR,
			   "DPP: Failed to generate EC_KEY parameters");
		goto fail;
	}
	EC_KEY_set_asn1_flag(ec_params, OPENSSL_EC_NAMED_CURVE);
	params = EVP_PKEY_new();
	if (!params || EVP_PKEY_set1_EC_KEY(params, ec_params) != 1) {
		wpa_printf(MSG_ERROR,
			   "DPP: Failed to generate EVP_PKEY parameters");
		goto fail;
	}

	kctx = EVP_PKEY_CTX_new(params, NULL);
	if (!kctx ||
	    EVP_PKEY_keygen_init(kctx) != 1 ||
	    EVP_PKEY_keygen(kctx, &key) != 1) {
		wpa_printf(MSG_ERROR, "DPP: Failed to generate EC key");
		key = NULL;
		goto fail;
	}

	if (wpa_debug_show_keys)
		dpp_debug_print_key("Own generated key", key);

fail:
	EC_KEY_free(ec_params);
	EVP_PKEY_free(params);
	EVP_PKEY_CTX_free(kctx);
	return key;
}