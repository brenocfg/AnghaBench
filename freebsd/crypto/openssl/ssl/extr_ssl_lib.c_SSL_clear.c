#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int mdpth; int pdpth; int /*<<< orphan*/ * mtlsa; int /*<<< orphan*/ * mcert; } ;
struct TYPE_15__ {int /*<<< orphan*/  rlayer; TYPE_3__* method; TYPE_2__* ctx; scalar_t__ shared_sigalgslen; int /*<<< orphan*/ * shared_sigalgs; int /*<<< orphan*/  param; TYPE_1__ dane; int /*<<< orphan*/ * pha_dgst; int /*<<< orphan*/  key_update; scalar_t__ first_packet; int /*<<< orphan*/ * init_buf; int /*<<< orphan*/  rwstate; int /*<<< orphan*/  version; int /*<<< orphan*/  client_version; scalar_t__ renegotiate; scalar_t__ shutdown; scalar_t__ hit; scalar_t__ error; scalar_t__ sent_tickets; scalar_t__ hello_retry_request; scalar_t__ psksession_id_len; int /*<<< orphan*/ * psksession_id; int /*<<< orphan*/ * psksession; int /*<<< orphan*/ * session; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* ssl_clear ) (TYPE_4__*) ;int /*<<< orphan*/  (* ssl_new ) (TYPE_4__*) ;int /*<<< orphan*/  (* ssl_free ) (TYPE_4__*) ;int /*<<< orphan*/  version; } ;
struct TYPE_13__ {TYPE_3__* method; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_MEM_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RECORD_LAYER_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_SSL_CLEAR ; 
 int /*<<< orphan*/  SSL_KEY_UPDATE_NONE ; 
 int /*<<< orphan*/  SSL_NOTHING ; 
 int /*<<< orphan*/  SSL_R_NO_METHOD_SPECIFIED ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_VERIFY_PARAM_move_peername (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_ciphers (TYPE_4__*) ; 
 int /*<<< orphan*/  ossl_statem_clear (TYPE_4__*) ; 
 scalar_t__ ssl_clear_bad_session (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 

int SSL_clear(SSL *s)
{
    if (s->method == NULL) {
        SSLerr(SSL_F_SSL_CLEAR, SSL_R_NO_METHOD_SPECIFIED);
        return 0;
    }

    if (ssl_clear_bad_session(s)) {
        SSL_SESSION_free(s->session);
        s->session = NULL;
    }
    SSL_SESSION_free(s->psksession);
    s->psksession = NULL;
    OPENSSL_free(s->psksession_id);
    s->psksession_id = NULL;
    s->psksession_id_len = 0;
    s->hello_retry_request = 0;
    s->sent_tickets = 0;

    s->error = 0;
    s->hit = 0;
    s->shutdown = 0;

    if (s->renegotiate) {
        SSLerr(SSL_F_SSL_CLEAR, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    ossl_statem_clear(s);

    s->version = s->method->version;
    s->client_version = s->version;
    s->rwstate = SSL_NOTHING;

    BUF_MEM_free(s->init_buf);
    s->init_buf = NULL;
    clear_ciphers(s);
    s->first_packet = 0;

    s->key_update = SSL_KEY_UPDATE_NONE;

    EVP_MD_CTX_free(s->pha_dgst);
    s->pha_dgst = NULL;

    /* Reset DANE verification result state */
    s->dane.mdpth = -1;
    s->dane.pdpth = -1;
    X509_free(s->dane.mcert);
    s->dane.mcert = NULL;
    s->dane.mtlsa = NULL;

    /* Clear the verification result peername */
    X509_VERIFY_PARAM_move_peername(s->param, NULL);

    /* Clear any shared connection state */
    OPENSSL_free(s->shared_sigalgs);
    s->shared_sigalgs = NULL;
    s->shared_sigalgslen = 0;

    /*
     * Check to see if we were changed into a different method, if so, revert
     * back.
     */
    if (s->method != s->ctx->method) {
        s->method->ssl_free(s);
        s->method = s->ctx->method;
        if (!s->method->ssl_new(s))
            return 0;
    } else {
        if (!s->method->ssl_clear(s))
            return 0;
    }

    RECORD_LAYER_clear(&s->rlayer);

    return 1;
}