#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct signature_alg {int /*<<< orphan*/  name; int /*<<< orphan*/  (* evp_md ) () ;} ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {size_t length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  Certificate ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 size_t EVP_MD_size (int /*<<< orphan*/ ) ; 
 int HX509_CRYPTO_BAD_SIGNATURE ; 
 int HX509_CRYPTO_SIG_INVALID_FORMAT ; 
 scalar_t__ ct_memcmp (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static int
evp_md_verify_signature(hx509_context context,
			const struct signature_alg *sig_alg,
			const Certificate *signer,
			const AlgorithmIdentifier *alg,
			const heim_octet_string *data,
			const heim_octet_string *sig)
{
    unsigned char digest[EVP_MAX_MD_SIZE];
    EVP_MD_CTX *ctx;
    size_t sigsize = EVP_MD_size(sig_alg->evp_md());

    if (sig->length != sigsize || sigsize > sizeof(digest)) {
	hx509_set_error_string(context, 0, HX509_CRYPTO_SIG_INVALID_FORMAT,
			       "SHA256 sigature have wrong length");
	return HX509_CRYPTO_SIG_INVALID_FORMAT;
    }

    ctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(ctx, sig_alg->evp_md(), NULL);
    EVP_DigestUpdate(ctx, data->data, data->length);
    EVP_DigestFinal_ex(ctx, digest, NULL);
    EVP_MD_CTX_destroy(ctx);

    if (ct_memcmp(digest, sig->data, sigsize) != 0) {
	hx509_set_error_string(context, 0, HX509_CRYPTO_BAD_SIGNATURE,
			       "Bad %s sigature", sig_alg->name);
	return HX509_CRYPTO_BAD_SIGNATURE;
    }

    return 0;
}