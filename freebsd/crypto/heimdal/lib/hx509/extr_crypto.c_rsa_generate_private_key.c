#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hx509_generate_private_context {long num_bits; } ;
typedef  TYPE_2__* hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {int /*<<< orphan*/ * rsa; } ;
struct TYPE_5__ {int /*<<< orphan*/  signature_alg; TYPE_1__ private_key; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OID_ID_PKCS1_SHA1WITHRSAENCRYPTION ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int const) ; 
 int HX509_PARSING_KEY_FAILED ; 
 int RSA_generate_key_ex (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
rsa_generate_private_key(hx509_context context,
			 struct hx509_generate_private_context *ctx,
			 hx509_private_key private_key)
{
    BIGNUM *e;
    int ret;
    unsigned long bits;

    static const int default_rsa_e = 65537;
    static const int default_rsa_bits = 2048;

    private_key->private_key.rsa = RSA_new();
    if (private_key->private_key.rsa == NULL) {
	hx509_set_error_string(context, 0, HX509_PARSING_KEY_FAILED,
			       "Failed to generate RSA key");
	return HX509_PARSING_KEY_FAILED;
    }

    e = BN_new();
    BN_set_word(e, default_rsa_e);

    bits = default_rsa_bits;

    if (ctx->num_bits)
	bits = ctx->num_bits;

    ret = RSA_generate_key_ex(private_key->private_key.rsa, bits, e, NULL);
    BN_free(e);
    if (ret != 1) {
	hx509_set_error_string(context, 0, HX509_PARSING_KEY_FAILED,
			       "Failed to generate RSA key");
	return HX509_PARSING_KEY_FAILED;
    }
    private_key->signature_alg = ASN1_OID_ID_PKCS1_SHA1WITHRSAENCRYPTION;

    return 0;
}