#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct signature_alg {int /*<<< orphan*/  (* evp_md ) () ;int /*<<< orphan*/  sig_oid; } ;
typedef  int /*<<< orphan*/  hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_5__ {size_t length; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ heim_octet_string ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 size_t EVP_MD_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int set_digest_alg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static int
evp_md_create_signature(hx509_context context,
			const struct signature_alg *sig_alg,
			const hx509_private_key signer,
			const AlgorithmIdentifier *alg,
			const heim_octet_string *data,
			AlgorithmIdentifier *signatureAlgorithm,
			heim_octet_string *sig)
{
    size_t sigsize = EVP_MD_size(sig_alg->evp_md());
    EVP_MD_CTX *ctx;

    memset(sig, 0, sizeof(*sig));

    if (signatureAlgorithm) {
	int ret;
	ret = set_digest_alg(signatureAlgorithm, sig_alg->sig_oid,
			     "\x05\x00", 2);
	if (ret)
	    return ret;
    }


    sig->data = malloc(sigsize);
    if (sig->data == NULL) {
	sig->length = 0;
	return ENOMEM;
    }
    sig->length = sigsize;

    ctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(ctx, sig_alg->evp_md(), NULL);
    EVP_DigestUpdate(ctx, data->data, data->length);
    EVP_DigestFinal_ex(ctx, sig->data, NULL);
    EVP_MD_CTX_destroy(ctx);


    return 0;
}