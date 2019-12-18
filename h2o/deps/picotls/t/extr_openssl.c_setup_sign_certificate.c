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
typedef  int /*<<< orphan*/  ptls_openssl_sign_certificate_t ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_bio_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_PRIVATE_KEY ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ptls_openssl_init_sign_certificate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_sign_certificate(ptls_openssl_sign_certificate_t *sc)
{
    BIO *bio = BIO_new_mem_buf(RSA_PRIVATE_KEY, (int)strlen(RSA_PRIVATE_KEY));
    EVP_PKEY *pkey = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
    assert(pkey != NULL || !"failed to load private key");
    BIO_free(bio);

    ptls_openssl_init_sign_certificate(sc, pkey);

    EVP_PKEY_free(pkey);
}