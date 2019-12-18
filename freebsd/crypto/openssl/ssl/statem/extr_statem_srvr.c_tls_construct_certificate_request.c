#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_17__ {scalar_t__ post_handshake_auth; int pha_context_len; TYPE_2__* s3; int /*<<< orphan*/  certreqs_sent; int /*<<< orphan*/ * pha_context; } ;
struct TYPE_15__ {int cert_request; } ;
struct TYPE_16__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 
 scalar_t__ RAND_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_EXT_TLS1_3_CERTIFICATE_REQUEST ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CERTIFICATE_REQUEST ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_3__*) ; 
 scalar_t__ SSL_PHA_REQUEST_PENDING ; 
 scalar_t__ SSL_USE_SIGALGS (TYPE_3__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_FLAGS_NON_ZERO_LENGTH ; 
 int /*<<< orphan*/  WPACKET_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_put_bytes_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_start_sub_packet_u8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WPACKET_sub_memcpy_u8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  construct_ca_names (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ca_names (TYPE_3__*) ; 
 int /*<<< orphan*/  ssl3_get_req_cert_type (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls12_copy_sigalgs (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t tls12_get_psigalgs (TYPE_3__*,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  tls13_restore_handshake_digest_for_pha (TYPE_3__*) ; 
 int /*<<< orphan*/  tls_construct_extensions (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int tls_construct_certificate_request(SSL *s, WPACKET *pkt)
{
    if (SSL_IS_TLS13(s)) {
        /* Send random context when doing post-handshake auth */
        if (s->post_handshake_auth == SSL_PHA_REQUEST_PENDING) {
            OPENSSL_free(s->pha_context);
            s->pha_context_len = 32;
            if ((s->pha_context = OPENSSL_malloc(s->pha_context_len)) == NULL
                    || RAND_bytes(s->pha_context, s->pha_context_len) <= 0
                    || !WPACKET_sub_memcpy_u8(pkt, s->pha_context, s->pha_context_len)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_CERTIFICATE_REQUEST,
                         ERR_R_INTERNAL_ERROR);
                return 0;
            }
            /* reset the handshake hash back to just after the ClientFinished */
            if (!tls13_restore_handshake_digest_for_pha(s)) {
                /* SSLfatal() already called */
                return 0;
            }
        } else {
            if (!WPACKET_put_bytes_u8(pkt, 0)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_CONSTRUCT_CERTIFICATE_REQUEST,
                         ERR_R_INTERNAL_ERROR);
                return 0;
            }
        }

        if (!tls_construct_extensions(s, pkt,
                                      SSL_EXT_TLS1_3_CERTIFICATE_REQUEST, NULL,
                                      0)) {
            /* SSLfatal() already called */
            return 0;
        }
        goto done;
    }

    /* get the list of acceptable cert types */
    if (!WPACKET_start_sub_packet_u8(pkt)
        || !ssl3_get_req_cert_type(s, pkt) || !WPACKET_close(pkt)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_TLS_CONSTRUCT_CERTIFICATE_REQUEST, ERR_R_INTERNAL_ERROR);
        return 0;
    }

    if (SSL_USE_SIGALGS(s)) {
        const uint16_t *psigs;
        size_t nl = tls12_get_psigalgs(s, 1, &psigs);

        if (!WPACKET_start_sub_packet_u16(pkt)
                || !WPACKET_set_flags(pkt, WPACKET_FLAGS_NON_ZERO_LENGTH)
                || !tls12_copy_sigalgs(s, pkt, psigs, nl)
                || !WPACKET_close(pkt)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_CONSTRUCT_CERTIFICATE_REQUEST,
                     ERR_R_INTERNAL_ERROR);
            return 0;
        }
    }

    if (!construct_ca_names(s, get_ca_names(s), pkt)) {
        /* SSLfatal() already called */
        return 0;
    }

 done:
    s->certreqs_sent++;
    s->s3->tmp.cert_request = 1;
    return 1;
}