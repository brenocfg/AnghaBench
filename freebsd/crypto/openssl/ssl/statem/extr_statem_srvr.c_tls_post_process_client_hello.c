#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORK_STATE ;
struct TYPE_22__ {scalar_t__ ticket_expected; } ;
struct TYPE_27__ {void* rwstate; TYPE_5__* session; TYPE_4__* s3; TYPE_2__ ext; scalar_t__ (* not_resumable_session_cb ) (TYPE_7__*,int) ;int /*<<< orphan*/  hit; int /*<<< orphan*/  peer_ciphers; TYPE_1__* cert; } ;
struct TYPE_26__ {int algorithm_mkey; } ;
struct TYPE_25__ {TYPE_6__ const* cipher; scalar_t__ not_resumable; } ;
struct TYPE_23__ {TYPE_6__ const* new_cipher; } ;
struct TYPE_24__ {TYPE_3__ tmp; } ;
struct TYPE_21__ {int (* cert_cb ) (TYPE_7__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cert_cb_arg; } ;
typedef  TYPE_6__ SSL_CIPHER ;
typedef  TYPE_7__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_POST_PROCESS_CLIENT_HELLO ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_7__*) ; 
 void* SSL_NOTHING ; 
 int /*<<< orphan*/  SSL_R_CERT_CB_ERROR ; 
 int /*<<< orphan*/  SSL_R_NO_SHARED_CIPHER ; 
 void* SSL_X509_LOOKUP ; 
 int /*<<< orphan*/  SSL_get_ciphers (TYPE_7__*) ; 
 int SSL_kDHE ; 
 int SSL_kECDHE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WORK_ERROR ; 
 scalar_t__ WORK_FINISHED_STOP ; 
 scalar_t__ WORK_MORE_A ; 
 scalar_t__ WORK_MORE_B ; 
 scalar_t__ WORK_MORE_C ; 
 TYPE_6__* ssl3_choose_cipher (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssl_check_srp_ext_ClientHello (TYPE_7__*) ; 
 int stub1 (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_7__*,int) ; 
 int /*<<< orphan*/  tls_choose_sigalg (TYPE_7__*,int) ; 
 int tls_early_post_process_client_hello (TYPE_7__*) ; 
 int /*<<< orphan*/  tls_handle_alpn (TYPE_7__*) ; 
 int /*<<< orphan*/  tls_handle_status_request (TYPE_7__*) ; 

WORK_STATE tls_post_process_client_hello(SSL *s, WORK_STATE wst)
{
    const SSL_CIPHER *cipher;

    if (wst == WORK_MORE_A) {
        int rv = tls_early_post_process_client_hello(s);
        if (rv == 0) {
            /* SSLfatal() was already called */
            goto err;
        }
        if (rv < 0)
            return WORK_MORE_A;
        wst = WORK_MORE_B;
    }
    if (wst == WORK_MORE_B) {
        if (!s->hit || SSL_IS_TLS13(s)) {
            /* Let cert callback update server certificates if required */
            if (!s->hit && s->cert->cert_cb != NULL) {
                int rv = s->cert->cert_cb(s, s->cert->cert_cb_arg);
                if (rv == 0) {
                    SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                             SSL_F_TLS_POST_PROCESS_CLIENT_HELLO,
                             SSL_R_CERT_CB_ERROR);
                    goto err;
                }
                if (rv < 0) {
                    s->rwstate = SSL_X509_LOOKUP;
                    return WORK_MORE_B;
                }
                s->rwstate = SSL_NOTHING;
            }

            /* In TLSv1.3 we selected the ciphersuite before resumption */
            if (!SSL_IS_TLS13(s)) {
                cipher =
                    ssl3_choose_cipher(s, s->peer_ciphers, SSL_get_ciphers(s));

                if (cipher == NULL) {
                    SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                             SSL_F_TLS_POST_PROCESS_CLIENT_HELLO,
                             SSL_R_NO_SHARED_CIPHER);
                    goto err;
                }
                s->s3->tmp.new_cipher = cipher;
            }
            if (!s->hit) {
                if (!tls_choose_sigalg(s, 1)) {
                    /* SSLfatal already called */
                    goto err;
                }
                /* check whether we should disable session resumption */
                if (s->not_resumable_session_cb != NULL)
                    s->session->not_resumable =
                        s->not_resumable_session_cb(s,
                            ((s->s3->tmp.new_cipher->algorithm_mkey
                              & (SSL_kDHE | SSL_kECDHE)) != 0));
                if (s->session->not_resumable)
                    /* do not send a session ticket */
                    s->ext.ticket_expected = 0;
            }
        } else {
            /* Session-id reuse */
            s->s3->tmp.new_cipher = s->session->cipher;
        }

        /*-
         * we now have the following setup.
         * client_random
         * cipher_list          - our preferred list of ciphers
         * ciphers              - the clients preferred list of ciphers
         * compression          - basically ignored right now
         * ssl version is set   - sslv3
         * s->session           - The ssl session has been setup.
         * s->hit               - session reuse flag
         * s->s3->tmp.new_cipher- the new cipher to use.
         */

        /*
         * Call status_request callback if needed. Has to be done after the
         * certificate callbacks etc above.
         */
        if (!tls_handle_status_request(s)) {
            /* SSLfatal() already called */
            goto err;
        }
        /*
         * Call alpn_select callback if needed.  Has to be done after SNI and
         * cipher negotiation (HTTP/2 restricts permitted ciphers). In TLSv1.3
         * we already did this because cipher negotiation happens earlier, and
         * we must handle ALPN before we decide whether to accept early_data.
         */
        if (!SSL_IS_TLS13(s) && !tls_handle_alpn(s)) {
            /* SSLfatal() already called */
            goto err;
        }

        wst = WORK_MORE_C;
    }
#ifndef OPENSSL_NO_SRP
    if (wst == WORK_MORE_C) {
        int ret;
        if ((ret = ssl_check_srp_ext_ClientHello(s)) == 0) {
            /*
             * callback indicates further work to be done
             */
            s->rwstate = SSL_X509_LOOKUP;
            return WORK_MORE_C;
        }
        if (ret < 0) {
            /* SSLfatal() already called */
            goto err;
        }
    }
#endif

    return WORK_FINISHED_STOP;
 err:
    return WORK_ERROR;
}