#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_7__ {int ticket_expected; int /*<<< orphan*/  session_ticket_cb_arg; int /*<<< orphan*/  (* session_ticket_cb ) (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_AD_UNSUPPORTED_EXTENSION ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_SESSION_TICKET ; 
 int /*<<< orphan*/  SSL_R_BAD_EXTENSION ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_use_ticket (TYPE_2__*) ; 

int tls_parse_stoc_session_ticket(SSL *s, PACKET *pkt, unsigned int context,
                                  X509 *x, size_t chainidx)
{
    if (s->ext.session_ticket_cb != NULL &&
        !s->ext.session_ticket_cb(s, PACKET_data(pkt),
                              PACKET_remaining(pkt),
                              s->ext.session_ticket_cb_arg)) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE,
                 SSL_F_TLS_PARSE_STOC_SESSION_TICKET, SSL_R_BAD_EXTENSION);
        return 0;
    }

    if (!tls_use_ticket(s)) {
        SSLfatal(s, SSL_AD_UNSUPPORTED_EXTENSION,
                 SSL_F_TLS_PARSE_STOC_SESSION_TICKET, SSL_R_BAD_EXTENSION);
        return 0;
    }
    if (PACKET_remaining(pkt) > 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_PARSE_STOC_SESSION_TICKET, SSL_R_BAD_EXTENSION);
        return 0;
    }

    s->ext.ticket_expected = 1;

    return 1;
}