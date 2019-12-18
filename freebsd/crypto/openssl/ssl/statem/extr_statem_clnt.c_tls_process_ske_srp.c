#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * B; int /*<<< orphan*/ * s; int /*<<< orphan*/ * g; int /*<<< orphan*/ * N; } ;
struct TYPE_15__ {TYPE_5__* session; TYPE_4__* s3; TYPE_1__ srp_ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  peer; } ;
struct TYPE_12__ {TYPE_2__* new_cipher; } ;
struct TYPE_13__ {TYPE_3__ tmp; } ;
struct TYPE_11__ {int algorithm_auth; } ;
typedef  TYPE_6__ SSL ;
typedef  int /*<<< orphan*/  PACKET ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 void* BN_bin2bn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PACKET_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_AD_DECODE_ERROR ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_PROCESS_SKE_SRP ; 
 int /*<<< orphan*/  SSL_R_LENGTH_MISMATCH ; 
 int SSL_aDSS ; 
 int SSL_aRSA ; 
 int /*<<< orphan*/  SSLfatal (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_verify_server_param (TYPE_6__*) ; 

__attribute__((used)) static int tls_process_ske_srp(SSL *s, PACKET *pkt, EVP_PKEY **pkey)
{
#ifndef OPENSSL_NO_SRP
    PACKET prime, generator, salt, server_pub;

    if (!PACKET_get_length_prefixed_2(pkt, &prime)
        || !PACKET_get_length_prefixed_2(pkt, &generator)
        || !PACKET_get_length_prefixed_1(pkt, &salt)
        || !PACKET_get_length_prefixed_2(pkt, &server_pub)) {
        SSLfatal(s, SSL_AD_DECODE_ERROR, SSL_F_TLS_PROCESS_SKE_SRP,
                 SSL_R_LENGTH_MISMATCH);
        return 0;
    }

    /* TODO(size_t): Convert BN_bin2bn() calls */
    if ((s->srp_ctx.N =
         BN_bin2bn(PACKET_data(&prime),
                   (int)PACKET_remaining(&prime), NULL)) == NULL
        || (s->srp_ctx.g =
            BN_bin2bn(PACKET_data(&generator),
                      (int)PACKET_remaining(&generator), NULL)) == NULL
        || (s->srp_ctx.s =
            BN_bin2bn(PACKET_data(&salt),
                      (int)PACKET_remaining(&salt), NULL)) == NULL
        || (s->srp_ctx.B =
            BN_bin2bn(PACKET_data(&server_pub),
                      (int)PACKET_remaining(&server_pub), NULL)) == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_SRP,
                 ERR_R_BN_LIB);
        return 0;
    }

    if (!srp_verify_server_param(s)) {
        /* SSLfatal() already called */
        return 0;
    }

    /* We must check if there is a certificate */
    if (s->s3->tmp.new_cipher->algorithm_auth & (SSL_aRSA | SSL_aDSS))
        *pkey = X509_get0_pubkey(s->session->peer);

    return 1;
#else
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_PROCESS_SKE_SRP,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}