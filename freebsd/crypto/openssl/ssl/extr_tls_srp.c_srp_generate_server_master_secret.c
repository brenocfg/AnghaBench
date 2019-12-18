#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  N; int /*<<< orphan*/  b; int /*<<< orphan*/  v; int /*<<< orphan*/  A; int /*<<< orphan*/  B; } ;
struct TYPE_7__ {TYPE_1__ srp_ctx; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/ * SRP_Calc_server_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SRP_Calc_u (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_Verify_A_mod_N (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_SRP_GENERATE_SERVER_MASTER_SECRET ; 
 int /*<<< orphan*/  SSLfatal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssl_generate_master_secret (TYPE_2__*,unsigned char*,int,int) ; 

int srp_generate_server_master_secret(SSL *s)
{
    BIGNUM *K = NULL, *u = NULL;
    int ret = -1, tmp_len = 0;
    unsigned char *tmp = NULL;

    if (!SRP_Verify_A_mod_N(s->srp_ctx.A, s->srp_ctx.N))
        goto err;
    if ((u = SRP_Calc_u(s->srp_ctx.A, s->srp_ctx.B, s->srp_ctx.N)) == NULL)
        goto err;
    if ((K = SRP_Calc_server_key(s->srp_ctx.A, s->srp_ctx.v, u, s->srp_ctx.b,
                                 s->srp_ctx.N)) == NULL)
        goto err;

    tmp_len = BN_num_bytes(K);
    if ((tmp = OPENSSL_malloc(tmp_len)) == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR,
                 SSL_F_SRP_GENERATE_SERVER_MASTER_SECRET, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    BN_bn2bin(K, tmp);
    /* Calls SSLfatal() as required */
    ret = ssl_generate_master_secret(s, tmp, tmp_len, 1);
 err:
    BN_clear_free(K);
    BN_clear_free(u);
    return ret;
}