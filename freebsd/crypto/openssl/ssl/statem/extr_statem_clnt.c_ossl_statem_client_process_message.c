#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int hand_state; } ;
struct TYPE_19__ {TYPE_2__ statem; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  TYPE_2__ OSSL_STATEM ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
#define  DTLS_ST_CR_HELLO_VERIFY_REQUEST 141 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_CLIENT_PROCESS_MESSAGE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TLS_ST_CR_CERT 140 
#define  TLS_ST_CR_CERT_REQ 139 
#define  TLS_ST_CR_CERT_STATUS 138 
#define  TLS_ST_CR_CERT_VRFY 137 
#define  TLS_ST_CR_CHANGE 136 
#define  TLS_ST_CR_ENCRYPTED_EXTENSIONS 135 
#define  TLS_ST_CR_FINISHED 134 
#define  TLS_ST_CR_HELLO_REQ 133 
#define  TLS_ST_CR_KEY_EXCH 132 
#define  TLS_ST_CR_KEY_UPDATE 131 
#define  TLS_ST_CR_SESSION_TICKET 130 
#define  TLS_ST_CR_SRVR_DONE 129 
#define  TLS_ST_CR_SRVR_HELLO 128 
 int /*<<< orphan*/  dtls_process_hello_verify (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_cert_status (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_cert_verify (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_certificate_request (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_change_cipher_spec (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_encrypted_extensions (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_finished (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_hello_req (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_key_exchange (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_key_update (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_new_session_ticket (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_server_certificate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_server_done (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_server_hello (TYPE_1__*,int /*<<< orphan*/ *) ; 

MSG_PROCESS_RETURN ossl_statem_client_process_message(SSL *s, PACKET *pkt)
{
    OSSL_STATEM *st = &s->statem;

    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_OSSL_STATEM_CLIENT_PROCESS_MESSAGE,
                 ERR_R_INTERNAL_ERROR);
        return MSG_PROCESS_ERROR;

    case TLS_ST_CR_SRVR_HELLO:
        return tls_process_server_hello(s, pkt);

    case DTLS_ST_CR_HELLO_VERIFY_REQUEST:
        return dtls_process_hello_verify(s, pkt);

    case TLS_ST_CR_CERT:
        return tls_process_server_certificate(s, pkt);

    case TLS_ST_CR_CERT_VRFY:
        return tls_process_cert_verify(s, pkt);

    case TLS_ST_CR_CERT_STATUS:
        return tls_process_cert_status(s, pkt);

    case TLS_ST_CR_KEY_EXCH:
        return tls_process_key_exchange(s, pkt);

    case TLS_ST_CR_CERT_REQ:
        return tls_process_certificate_request(s, pkt);

    case TLS_ST_CR_SRVR_DONE:
        return tls_process_server_done(s, pkt);

    case TLS_ST_CR_CHANGE:
        return tls_process_change_cipher_spec(s, pkt);

    case TLS_ST_CR_SESSION_TICKET:
        return tls_process_new_session_ticket(s, pkt);

    case TLS_ST_CR_FINISHED:
        return tls_process_finished(s, pkt);

    case TLS_ST_CR_HELLO_REQ:
        return tls_process_hello_req(s, pkt);

    case TLS_ST_CR_ENCRYPTED_EXTENSIONS:
        return tls_process_encrypted_extensions(s, pkt);

    case TLS_ST_CR_KEY_UPDATE:
        return tls_process_key_update(s, pkt);
    }
}