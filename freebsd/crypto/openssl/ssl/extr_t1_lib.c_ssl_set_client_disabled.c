#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int srp_Mask; } ;
struct TYPE_11__ {TYPE_3__* s3; TYPE_1__ srp_ctx; int /*<<< orphan*/  psk_client_callback; } ;
struct TYPE_9__ {int mask_k; int /*<<< orphan*/  mask_a; int /*<<< orphan*/  max_ver; int /*<<< orphan*/  min_ver; } ;
struct TYPE_10__ {TYPE_2__ tmp; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int SSL_PSK ; 
 int /*<<< orphan*/  SSL_SECOP_SIGALG_MASK ; 
 int /*<<< orphan*/  SSL_aPSK ; 
 int /*<<< orphan*/  SSL_aSRP ; 
 int SSL_kSRP ; 
 scalar_t__ ssl_get_min_max_version (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_set_sig_mask (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 

int ssl_set_client_disabled(SSL *s)
{
    s->s3->tmp.mask_a = 0;
    s->s3->tmp.mask_k = 0;
    ssl_set_sig_mask(&s->s3->tmp.mask_a, s, SSL_SECOP_SIGALG_MASK);
    if (ssl_get_min_max_version(s, &s->s3->tmp.min_ver,
                                &s->s3->tmp.max_ver, NULL) != 0)
        return 0;
#ifndef OPENSSL_NO_PSK
    /* with PSK there must be client callback set */
    if (!s->psk_client_callback) {
        s->s3->tmp.mask_a |= SSL_aPSK;
        s->s3->tmp.mask_k |= SSL_PSK;
    }
#endif                          /* OPENSSL_NO_PSK */
#ifndef OPENSSL_NO_SRP
    if (!(s->srp_ctx.srp_Mask & SSL_kSRP)) {
        s->s3->tmp.mask_a |= SSL_aSRP;
        s->s3->tmp.mask_k |= SSL_kSRP;
    }
#endif
    return 1;
}