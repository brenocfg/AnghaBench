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
typedef  int /*<<< orphan*/  WRITE_TRAN ;
struct TYPE_15__ {int hand_state; } ;
struct TYPE_14__ {int options; int /*<<< orphan*/  hit; TYPE_2__* s3; int /*<<< orphan*/  early_data_state; int /*<<< orphan*/  hello_retry_request; int /*<<< orphan*/  renegotiate; TYPE_4__ statem; } ;
struct TYPE_12__ {int cert_req; } ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  npn_seen; TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;
typedef  TYPE_4__ OSSL_STATEM ;

/* Variables and functions */
#define  DTLS_ST_CR_HELLO_VERIFY_REQUEST 142 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_CONNECTING ; 
 int /*<<< orphan*/  SSL_EARLY_DATA_FINISHED_WRITING ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_CLIENT_WRITE_TRANSITION ; 
 int /*<<< orphan*/  SSL_HRR_PENDING ; 
 int /*<<< orphan*/  SSL_IS_DTLS (TYPE_3__*) ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_3__*) ; 
 int SSL_OP_ENABLE_MIDDLEBOX_COMPAT ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TLS1_FLAGS_SKIP_CERT_VERIFY ; 
#define  TLS_ST_BEFORE 141 
#define  TLS_ST_CR_FINISHED 140 
#define  TLS_ST_CR_HELLO_REQ 139 
#define  TLS_ST_CR_SRVR_DONE 138 
#define  TLS_ST_CR_SRVR_HELLO 137 
#define  TLS_ST_CW_CERT 136 
#define  TLS_ST_CW_CERT_VRFY 135 
#define  TLS_ST_CW_CHANGE 134 
#define  TLS_ST_CW_CLNT_HELLO 133 
#define  TLS_ST_CW_FINISHED 132 
#define  TLS_ST_CW_KEY_EXCH 131 
#define  TLS_ST_CW_NEXT_PROTO 130 
#define  TLS_ST_EARLY_DATA 129 
#define  TLS_ST_OK 128 
 int /*<<< orphan*/  WRITE_TRAN_CONTINUE ; 
 int /*<<< orphan*/  WRITE_TRAN_ERROR ; 
 int /*<<< orphan*/  WRITE_TRAN_FINISHED ; 
 int /*<<< orphan*/  ossl_statem_client13_write_transition (TYPE_3__*) ; 
 int /*<<< orphan*/  ssl3_renegotiate_check (TYPE_3__*,int) ; 
 int /*<<< orphan*/  tls_setup_handshake (TYPE_3__*) ; 

WRITE_TRAN ossl_statem_client_write_transition(SSL *s)
{
    OSSL_STATEM *st = &s->statem;

    /*
     * Note that immediately before/after a ClientHello we don't know what
     * version we are going to negotiate yet, so we don't take this branch until
     * later
     */
    if (SSL_IS_TLS13(s))
        return ossl_statem_client13_write_transition(s);

    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_OSSL_STATEM_CLIENT_WRITE_TRANSITION,
                 ERR_R_INTERNAL_ERROR);
        return WRITE_TRAN_ERROR;

    case TLS_ST_OK:
        if (!s->renegotiate) {
            /*
             * We haven't requested a renegotiation ourselves so we must have
             * received a message from the server. Better read it.
             */
            return WRITE_TRAN_FINISHED;
        }
        /* Renegotiation */
        /* fall thru */
    case TLS_ST_BEFORE:
        st->hand_state = TLS_ST_CW_CLNT_HELLO;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CW_CLNT_HELLO:
        if (s->early_data_state == SSL_EARLY_DATA_CONNECTING) {
            /*
             * We are assuming this is a TLSv1.3 connection, although we haven't
             * actually selected a version yet.
             */
            if ((s->options & SSL_OP_ENABLE_MIDDLEBOX_COMPAT) != 0)
                st->hand_state = TLS_ST_CW_CHANGE;
            else
                st->hand_state = TLS_ST_EARLY_DATA;
            return WRITE_TRAN_CONTINUE;
        }
        /*
         * No transition at the end of writing because we don't know what
         * we will be sent
         */
        return WRITE_TRAN_FINISHED;

    case TLS_ST_CR_SRVR_HELLO:
        /*
         * We only get here in TLSv1.3. We just received an HRR, so issue a
         * CCS unless middlebox compat mode is off, or we already issued one
         * because we did early data.
         */
        if ((s->options & SSL_OP_ENABLE_MIDDLEBOX_COMPAT) != 0
                && s->early_data_state != SSL_EARLY_DATA_FINISHED_WRITING)
            st->hand_state = TLS_ST_CW_CHANGE;
        else
            st->hand_state = TLS_ST_CW_CLNT_HELLO;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_EARLY_DATA:
        return WRITE_TRAN_FINISHED;

    case DTLS_ST_CR_HELLO_VERIFY_REQUEST:
        st->hand_state = TLS_ST_CW_CLNT_HELLO;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CR_SRVR_DONE:
        if (s->s3->tmp.cert_req)
            st->hand_state = TLS_ST_CW_CERT;
        else
            st->hand_state = TLS_ST_CW_KEY_EXCH;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CW_CERT:
        st->hand_state = TLS_ST_CW_KEY_EXCH;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CW_KEY_EXCH:
        /*
         * For TLS, cert_req is set to 2, so a cert chain of nothing is
         * sent, but no verify packet is sent
         */
        /*
         * XXX: For now, we do not support client authentication in ECDH
         * cipher suites with ECDH (rather than ECDSA) certificates. We
         * need to skip the certificate verify message when client's
         * ECDH public key is sent inside the client certificate.
         */
        if (s->s3->tmp.cert_req == 1) {
            st->hand_state = TLS_ST_CW_CERT_VRFY;
        } else {
            st->hand_state = TLS_ST_CW_CHANGE;
        }
        if (s->s3->flags & TLS1_FLAGS_SKIP_CERT_VERIFY) {
            st->hand_state = TLS_ST_CW_CHANGE;
        }
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CW_CERT_VRFY:
        st->hand_state = TLS_ST_CW_CHANGE;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_CW_CHANGE:
        if (s->hello_retry_request == SSL_HRR_PENDING) {
            st->hand_state = TLS_ST_CW_CLNT_HELLO;
        } else if (s->early_data_state == SSL_EARLY_DATA_CONNECTING) {
            st->hand_state = TLS_ST_EARLY_DATA;
        } else {
#if defined(OPENSSL_NO_NEXTPROTONEG)
            st->hand_state = TLS_ST_CW_FINISHED;
#else
            if (!SSL_IS_DTLS(s) && s->s3->npn_seen)
                st->hand_state = TLS_ST_CW_NEXT_PROTO;
            else
                st->hand_state = TLS_ST_CW_FINISHED;
#endif
        }
        return WRITE_TRAN_CONTINUE;

#if !defined(OPENSSL_NO_NEXTPROTONEG)
    case TLS_ST_CW_NEXT_PROTO:
        st->hand_state = TLS_ST_CW_FINISHED;
        return WRITE_TRAN_CONTINUE;
#endif

    case TLS_ST_CW_FINISHED:
        if (s->hit) {
            st->hand_state = TLS_ST_OK;
            return WRITE_TRAN_CONTINUE;
        } else {
            return WRITE_TRAN_FINISHED;
        }

    case TLS_ST_CR_FINISHED:
        if (s->hit) {
            st->hand_state = TLS_ST_CW_CHANGE;
            return WRITE_TRAN_CONTINUE;
        } else {
            st->hand_state = TLS_ST_OK;
            return WRITE_TRAN_CONTINUE;
        }

    case TLS_ST_CR_HELLO_REQ:
        /*
         * If we can renegotiate now then do so, otherwise wait for a more
         * convenient time.
         */
        if (ssl3_renegotiate_check(s, 1)) {
            if (!tls_setup_handshake(s)) {
                /* SSLfatal() already called */
                return WRITE_TRAN_ERROR;
            }
            st->hand_state = TLS_ST_CW_CLNT_HELLO;
            return WRITE_TRAN_CONTINUE;
        }
        st->hand_state = TLS_ST_OK;
        return WRITE_TRAN_CONTINUE;
    }
}