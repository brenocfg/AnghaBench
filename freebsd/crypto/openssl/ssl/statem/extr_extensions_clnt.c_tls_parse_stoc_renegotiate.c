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
struct TYPE_5__ {size_t previous_client_finished_len; size_t previous_server_finished_len; int send_connection_binding; int /*<<< orphan*/  previous_server_finished; int /*<<< orphan*/  previous_client_finished; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  PACKET_get_1_len (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  PACKET_get_bytes (int /*<<< orphan*/ *,unsigned char const**,scalar_t__) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PARSE_STOC_RENEGOTIATE ; 
 int /*<<< orphan*/  SSL_R_RENEGOTIATION_ENCODING_ERR ; 
 int /*<<< orphan*/  SSL_R_RENEGOTIATION_MISMATCH ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 

int tls_parse_stoc_renegotiate(SSL *s, PACKET *pkt, unsigned int context,
                               X509 *x, size_t chainidx)
{
    size_t expected_len = s->s3->previous_client_finished_len
        + s->s3->previous_server_finished_len;
    size_t ilen;
    const unsigned char *data;

    /* Check for logic errors */
    if (!ossl_assert(expected_len == 0
                     || s->s3->previous_client_finished_len != 0)
        || !ossl_assert(expected_len == 0
                        || s->s3->previous_server_finished_len != 0)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PARSE_STOC_RENEGOTIATE,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    /* Parse the length byte */
    if (!PACKET_get_1_len(pkt, &ilen)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_RENEGOTIATE,
                 SSL_R_RENEGOTIATION_ENCODING_ERR);
        return 0;
    }

    /* Consistency check */
    if (PACKET_remaining(pkt) != ilen) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PARSE_STOC_RENEGOTIATE,
                 SSL_R_RENEGOTIATION_ENCODING_ERR);
        return 0;
    }

    /* Check that the extension matches */
    if (ilen != expected_len) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_STOC_RENEGOTIATE,
                 SSL_R_RENEGOTIATION_MISMATCH);
        return 0;
    }

    if (!PACKET_get_bytes(pkt, &data, s->s3->previous_client_finished_len)
        || memcmp(data, s->s3->previous_client_finished,
                  s->s3->previous_client_finished_len) != 0) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_STOC_RENEGOTIATE,
                 SSL_R_RENEGOTIATION_MISMATCH);
        return 0;
    }

    if (!PACKET_get_bytes(pkt, &data, s->s3->previous_server_finished_len)
        || memcmp(data, s->s3->previous_server_finished,
                  s->s3->previous_server_finished_len) != 0) {
        SSLfatal(s, SSL_AD_ILLEGAL_PARAMETER, SSL_F_TLS_PARSE_STOC_RENEGOTIATE,
                 SSL_R_RENEGOTIATION_MISMATCH);
        return 0;
    }
    s->s3->send_connection_binding = 1;

    return 1;
}