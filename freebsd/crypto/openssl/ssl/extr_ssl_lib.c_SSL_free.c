#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_4__* resp; int /*<<< orphan*/  ids; int /*<<< orphan*/  exts; } ;
struct TYPE_15__ {TYPE_4__* npn; TYPE_4__* tls13_cookie; TYPE_4__* alpn; TYPE_1__ ocsp; TYPE_4__* scts; TYPE_4__* peer_supportedgroups; TYPE_4__* supportedgroups; TYPE_4__* peer_ecpointformats; TYPE_4__* ecpointformats; TYPE_4__* hostname; } ;
struct TYPE_16__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  srtp_profiles; TYPE_3__ ext; int /*<<< orphan*/  waitctx; int /*<<< orphan*/  ctx; int /*<<< orphan*/  rlayer; TYPE_2__* method; int /*<<< orphan*/  verified_chain; int /*<<< orphan*/  client_ca_names; int /*<<< orphan*/  ca_names; int /*<<< orphan*/  pha_dgst; struct TYPE_16__* pha_context; struct TYPE_16__* clienthello; int /*<<< orphan*/  scts; int /*<<< orphan*/  session_ctx; struct TYPE_16__* shared_sigalgs; int /*<<< orphan*/  cert; struct TYPE_16__* psksession_id; int /*<<< orphan*/ * psksession; int /*<<< orphan*/ * session; int /*<<< orphan*/  peer_ciphers; int /*<<< orphan*/  tls13_ciphersuites; int /*<<< orphan*/  cipher_list_by_id; int /*<<< orphan*/  cipher_list; int /*<<< orphan*/  init_buf; int /*<<< orphan*/  rbio; int /*<<< orphan*/  wbio; int /*<<< orphan*/  ex_data; int /*<<< orphan*/  dane; int /*<<< orphan*/  param; int /*<<< orphan*/  references; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* ssl_free ) (TYPE_4__*) ;} ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_WAIT_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUF_MEM_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_EX_INDEX_SSL ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_free_ex_data (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCSP_RESPID_free ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_4__*) ; 
 int /*<<< orphan*/  RECORD_LAYER_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REF_ASSERT_ISNT (int) ; 
 int /*<<< orphan*/  REF_PRINT_COUNT (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  SCT_LIST_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_EXTENSION_free ; 
 int /*<<< orphan*/  X509_NAME_free ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free ; 
 int /*<<< orphan*/  clear_ciphers (TYPE_4__*) ; 
 int /*<<< orphan*/  dane_final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_OCSP_RESPID_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_SRTP_PROTECTION_PROFILE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_SSL_CIPHER_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_NAME_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_cert_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_clear_bad_session (TYPE_4__*) ; 
 int /*<<< orphan*/  ssl_free_wbio_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

void SSL_free(SSL *s)
{
    int i;

    if (s == NULL)
        return;
    CRYPTO_DOWN_REF(&s->references, &i, s->lock);
    REF_PRINT_COUNT("SSL", s);
    if (i > 0)
        return;
    REF_ASSERT_ISNT(i < 0);

    X509_VERIFY_PARAM_free(s->param);
    dane_final(&s->dane);
    CRYPTO_free_ex_data(CRYPTO_EX_INDEX_SSL, s, &s->ex_data);

    /* Ignore return value */
    ssl_free_wbio_buffer(s);

    BIO_free_all(s->wbio);
    BIO_free_all(s->rbio);

    BUF_MEM_free(s->init_buf);

    /* add extra stuff */
    sk_SSL_CIPHER_free(s->cipher_list);
    sk_SSL_CIPHER_free(s->cipher_list_by_id);
    sk_SSL_CIPHER_free(s->tls13_ciphersuites);
    sk_SSL_CIPHER_free(s->peer_ciphers);

    /* Make the next call work :-) */
    if (s->session != NULL) {
        ssl_clear_bad_session(s);
        SSL_SESSION_free(s->session);
    }
    SSL_SESSION_free(s->psksession);
    OPENSSL_free(s->psksession_id);

    clear_ciphers(s);

    ssl_cert_free(s->cert);
    OPENSSL_free(s->shared_sigalgs);
    /* Free up if allocated */

    OPENSSL_free(s->ext.hostname);
    SSL_CTX_free(s->session_ctx);
#ifndef OPENSSL_NO_EC
    OPENSSL_free(s->ext.ecpointformats);
    OPENSSL_free(s->ext.peer_ecpointformats);
    OPENSSL_free(s->ext.supportedgroups);
    OPENSSL_free(s->ext.peer_supportedgroups);
#endif                          /* OPENSSL_NO_EC */
    sk_X509_EXTENSION_pop_free(s->ext.ocsp.exts, X509_EXTENSION_free);
#ifndef OPENSSL_NO_OCSP
    sk_OCSP_RESPID_pop_free(s->ext.ocsp.ids, OCSP_RESPID_free);
#endif
#ifndef OPENSSL_NO_CT
    SCT_LIST_free(s->scts);
    OPENSSL_free(s->ext.scts);
#endif
    OPENSSL_free(s->ext.ocsp.resp);
    OPENSSL_free(s->ext.alpn);
    OPENSSL_free(s->ext.tls13_cookie);
    OPENSSL_free(s->clienthello);
    OPENSSL_free(s->pha_context);
    EVP_MD_CTX_free(s->pha_dgst);

    sk_X509_NAME_pop_free(s->ca_names, X509_NAME_free);
    sk_X509_NAME_pop_free(s->client_ca_names, X509_NAME_free);

    sk_X509_pop_free(s->verified_chain, X509_free);

    if (s->method != NULL)
        s->method->ssl_free(s);

    RECORD_LAYER_release(&s->rlayer);

    SSL_CTX_free(s->ctx);

    ASYNC_WAIT_CTX_free(s->waitctx);

#if !defined(OPENSSL_NO_NEXTPROTONEG)
    OPENSSL_free(s->ext.npn);
#endif

#ifndef OPENSSL_NO_SRTP
    sk_SRTP_PROTECTION_PROFILE_free(s->srtp_profiles);
#endif

    CRYPTO_THREAD_lock_free(s->lock);

    OPENSSL_free(s);
}