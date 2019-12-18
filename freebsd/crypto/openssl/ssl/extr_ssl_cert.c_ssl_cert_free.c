#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; struct TYPE_6__* psk_identity_hint; int /*<<< orphan*/  custext; int /*<<< orphan*/  chain_store; int /*<<< orphan*/  verify_store; struct TYPE_6__* ctype; struct TYPE_6__* client_sigalgs; struct TYPE_6__* conf_sigalgs; int /*<<< orphan*/  dh_tmp; int /*<<< orphan*/  references; } ;
typedef  TYPE_1__ CERT ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  custom_exts_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_cert_clear_certs (TYPE_1__*) ; 

void ssl_cert_free(CERT *c)
{
    int i;

    if (c == NULL)
        return;
    CRYPTO_DOWN_REF(&c->references, &i, c->lock);
    REF_PRINT_COUNT("CERT", c);
    if (i > 0)
        return;
    REF_ASSERT_ISNT(i < 0);

#ifndef OPENSSL_NO_DH
    EVP_PKEY_free(c->dh_tmp);
#endif

    ssl_cert_clear_certs(c);
    OPENSSL_free(c->conf_sigalgs);
    OPENSSL_free(c->client_sigalgs);
    OPENSSL_free(c->ctype);
    X509_STORE_free(c->verify_store);
    X509_STORE_free(c->chain_store);
    custom_exts_free(&c->custext);
#ifndef OPENSSL_NO_PSK
    OPENSSL_free(c->psk_identity_hint);
#endif
    CRYPTO_THREAD_lock_free(c->lock);
    OPENSSL_free(c);
}