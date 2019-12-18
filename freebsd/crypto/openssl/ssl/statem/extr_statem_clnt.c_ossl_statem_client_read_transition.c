#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int hand_state; } ;
struct TYPE_22__ {int /*<<< orphan*/  ticket_expected; int /*<<< orphan*/  status_expected; int /*<<< orphan*/ * session_secret_cb; } ;
struct TYPE_23__ {int hit; int /*<<< orphan*/  rwstate; scalar_t__ init_num; TYPE_6__ ext; TYPE_5__* s3; TYPE_2__* session; int /*<<< orphan*/  version; TYPE_8__ statem; } ;
struct TYPE_20__ {TYPE_3__* new_cipher; } ;
struct TYPE_21__ {TYPE_4__ tmp; } ;
struct TYPE_19__ {int algorithm_auth; int algorithm_mkey; } ;
struct TYPE_17__ {int /*<<< orphan*/ * tick; } ;
struct TYPE_18__ {TYPE_1__ ext; } ;
typedef  TYPE_7__ SSL ;
typedef  TYPE_8__ OSSL_STATEM ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
 int DTLS1_MT_HELLO_VERIFY_REQUEST ; 
 void* DTLS_ST_CR_HELLO_VERIFY_REQUEST ; 
 int /*<<< orphan*/  SSL3_AD_UNEXPECTED_MESSAGE ; 
 int SSL3_MT_CERTIFICATE ; 
 int SSL3_MT_CERTIFICATE_REQUEST ; 
 int SSL3_MT_CERTIFICATE_STATUS ; 
 int SSL3_MT_CHANGE_CIPHER_SPEC ; 
 int SSL3_MT_FINISHED ; 
 int SSL3_MT_HELLO_REQUEST ; 
 int SSL3_MT_NEWSESSION_TICKET ; 
 int SSL3_MT_SERVER_DONE ; 
 int SSL3_MT_SERVER_HELLO ; 
 int SSL3_MT_SERVER_KEY_EXCHANGE ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_CLIENT_READ_TRANSITION ; 
 scalar_t__ SSL_IS_DTLS (TYPE_7__*) ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_7__*) ; 
 int SSL_PSK ; 
 int /*<<< orphan*/  SSL_READING ; 
 int /*<<< orphan*/  SSL_R_UNEXPECTED_MESSAGE ; 
 int SSL_aNULL ; 
 int SSL_aPSK ; 
 int SSL_aSRP ; 
 int /*<<< orphan*/ * SSL_get_rbio (TYPE_7__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLS1_VERSION ; 
#define  TLS_ST_CR_CERT 138 
#define  TLS_ST_CR_CERT_REQ 137 
#define  TLS_ST_CR_CERT_STATUS 136 
#define  TLS_ST_CR_CHANGE 135 
 int TLS_ST_CR_FINISHED ; 
 int TLS_ST_CR_HELLO_REQ ; 
#define  TLS_ST_CR_KEY_EXCH 134 
#define  TLS_ST_CR_SESSION_TICKET 133 
 void* TLS_ST_CR_SRVR_DONE ; 
#define  TLS_ST_CR_SRVR_HELLO 132 
#define  TLS_ST_CW_CLNT_HELLO 131 
#define  TLS_ST_CW_FINISHED 130 
#define  TLS_ST_EARLY_DATA 129 
#define  TLS_ST_OK 128 
 int /*<<< orphan*/  cert_req_allowed (TYPE_7__*) ; 
 int key_exchange_expected (TYPE_7__*) ; 
 int /*<<< orphan*/  ossl_statem_client13_read_transition (TYPE_7__*,int) ; 

int ossl_statem_client_read_transition(SSL *s, int mt)
{
    OSSL_STATEM *st = &s->statem;
    int ske_expected;

    /*
     * Note that after writing the first ClientHello we don't know what version
     * we are going to negotiate yet, so we don't take this branch until later.
     */
    if (SSL_IS_TLS13(s)) {
        if (!ossl_statem_client13_read_transition(s, mt))
            goto err;
        return 1;
    }

    switch (st->hand_state) {
    default:
        break;

    case TLS_ST_CW_CLNT_HELLO:
        if (mt == SSL3_MT_SERVER_HELLO) {
            st->hand_state = TLS_ST_CR_SRVR_HELLO;
            return 1;
        }

        if (SSL_IS_DTLS(s)) {
            if (mt == DTLS1_MT_HELLO_VERIFY_REQUEST) {
                st->hand_state = DTLS_ST_CR_HELLO_VERIFY_REQUEST;
                return 1;
            }
        }
        break;

    case TLS_ST_EARLY_DATA:
        /*
         * We've not actually selected TLSv1.3 yet, but we have sent early
         * data. The only thing allowed now is a ServerHello or a
         * HelloRetryRequest.
         */
        if (mt == SSL3_MT_SERVER_HELLO) {
            st->hand_state = TLS_ST_CR_SRVR_HELLO;
            return 1;
        }
        break;

    case TLS_ST_CR_SRVR_HELLO:
        if (s->hit) {
            if (s->ext.ticket_expected) {
                if (mt == SSL3_MT_NEWSESSION_TICKET) {
                    st->hand_state = TLS_ST_CR_SESSION_TICKET;
                    return 1;
                }
            } else if (mt == SSL3_MT_CHANGE_CIPHER_SPEC) {
                st->hand_state = TLS_ST_CR_CHANGE;
                return 1;
            }
        } else {
            if (SSL_IS_DTLS(s) && mt == DTLS1_MT_HELLO_VERIFY_REQUEST) {
                st->hand_state = DTLS_ST_CR_HELLO_VERIFY_REQUEST;
                return 1;
            } else if (s->version >= TLS1_VERSION
                       && s->ext.session_secret_cb != NULL
                       && s->session->ext.tick != NULL
                       && mt == SSL3_MT_CHANGE_CIPHER_SPEC) {
                /*
                 * Normally, we can tell if the server is resuming the session
                 * from the session ID. EAP-FAST (RFC 4851), however, relies on
                 * the next server message after the ServerHello to determine if
                 * the server is resuming.
                 */
                s->hit = 1;
                st->hand_state = TLS_ST_CR_CHANGE;
                return 1;
            } else if (!(s->s3->tmp.new_cipher->algorithm_auth
                         & (SSL_aNULL | SSL_aSRP | SSL_aPSK))) {
                if (mt == SSL3_MT_CERTIFICATE) {
                    st->hand_state = TLS_ST_CR_CERT;
                    return 1;
                }
            } else {
                ske_expected = key_exchange_expected(s);
                /* SKE is optional for some PSK ciphersuites */
                if (ske_expected
                    || ((s->s3->tmp.new_cipher->algorithm_mkey & SSL_PSK)
                        && mt == SSL3_MT_SERVER_KEY_EXCHANGE)) {
                    if (mt == SSL3_MT_SERVER_KEY_EXCHANGE) {
                        st->hand_state = TLS_ST_CR_KEY_EXCH;
                        return 1;
                    }
                } else if (mt == SSL3_MT_CERTIFICATE_REQUEST
                           && cert_req_allowed(s)) {
                    st->hand_state = TLS_ST_CR_CERT_REQ;
                    return 1;
                } else if (mt == SSL3_MT_SERVER_DONE) {
                    st->hand_state = TLS_ST_CR_SRVR_DONE;
                    return 1;
                }
            }
        }
        break;

    case TLS_ST_CR_CERT:
        /*
         * The CertificateStatus message is optional even if
         * |ext.status_expected| is set
         */
        if (s->ext.status_expected && mt == SSL3_MT_CERTIFICATE_STATUS) {
            st->hand_state = TLS_ST_CR_CERT_STATUS;
            return 1;
        }
        /* Fall through */

    case TLS_ST_CR_CERT_STATUS:
        ske_expected = key_exchange_expected(s);
        /* SKE is optional for some PSK ciphersuites */
        if (ske_expected || ((s->s3->tmp.new_cipher->algorithm_mkey & SSL_PSK)
                             && mt == SSL3_MT_SERVER_KEY_EXCHANGE)) {
            if (mt == SSL3_MT_SERVER_KEY_EXCHANGE) {
                st->hand_state = TLS_ST_CR_KEY_EXCH;
                return 1;
            }
            goto err;
        }
        /* Fall through */

    case TLS_ST_CR_KEY_EXCH:
        if (mt == SSL3_MT_CERTIFICATE_REQUEST) {
            if (cert_req_allowed(s)) {
                st->hand_state = TLS_ST_CR_CERT_REQ;
                return 1;
            }
            goto err;
        }
        /* Fall through */

    case TLS_ST_CR_CERT_REQ:
        if (mt == SSL3_MT_SERVER_DONE) {
            st->hand_state = TLS_ST_CR_SRVR_DONE;
            return 1;
        }
        break;

    case TLS_ST_CW_FINISHED:
        if (s->ext.ticket_expected) {
            if (mt == SSL3_MT_NEWSESSION_TICKET) {
                st->hand_state = TLS_ST_CR_SESSION_TICKET;
                return 1;
            }
        } else if (mt == SSL3_MT_CHANGE_CIPHER_SPEC) {
            st->hand_state = TLS_ST_CR_CHANGE;
            return 1;
        }
        break;

    case TLS_ST_CR_SESSION_TICKET:
        if (mt == SSL3_MT_CHANGE_CIPHER_SPEC) {
            st->hand_state = TLS_ST_CR_CHANGE;
            return 1;
        }
        break;

    case TLS_ST_CR_CHANGE:
        if (mt == SSL3_MT_FINISHED) {
            st->hand_state = TLS_ST_CR_FINISHED;
            return 1;
        }
        break;

    case TLS_ST_OK:
        if (mt == SSL3_MT_HELLO_REQUEST) {
            st->hand_state = TLS_ST_CR_HELLO_REQ;
            return 1;
        }
        break;
    }

 err:
    /* No valid transition found */
    if (SSL_IS_DTLS(s) && mt == SSL3_MT_CHANGE_CIPHER_SPEC) {
        BIO *rbio;

        /*
         * CCS messages don't have a message sequence number so this is probably
         * because of an out-of-order CCS. We'll just drop it.
         */
        s->init_num = 0;
        s->rwstate = SSL_READING;
        rbio = SSL_get_rbio(s);
        BIO_clear_retry_flags(rbio);
        BIO_set_retry_read(rbio);
        return 0;
    }
    SSLfatal(s, SSL3_AD_UNEXPECTED_MESSAGE,
             SSL_F_OSSL_STATEM_CLIENT_READ_TRANSITION,
             SSL_R_UNEXPECTED_MESSAGE);
    return 0;
}