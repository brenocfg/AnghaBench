#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int hand_state; int /*<<< orphan*/  no_cert_verify; } ;
struct TYPE_15__ {int verify_mode; int /*<<< orphan*/  rwstate; scalar_t__ init_num; TYPE_3__* s3; TYPE_2__* session; int /*<<< orphan*/  version; TYPE_5__ statem; } ;
struct TYPE_12__ {int /*<<< orphan*/  cert_request; } ;
struct TYPE_14__ {int /*<<< orphan*/  npn_seen; TYPE_1__ tmp; } ;
struct TYPE_13__ {int /*<<< orphan*/ * peer; } ;
typedef  TYPE_4__ SSL ;
typedef  TYPE_5__ OSSL_STATEM ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
#define  DTLS_ST_SW_HELLO_VERIFY_REQUEST 137 
 int /*<<< orphan*/  SSL3_AD_UNEXPECTED_MESSAGE ; 
 int SSL3_MT_CERTIFICATE ; 
 int SSL3_MT_CERTIFICATE_VERIFY ; 
 int SSL3_MT_CHANGE_CIPHER_SPEC ; 
 int SSL3_MT_CLIENT_HELLO ; 
 int SSL3_MT_CLIENT_KEY_EXCHANGE ; 
 int SSL3_MT_FINISHED ; 
 int SSL3_MT_NEXT_PROTO ; 
 int /*<<< orphan*/  SSL3_VERSION ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_SERVER_READ_TRANSITION ; 
 scalar_t__ SSL_IS_DTLS (TYPE_4__*) ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_READING ; 
 int /*<<< orphan*/  SSL_R_PEER_DID_NOT_RETURN_A_CERTIFICATE ; 
 int /*<<< orphan*/  SSL_R_UNEXPECTED_MESSAGE ; 
 int SSL_VERIFY_FAIL_IF_NO_PEER_CERT ; 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/ * SSL_get_rbio (TYPE_4__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TLS_ST_BEFORE 136 
#define  TLS_ST_OK 135 
#define  TLS_ST_SR_CERT 134 
#define  TLS_ST_SR_CERT_VRFY 133 
#define  TLS_ST_SR_CHANGE 132 
 int TLS_ST_SR_CLNT_HELLO ; 
 void* TLS_ST_SR_FINISHED ; 
#define  TLS_ST_SR_KEY_EXCH 131 
#define  TLS_ST_SR_NEXT_PROTO 130 
#define  TLS_ST_SW_FINISHED 129 
#define  TLS_ST_SW_SRVR_DONE 128 
 int /*<<< orphan*/  ossl_statem_server13_read_transition (TYPE_4__*,int) ; 

int ossl_statem_server_read_transition(SSL *s, int mt)
{
    OSSL_STATEM *st = &s->statem;

    if (SSL_IS_TLS13(s)) {
        if (!ossl_statem_server13_read_transition(s, mt))
            goto err;
        return 1;
    }

    switch (st->hand_state) {
    default:
        break;

    case TLS_ST_BEFORE:
    case TLS_ST_OK:
    case DTLS_ST_SW_HELLO_VERIFY_REQUEST:
        if (mt == SSL3_MT_CLIENT_HELLO) {
            st->hand_state = TLS_ST_SR_CLNT_HELLO;
            return 1;
        }
        break;

    case TLS_ST_SW_SRVR_DONE:
        /*
         * If we get a CKE message after a ServerDone then either
         * 1) We didn't request a Certificate
         * OR
         * 2) If we did request one then
         *      a) We allow no Certificate to be returned
         *      AND
         *      b) We are running SSL3 (in TLS1.0+ the client must return a 0
         *         list if we requested a certificate)
         */
        if (mt == SSL3_MT_CLIENT_KEY_EXCHANGE) {
            if (s->s3->tmp.cert_request) {
                if (s->version == SSL3_VERSION) {
                    if ((s->verify_mode & SSL_VERIFY_PEER)
                        && (s->verify_mode & SSL_VERIFY_FAIL_IF_NO_PEER_CERT)) {
                        /*
                         * This isn't an unexpected message as such - we're just
                         * not going to accept it because we require a client
                         * cert.
                         */
                        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                                 SSL_F_OSSL_STATEM_SERVER_READ_TRANSITION,
                                 SSL_R_PEER_DID_NOT_RETURN_A_CERTIFICATE);
                        return 0;
                    }
                    st->hand_state = TLS_ST_SR_KEY_EXCH;
                    return 1;
                }
            } else {
                st->hand_state = TLS_ST_SR_KEY_EXCH;
                return 1;
            }
        } else if (s->s3->tmp.cert_request) {
            if (mt == SSL3_MT_CERTIFICATE) {
                st->hand_state = TLS_ST_SR_CERT;
                return 1;
            }
        }
        break;

    case TLS_ST_SR_CERT:
        if (mt == SSL3_MT_CLIENT_KEY_EXCHANGE) {
            st->hand_state = TLS_ST_SR_KEY_EXCH;
            return 1;
        }
        break;

    case TLS_ST_SR_KEY_EXCH:
        /*
         * We should only process a CertificateVerify message if we have
         * received a Certificate from the client. If so then |s->session->peer|
         * will be non NULL. In some instances a CertificateVerify message is
         * not required even if the peer has sent a Certificate (e.g. such as in
         * the case of static DH). In that case |st->no_cert_verify| should be
         * set.
         */
        if (s->session->peer == NULL || st->no_cert_verify) {
            if (mt == SSL3_MT_CHANGE_CIPHER_SPEC) {
                /*
                 * For the ECDH ciphersuites when the client sends its ECDH
                 * pub key in a certificate, the CertificateVerify message is
                 * not sent. Also for GOST ciphersuites when the client uses
                 * its key from the certificate for key exchange.
                 */
                st->hand_state = TLS_ST_SR_CHANGE;
                return 1;
            }
        } else {
            if (mt == SSL3_MT_CERTIFICATE_VERIFY) {
                st->hand_state = TLS_ST_SR_CERT_VRFY;
                return 1;
            }
        }
        break;

    case TLS_ST_SR_CERT_VRFY:
        if (mt == SSL3_MT_CHANGE_CIPHER_SPEC) {
            st->hand_state = TLS_ST_SR_CHANGE;
            return 1;
        }
        break;

    case TLS_ST_SR_CHANGE:
#ifndef OPENSSL_NO_NEXTPROTONEG
        if (s->s3->npn_seen) {
            if (mt == SSL3_MT_NEXT_PROTO) {
                st->hand_state = TLS_ST_SR_NEXT_PROTO;
                return 1;
            }
        } else {
#endif
            if (mt == SSL3_MT_FINISHED) {
                st->hand_state = TLS_ST_SR_FINISHED;
                return 1;
            }
#ifndef OPENSSL_NO_NEXTPROTONEG
        }
#endif
        break;

#ifndef OPENSSL_NO_NEXTPROTONEG
    case TLS_ST_SR_NEXT_PROTO:
        if (mt == SSL3_MT_FINISHED) {
            st->hand_state = TLS_ST_SR_FINISHED;
            return 1;
        }
        break;
#endif

    case TLS_ST_SW_FINISHED:
        if (mt == SSL3_MT_CHANGE_CIPHER_SPEC) {
            st->hand_state = TLS_ST_SR_CHANGE;
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
             SSL_F_OSSL_STATEM_SERVER_READ_TRANSITION,
             SSL_R_UNEXPECTED_MESSAGE);
    return 0;
}