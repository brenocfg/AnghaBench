#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WRITE_TRAN ;
struct TYPE_9__ {int hand_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  ticket_expected; } ;
struct TYPE_8__ {int options; int /*<<< orphan*/  sent_tickets; int /*<<< orphan*/  num_tickets; int /*<<< orphan*/  hit; TYPE_1__ ext; int /*<<< orphan*/  post_handshake_auth; int /*<<< orphan*/  hello_retry_request; int /*<<< orphan*/  key_update; TYPE_3__ statem; } ;
typedef  TYPE_2__ SSL ;
typedef  TYPE_3__ OSSL_STATEM ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_OSSL_STATEM_SERVER13_WRITE_TRANSITION ; 
 int /*<<< orphan*/  SSL_HRR_COMPLETE ; 
 int /*<<< orphan*/  SSL_HRR_PENDING ; 
 int /*<<< orphan*/  SSL_KEY_UPDATE_NONE ; 
 int SSL_OP_ENABLE_MIDDLEBOX_COMPAT ; 
 int /*<<< orphan*/  SSL_PHA_EXT_RECEIVED ; 
 int /*<<< orphan*/  SSL_PHA_REQUESTED ; 
 int /*<<< orphan*/  SSL_PHA_REQUEST_PENDING ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  TLS_ST_EARLY_DATA 141 
#define  TLS_ST_OK 140 
#define  TLS_ST_SR_CLNT_HELLO 139 
#define  TLS_ST_SR_FINISHED 138 
#define  TLS_ST_SR_KEY_UPDATE 137 
#define  TLS_ST_SW_CERT 136 
#define  TLS_ST_SW_CERT_REQ 135 
#define  TLS_ST_SW_CERT_VRFY 134 
#define  TLS_ST_SW_CHANGE 133 
#define  TLS_ST_SW_ENCRYPTED_EXTENSIONS 132 
#define  TLS_ST_SW_FINISHED 131 
#define  TLS_ST_SW_KEY_UPDATE 130 
#define  TLS_ST_SW_SESSION_TICKET 129 
#define  TLS_ST_SW_SRVR_HELLO 128 
 int /*<<< orphan*/  WRITE_TRAN_CONTINUE ; 
 int /*<<< orphan*/  WRITE_TRAN_ERROR ; 
 int /*<<< orphan*/  WRITE_TRAN_FINISHED ; 
 int /*<<< orphan*/  send_certificate_request (TYPE_2__*) ; 

__attribute__((used)) static WRITE_TRAN ossl_statem_server13_write_transition(SSL *s)
{
    OSSL_STATEM *st = &s->statem;

    /*
     * No case for TLS_ST_BEFORE, because at that stage we have not negotiated
     * TLSv1.3 yet, so that is handled by ossl_statem_server_write_transition()
     */

    switch (st->hand_state) {
    default:
        /* Shouldn't happen */
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_OSSL_STATEM_SERVER13_WRITE_TRANSITION,
                 ERR_R_INTERNAL_ERROR);
        return WRITE_TRAN_ERROR;

    case TLS_ST_OK:
        if (s->key_update != SSL_KEY_UPDATE_NONE) {
            st->hand_state = TLS_ST_SW_KEY_UPDATE;
            return WRITE_TRAN_CONTINUE;
        }
        if (s->post_handshake_auth == SSL_PHA_REQUEST_PENDING) {
            st->hand_state = TLS_ST_SW_CERT_REQ;
            return WRITE_TRAN_CONTINUE;
        }
        /* Try to read from the client instead */
        return WRITE_TRAN_FINISHED;

    case TLS_ST_SR_CLNT_HELLO:
        st->hand_state = TLS_ST_SW_SRVR_HELLO;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_SRVR_HELLO:
        if ((s->options & SSL_OP_ENABLE_MIDDLEBOX_COMPAT) != 0
                && s->hello_retry_request != SSL_HRR_COMPLETE)
            st->hand_state = TLS_ST_SW_CHANGE;
        else if (s->hello_retry_request == SSL_HRR_PENDING)
            st->hand_state = TLS_ST_EARLY_DATA;
        else
            st->hand_state = TLS_ST_SW_ENCRYPTED_EXTENSIONS;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_CHANGE:
        if (s->hello_retry_request == SSL_HRR_PENDING)
            st->hand_state = TLS_ST_EARLY_DATA;
        else
            st->hand_state = TLS_ST_SW_ENCRYPTED_EXTENSIONS;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_ENCRYPTED_EXTENSIONS:
        if (s->hit)
            st->hand_state = TLS_ST_SW_FINISHED;
        else if (send_certificate_request(s))
            st->hand_state = TLS_ST_SW_CERT_REQ;
        else
            st->hand_state = TLS_ST_SW_CERT;

        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_CERT_REQ:
        if (s->post_handshake_auth == SSL_PHA_REQUEST_PENDING) {
            s->post_handshake_auth = SSL_PHA_REQUESTED;
            st->hand_state = TLS_ST_OK;
        } else {
            st->hand_state = TLS_ST_SW_CERT;
        }
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_CERT:
        st->hand_state = TLS_ST_SW_CERT_VRFY;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_CERT_VRFY:
        st->hand_state = TLS_ST_SW_FINISHED;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_FINISHED:
        st->hand_state = TLS_ST_EARLY_DATA;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_EARLY_DATA:
        return WRITE_TRAN_FINISHED;

    case TLS_ST_SR_FINISHED:
        /*
         * Technically we have finished the handshake at this point, but we're
         * going to remain "in_init" for now and write out any session tickets
         * immediately.
         */
        if (s->post_handshake_auth == SSL_PHA_REQUESTED) {
            s->post_handshake_auth = SSL_PHA_EXT_RECEIVED;
        } else if (!s->ext.ticket_expected) {
            /*
             * If we're not going to renew the ticket then we just finish the
             * handshake at this point.
             */
            st->hand_state = TLS_ST_OK;
            return WRITE_TRAN_CONTINUE;
        }
        if (s->num_tickets > s->sent_tickets)
            st->hand_state = TLS_ST_SW_SESSION_TICKET;
        else
            st->hand_state = TLS_ST_OK;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SR_KEY_UPDATE:
    case TLS_ST_SW_KEY_UPDATE:
        st->hand_state = TLS_ST_OK;
        return WRITE_TRAN_CONTINUE;

    case TLS_ST_SW_SESSION_TICKET:
        /* In a resumption we only ever send a maximum of one new ticket.
         * Following an initial handshake we send the number of tickets we have
         * been configured for.
         */
        if (s->hit || s->num_tickets <= s->sent_tickets) {
            /* We've written enough tickets out. */
            st->hand_state = TLS_ST_OK;
        }
        return WRITE_TRAN_CONTINUE;
    }
}