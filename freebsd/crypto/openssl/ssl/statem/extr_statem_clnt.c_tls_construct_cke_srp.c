#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPACKET ;
struct TYPE_6__ {int /*<<< orphan*/  login; int /*<<< orphan*/ * A; } ;
struct TYPE_8__ {TYPE_2__* session; TYPE_1__ srp_ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/ * srp_username; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS_CONSTRUCT_CKE_SRP ; 
 int /*<<< orphan*/  SSLfatal (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPACKET_sub_allocate_bytes_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char**) ; 

__attribute__((used)) static int tls_construct_cke_srp(SSL *s, WPACKET *pkt)
{
#ifndef OPENSSL_NO_SRP
    unsigned char *abytes = NULL;

    if (s->srp_ctx.A == NULL
            || !WPACKET_sub_allocate_bytes_u16(pkt, BN_num_bytes(s->srp_ctx.A),
                                               &abytes)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_SRP,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }
    BN_bn2bin(s->srp_ctx.A, abytes);

    OPENSSL_free(s->session->srp_username);
    s->session->srp_username = OPENSSL_strdup(s->srp_ctx.login);
    if (s->session->srp_username == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_SRP,
                 ERR_R_MALLOC_FAILURE);
        return 0;
    }

    return 1;
#else
    SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS_CONSTRUCT_CKE_SRP,
             ERR_R_INTERNAL_ERROR);
    return 0;
#endif
}