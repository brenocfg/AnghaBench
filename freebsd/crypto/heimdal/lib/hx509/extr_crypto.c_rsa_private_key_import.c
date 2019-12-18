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
typedef  TYPE_2__* hx509_private_key ;
typedef  int hx509_key_format_t ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {int /*<<< orphan*/ * rsa; } ;
struct TYPE_5__ {int /*<<< orphan*/  signature_alg; TYPE_1__ private_key; } ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OID_ID_PKCS1_SHA1WITHRSAENCRYPTION ; 
 int HX509_CRYPTO_KEY_FORMAT_UNSUPPORTED ; 
#define  HX509_KEY_FORMAT_DER 128 
 int HX509_PARSING_KEY_FAILED ; 
 int /*<<< orphan*/ * d2i_RSAPrivateKey (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
rsa_private_key_import(hx509_context context,
		       const AlgorithmIdentifier *keyai,
		       const void *data,
		       size_t len,
		       hx509_key_format_t format,
		       hx509_private_key private_key)
{
    switch (format) {
    case HX509_KEY_FORMAT_DER: {
	const unsigned char *p = data;

	private_key->private_key.rsa =
	    d2i_RSAPrivateKey(NULL, &p, len);
	if (private_key->private_key.rsa == NULL) {
	    hx509_set_error_string(context, 0, HX509_PARSING_KEY_FAILED,
				   "Failed to parse RSA key");
	    return HX509_PARSING_KEY_FAILED;
	}
	private_key->signature_alg = ASN1_OID_ID_PKCS1_SHA1WITHRSAENCRYPTION;
	break;

    }
    default:
	return HX509_CRYPTO_KEY_FORMAT_UNSUPPORTED;
    }

    return 0;
}