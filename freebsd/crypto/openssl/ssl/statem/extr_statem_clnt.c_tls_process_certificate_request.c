#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int shutdown; scalar_t__ post_handshake_auth; TYPE_2__* s3; scalar_t__ pha_context_len; int /*<<< orphan*/ * pha_context; } ;
struct TYPE_13__ {int cert_req; scalar_t__ ctype_len; int /*<<< orphan*/ * ctype; scalar_t__* valid_flags; } ;
struct TYPE_14__ {TYPE_1__ tmp; } ;
typedef  TYPE_3__ SSL ;
typedef  int /*<<< orphan*/  RAW_EXTENSION ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  MSG_PROCESS_RETURN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_PROCESSING ; 
 int /*<<< orphan*/  MSG_PROCESS_CONTINUE_READING ; 
 int /*<<< orphan*/  MSG_PROCESS_ERROR ; 
 int /*<<< orphan*/  MSG_PROCESS_FINISHED_READING ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_memdup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_EXT_TLS1_3_CERTIFICATE_REQUEST ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST ; 
 scalar_t__ SSL_IS_TLS13 (TYPE_3__*) ; 
 scalar_t__ SSL_PHA_REQUESTED ; 
 size_t SSL_PKEY_NUM ; 
 int /*<<< orphan*/  SSL_R_BAD_LENGTH ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SSL_R_SIGNATURE_ALGORITHMS_ERROR ; 
 int SSL_SENT_SHUTDOWN ; 
 scalar_t__ SSL_USE_SIGALGS (TYPE_3__*) ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_ca_names (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls1_process_sigalgs (TYPE_3__*) ; 
 int /*<<< orphan*/  tls1_save_sigalgs (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_collect_extensions (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls_parse_all_extensions (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

MSG_PROCESS_RETURN tls_process_certificate_request(SSL *s, PACKET *pkt)
{
    size_t i;

    /* Clear certificate validity flags */
    for (i = 0; i < SSL_PKEY_NUM; i++)
        s->s3->tmp.valid_flags[i] = 0;

    if (SSL_IS_TLS13(s)) {
        PACKET reqctx, extensions;
        RAW_EXTENSION *rawexts = NULL;

        if ((s->shutdown & SSL_SENT_SHUTDOWN) != 0) {
            /*
             * We already sent close_notify. This can only happen in TLSv1.3
             * post-handshake messages. We can't reasonably respond to this, so
             * we just ignore it
             */
            return MSG_PROCESS_FINISHED_READING;
        }

        /* Free and zero certificate types: it is not present in TLS 1.3 */
        OPENSSL_free(s->s3->tmp.ctype);
        s->s3->tmp.ctype = NULL;
        s->s3->tmp.ctype_len = 0;
        OPENSSL_free(s->pha_context);
        s->pha_context = NULL;

        if (!PACKET_get_length_prefixed_1(pkt, &reqctx) ||
            !PACKET_memdup(&reqctx, &s->pha_context, &s->pha_context_len)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST,
                     SSL_R_LENGTH_MISMATCH);
            return MSG_PROCESS_ERROR;
        }

        if (!PACKET_get_length_prefixed_2(pkt, &extensions)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST,
                     SSL_R_BAD_LENGTH);
            return MSG_PROCESS_ERROR;
        }
        if (!tls_collect_extensions(s, &extensions,
                                    SSL_EXT_TLS1_3_CERTIFICATE_REQUEST,
                                    &rawexts, NULL, 1)
            || !tls_parse_all_extensions(s, SSL_EXT_TLS1_3_CERTIFICATE_REQUEST,
                                         rawexts, NULL, 0, 1)) {
            /* SSLfatal() already called */
            OPENSSL_free(rawexts);
            return MSG_PROCESS_ERROR;
        }
        OPENSSL_free(rawexts);
        if (!tls1_process_sigalgs(s)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST,
                     SSL_R_BAD_LENGTH);
            return MSG_PROCESS_ERROR;
        }
    } else {
        PACKET ctypes;

        /* get the certificate types */
        if (!PACKET_get_length_prefixed_1(pkt, &ctypes)) {
            SSLfatal(s, SSL_AD_DECODE_ERROR,
                     SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST,
                     SSL_R_LENGTH_MISMATCH);
            return MSG_PROCESS_ERROR;
        }

        if (!PACKET_memdup(&ctypes, &s->s3->tmp.ctype, &s->s3->tmp.ctype_len)) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                     SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST,
                     ERR_R_INTERNAL_ERROR);
            return MSG_PROCESS_ERROR;
        }

        if (SSL_USE_SIGALGS(s)) {
            PACKET sigalgs;

            if (!PACKET_get_length_prefixed_2(pkt, &sigalgs)) {
                SSLfatal(s, SSL_AD_DECODE_ERROR,
                         SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST,
                         SSL_R_LENGTH_MISMATCH);
                return MSG_PROCESS_ERROR;
            }

            /*
             * Despite this being for certificates, preserve compatibility
             * with pre-TLS 1.3 and use the regular sigalgs field.
             */
            if (!tls1_save_sigalgs(s, &sigalgs, 0)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST,
                         SSL_R_SIGNATURE_ALGORITHMS_ERROR);
                return MSG_PROCESS_ERROR;
            }
            if (!tls1_process_sigalgs(s)) {
                SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                         SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST,
                         ERR_R_MALLOC_FAILURE);
                return MSG_PROCESS_ERROR;
            }
        }

        /* get the CA RDNs */
        if (!parse_ca_names(s, pkt)) {
            /* SSLfatal() already called */
            return MSG_PROCESS_ERROR;
        }
    }

    if (PACKET_remaining(pkt) != 0) {
        SSLfatal(s, SSL_AD_DECODE_ERROR,
                 SSL_F_TLS_PROCESS_CERTIFICATE_REQUEST,
                 SSL_R_LENGTH_MISMATCH);
        return MSG_PROCESS_ERROR;
    }

    /* we should setup a certificate to return.... */
    s->s3->tmp.cert_req = 1;

    /*
     * In TLSv1.3 we don't prepare the client certificate yet. We wait until
     * after the CertificateVerify message has been received. This is because
     * in TLSv1.3 the CertificateRequest arrives before the Certificate message
     * but in TLSv1.2 it is the other way around. We want to make sure that
     * SSL_get_peer_certificate() returns something sensible in
     * client_cert_cb.
     */
    if (SSL_IS_TLS13(s) && s->post_handshake_auth != SSL_PHA_REQUESTED)
        return MSG_PROCESS_CONTINUE_READING;

    return MSG_PROCESS_CONTINUE_PROCESSING;
}