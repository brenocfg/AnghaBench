#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int hand_state; } ;
struct TYPE_14__ {TYPE_2__ statem; } ;
typedef  TYPE_1__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  TYPE_2__ OSSL_STATEM ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_SERVER_PROCESS_MESSAGE ; 
 int /*<<< orphan*/  SSLfatal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TLS_ST_SR_CERT 136 
#define  TLS_ST_SR_CERT_VRFY 135 
#define  TLS_ST_SR_CHANGE 134 
#define  TLS_ST_SR_CLNT_HELLO 133 
#define  TLS_ST_SR_END_OF_EARLY_DATA 132 
#define  TLS_ST_SR_FINISHED 131 
#define  TLS_ST_SR_KEY_EXCH 130 
#define  TLS_ST_SR_KEY_UPDATE 129 
#define  TLS_ST_SR_NEXT_PROTO 128 
 int /*<<< orphan*/  tls_process_cert_verify (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_change_cipher_spec (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_client_certificate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_client_hello (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_client_key_exchange (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_end_of_early_data (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_finished (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_key_update (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_process_next_proto (TYPE_1__*,int /*<<< orphan*/ *) ; 

MSG_PROCESS_RETURN ossl_statem_server_process_message(SSL *s, PACKET *pkt)
{
    OSSL_STATEM *st = &s->statem;

    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_OSSL_STATEM_SERVER_PROCESS_MESSAGE,
                 ERR_R_INTERNAL_ERROR);
        return MSG_PROCESS_ERROR;

    case TLS_ST_SR_CLNT_HELLO:
        return tls_process_client_hello(s, pkt);

    case TLS_ST_SR_END_OF_EARLY_DATA:
        return tls_process_end_of_early_data(s, pkt);

    case TLS_ST_SR_CERT:
        return tls_process_client_certificate(s, pkt);

    case TLS_ST_SR_KEY_EXCH:
        return tls_process_client_key_exchange(s, pkt);

    case TLS_ST_SR_CERT_VRFY:
        return tls_process_cert_verify(s, pkt);

#ifndef OPENSSL_NO_NEXTPROTONEG
    case TLS_ST_SR_NEXT_PROTO:
        return tls_process_next_proto(s, pkt);
#endif

    case TLS_ST_SR_CHANGE:
        return tls_process_change_cipher_spec(s, pkt);

    case TLS_ST_SR_FINISHED:
        return tls_process_finished(s, pkt);

    case TLS_ST_SR_KEY_UPDATE:
        return tls_process_key_update(s, pkt);

    }
}