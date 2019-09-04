#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  super; } ;
typedef  TYPE_1__ ptls_openssl_sign_certificate_t ;
struct TYPE_6__ {int /*<<< orphan*/ * sign_certificate; } ;
typedef  TYPE_2__ ptls_context_t ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_new_file (char const*,char*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_openssl_init_sign_certificate (TYPE_1__*,int /*<<< orphan*/ *) ; 

void SetSignCertificate(char const * keypem, ptls_context_t * ctx)
{
    static ptls_openssl_sign_certificate_t signer;

    EVP_PKEY *pkey = EVP_PKEY_new();
    BIO* bio_key = BIO_new_file(keypem, "rb");
    PEM_read_bio_PrivateKey(bio_key, &pkey, NULL, NULL);
    ptls_openssl_init_sign_certificate(&signer, pkey);
    EVP_PKEY_free(pkey);
    ctx->sign_certificate = &signer.super;
}