#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int pmslen; int /*<<< orphan*/  peer_cert_sigalgs; int /*<<< orphan*/  peer_sigalgs; TYPE_7__* pms; int /*<<< orphan*/  ciphers_raw; int /*<<< orphan*/  peer_ca_names; int /*<<< orphan*/  ctype; int /*<<< orphan*/ * pkey; } ;
struct TYPE_10__ {int /*<<< orphan*/  alpn_proposed; int /*<<< orphan*/  alpn_selected; TYPE_1__ tmp; int /*<<< orphan*/ * peer_tmp; } ;
struct TYPE_9__ {TYPE_7__* s3; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (TYPE_7__*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_SRP_CTX_free (TYPE_2__*) ; 
 int /*<<< orphan*/  X509_NAME_free ; 
 int /*<<< orphan*/  sk_X509_NAME_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl3_cleanup_key_block (TYPE_2__*) ; 
 int /*<<< orphan*/  ssl3_free_digest_list (TYPE_2__*) ; 

void ssl3_free(SSL *s)
{
    if (s == NULL || s->s3 == NULL)
        return;

    ssl3_cleanup_key_block(s);

#if !defined(OPENSSL_NO_EC) || !defined(OPENSSL_NO_DH)
    EVP_PKEY_free(s->s3->peer_tmp);
    s->s3->peer_tmp = NULL;
    EVP_PKEY_free(s->s3->tmp.pkey);
    s->s3->tmp.pkey = NULL;
#endif

    OPENSSL_free(s->s3->tmp.ctype);
    sk_X509_NAME_pop_free(s->s3->tmp.peer_ca_names, X509_NAME_free);
    OPENSSL_free(s->s3->tmp.ciphers_raw);
    OPENSSL_clear_free(s->s3->tmp.pms, s->s3->tmp.pmslen);
    OPENSSL_free(s->s3->tmp.peer_sigalgs);
    OPENSSL_free(s->s3->tmp.peer_cert_sigalgs);
    ssl3_free_digest_list(s);
    OPENSSL_free(s->s3->alpn_selected);
    OPENSSL_free(s->s3->alpn_proposed);

#ifndef OPENSSL_NO_SRP
    SSL_SRP_CTX_free(s);
#endif
    OPENSSL_clear_free(s->s3, sizeof(*s->s3));
    s->s3 = NULL;
}