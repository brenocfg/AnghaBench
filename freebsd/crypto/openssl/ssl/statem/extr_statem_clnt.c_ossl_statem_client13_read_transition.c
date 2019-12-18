#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int hand_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  post_handshake_auth; int /*<<< orphan*/  hit; TYPE_2__ statem; } ;
typedef  TYPE_1__ SSL ;
typedef  TYPE_2__ OSSL_STATEM ;

/* Variables and functions */
 int SSL3_MT_CERTIFICATE ; 
 int SSL3_MT_CERTIFICATE_REQUEST ; 
 int SSL3_MT_CERTIFICATE_VERIFY ; 
 int SSL3_MT_ENCRYPTED_EXTENSIONS ; 
 int SSL3_MT_FINISHED ; 
 int SSL3_MT_KEY_UPDATE ; 
 int SSL3_MT_NEWSESSION_TICKET ; 
 int SSL3_MT_SERVER_HELLO ; 
 int /*<<< orphan*/  SSL_IS_DTLS (TYPE_1__*) ; 
 int /*<<< orphan*/  SSL_PHA_EXT_SENT ; 
 int /*<<< orphan*/  SSL_PHA_REQUESTED ; 
#define  TLS_ST_CR_CERT 134 
#define  TLS_ST_CR_CERT_REQ 133 
#define  TLS_ST_CR_CERT_VRFY 132 
#define  TLS_ST_CR_ENCRYPTED_EXTENSIONS 131 
 void* TLS_ST_CR_FINISHED ; 
 int TLS_ST_CR_KEY_UPDATE ; 
 int TLS_ST_CR_SESSION_TICKET ; 
#define  TLS_ST_CR_SRVR_HELLO 130 
#define  TLS_ST_CW_CLNT_HELLO 129 
#define  TLS_ST_OK 128 
 int /*<<< orphan*/  tls13_restore_handshake_digest_for_pha (TYPE_1__*) ; 

__attribute__((used)) static int ossl_statem_client13_read_transition(SSL *s, int mt)
{
    OSSL_STATEM *st = &s->statem;

    /*
     * Note: There is no case for TLS_ST_CW_CLNT_HELLO, because we haven't
     * yet negotiated TLSv1.3 at that point so that is handled by
     * ossl_statem_client_read_transition()
     */

    switch (st->hand_state) {
    default:
        break;

    case TLS_ST_CW_CLNT_HELLO:
        /*
         * This must a ClientHello following a HelloRetryRequest, so the only
         * thing we can get now is a ServerHello.
         */
        if (mt == SSL3_MT_SERVER_HELLO) {
            st->hand_state = TLS_ST_CR_SRVR_HELLO;
            return 1;
        }
        break;

    case TLS_ST_CR_SRVR_HELLO:
        if (mt == SSL3_MT_ENCRYPTED_EXTENSIONS) {
            st->hand_state = TLS_ST_CR_ENCRYPTED_EXTENSIONS;
            return 1;
        }
        break;

    case TLS_ST_CR_ENCRYPTED_EXTENSIONS:
        if (s->hit) {
            if (mt == SSL3_MT_FINISHED) {
                st->hand_state = TLS_ST_CR_FINISHED;
                return 1;
            }
        } else {
            if (mt == SSL3_MT_CERTIFICATE_REQUEST) {
                st->hand_state = TLS_ST_CR_CERT_REQ;
                return 1;
            }
            if (mt == SSL3_MT_CERTIFICATE) {
                st->hand_state = TLS_ST_CR_CERT;
                return 1;
            }
        }
        break;

    case TLS_ST_CR_CERT_REQ:
        if (mt == SSL3_MT_CERTIFICATE) {
            st->hand_state = TLS_ST_CR_CERT;
            return 1;
        }
        break;

    case TLS_ST_CR_CERT:
        if (mt == SSL3_MT_CERTIFICATE_VERIFY) {
            st->hand_state = TLS_ST_CR_CERT_VRFY;
            return 1;
        }
        break;

    case TLS_ST_CR_CERT_VRFY:
        if (mt == SSL3_MT_FINISHED) {
            st->hand_state = TLS_ST_CR_FINISHED;
            return 1;
        }
        break;

    case TLS_ST_OK:
        if (mt == SSL3_MT_NEWSESSION_TICKET) {
            st->hand_state = TLS_ST_CR_SESSION_TICKET;
            return 1;
        }
        if (mt == SSL3_MT_KEY_UPDATE) {
            st->hand_state = TLS_ST_CR_KEY_UPDATE;
            return 1;
        }
        if (mt == SSL3_MT_CERTIFICATE_REQUEST) {
#if DTLS_MAX_VERSION != DTLS1_2_VERSION
# error TODO(DTLS1.3): Restore digest for PHA before adding message.
#endif
            if (!SSL_IS_DTLS(s) && s->post_handshake_auth == SSL_PHA_EXT_SENT) {
                s->post_handshake_auth = SSL_PHA_REQUESTED;
                /*
                 * In TLS, this is called before the message is added to the
                 * digest. In DTLS, this is expected to be called after adding
                 * to the digest. Either move the digest restore, or add the
                 * message here after the swap, or do it after the clientFinished?
                 */
                if (!tls13_restore_handshake_digest_for_pha(s)) {
                    /* SSLfatal() already called */
                    return 0;
                }
                st->hand_state = TLS_ST_CR_CERT_REQ;
                return 1;
            }
        }
        break;
    }

    /* No valid transition found */
    return 0;
}