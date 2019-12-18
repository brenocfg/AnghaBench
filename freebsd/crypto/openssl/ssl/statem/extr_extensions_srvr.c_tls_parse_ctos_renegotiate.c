#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {TYPE_1__* s3; } ;
struct TYPE_5__ {unsigned int previous_client_finished_len; int send_connection_binding; int /*<<< orphan*/  previous_client_finished; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_get_1 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_bytes (int /*<<< orphan*/ *,unsigned char const**,unsigned int) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_CTOS_RENEGOTIATE ; 
 int /*<<< orphan*/  SSL_R_RENEGOTIATION_ENCODING_ERR ; 
 int /*<<< orphan*/  SSL_R_RENEGOTIATION_MISMATCH ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,unsigned int) ; 

int tls_parse_ctos_renegotiate(SSL *s, PACKET *pkt, unsigned int context,
                               X509 *x, size_t chainidx)
{
    unsigned int ilen;
    const unsigned char *data;

    /* Parse the length byte */
    if (!PACKET_get_1(pkt, &ilen)
        || !PACKET_get_bytes(pkt, &data, ilen)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_CTOS_RENEGOTIATE,
                 SSL_R_RENEGOTIATION_ENCODING_ERR);
        return 0;
    }

    /* Check that the extension matches */
    if (ilen != s->s3->previous_client_finished_len) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS_PARSE_CTOS_RENEGOTIATE,
                 SSL_R_RENEGOTIATION_MISMATCH);
        return 0;
    }

    if (memcmp(data, s->s3->previous_client_finished,
               s->s3->previous_client_finished_len)) {
        SSLfatal(s, SSL_AD_HANDSHAKE_FAILURE, SSL_F_TLS_PARSE_CTOS_RENEGOTIATE,
                 SSL_R_RENEGOTIATION_MISMATCH);
        return 0;
    }

    s->s3->send_connection_binding = 1;

    return 1;
}