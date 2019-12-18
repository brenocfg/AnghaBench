#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * v; int /*<<< orphan*/ * b; int /*<<< orphan*/ * a; int /*<<< orphan*/ * A; int /*<<< orphan*/ * B; int /*<<< orphan*/ * s; int /*<<< orphan*/ * g; int /*<<< orphan*/ * N; int /*<<< orphan*/ * info; int /*<<< orphan*/ * login; int /*<<< orphan*/  srp_Mask; int /*<<< orphan*/  strength; int /*<<< orphan*/  SRP_give_srp_client_pwd_callback; int /*<<< orphan*/  SRP_verify_param_callback; int /*<<< orphan*/  TLS_ext_srp_username_callback; int /*<<< orphan*/  SRP_cb_arg; } ;
struct ssl_st {TYPE_3__ srp_ctx; TYPE_2__* ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  srp_Mask; int /*<<< orphan*/ * info; int /*<<< orphan*/ * login; int /*<<< orphan*/ * b; int /*<<< orphan*/ * v; int /*<<< orphan*/ * a; int /*<<< orphan*/ * A; int /*<<< orphan*/ * B; int /*<<< orphan*/ * s; int /*<<< orphan*/ * g; int /*<<< orphan*/ * N; int /*<<< orphan*/  strength; int /*<<< orphan*/  SRP_give_srp_client_pwd_callback; int /*<<< orphan*/  SRP_verify_param_callback; int /*<<< orphan*/  TLS_ext_srp_username_callback; int /*<<< orphan*/  SRP_cb_arg; } ;
struct TYPE_5__ {TYPE_1__ srp_ctx; } ;
typedef  TYPE_2__ SSL_CTX ;

/* Variables and functions */
 void* BN_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BUF_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_F_SSL_SRP_CTX_INIT ; 
 int /*<<< orphan*/  SSLerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

int SSL_SRP_CTX_init(struct ssl_st *s)
{
    SSL_CTX *ctx;

    if ((s == NULL) || ((ctx = s->ctx) == NULL))
        return 0;

    memset(&s->srp_ctx, 0, sizeof(s->srp_ctx));

    s->srp_ctx.SRP_cb_arg = ctx->srp_ctx.SRP_cb_arg;
    /* set client Hello login callback */
    s->srp_ctx.TLS_ext_srp_username_callback =
        ctx->srp_ctx.TLS_ext_srp_username_callback;
    /* set SRP N/g param callback for verification */
    s->srp_ctx.SRP_verify_param_callback =
        ctx->srp_ctx.SRP_verify_param_callback;
    /* set SRP client passwd callback */
    s->srp_ctx.SRP_give_srp_client_pwd_callback =
        ctx->srp_ctx.SRP_give_srp_client_pwd_callback;

    s->srp_ctx.strength = ctx->srp_ctx.strength;

    if (((ctx->srp_ctx.N != NULL) &&
         ((s->srp_ctx.N = BN_dup(ctx->srp_ctx.N)) == NULL)) ||
        ((ctx->srp_ctx.g != NULL) &&
         ((s->srp_ctx.g = BN_dup(ctx->srp_ctx.g)) == NULL)) ||
        ((ctx->srp_ctx.s != NULL) &&
         ((s->srp_ctx.s = BN_dup(ctx->srp_ctx.s)) == NULL)) ||
        ((ctx->srp_ctx.B != NULL) &&
         ((s->srp_ctx.B = BN_dup(ctx->srp_ctx.B)) == NULL)) ||
        ((ctx->srp_ctx.A != NULL) &&
         ((s->srp_ctx.A = BN_dup(ctx->srp_ctx.A)) == NULL)) ||
        ((ctx->srp_ctx.a != NULL) &&
         ((s->srp_ctx.a = BN_dup(ctx->srp_ctx.a)) == NULL)) ||
        ((ctx->srp_ctx.v != NULL) &&
         ((s->srp_ctx.v = BN_dup(ctx->srp_ctx.v)) == NULL)) ||
        ((ctx->srp_ctx.b != NULL) &&
         ((s->srp_ctx.b = BN_dup(ctx->srp_ctx.b)) == NULL))) {
        SSLerr(SSL_F_SSL_SRP_CTX_INIT, ERR_R_BN_LIB);
        goto err;
    }
    if ((ctx->srp_ctx.login != NULL) &&
        ((s->srp_ctx.login = OPENSSL_strdup(ctx->srp_ctx.login)) == NULL)) {
        SSLerr(SSL_F_SSL_SRP_CTX_INIT, ERR_R_INTERNAL_ERROR);
        goto err;
    }
    if ((ctx->srp_ctx.info != NULL) &&
        ((s->srp_ctx.info = BUF_strdup(ctx->srp_ctx.info)) == NULL)) {
        SSLerr(SSL_F_SSL_SRP_CTX_INIT, ERR_R_INTERNAL_ERROR);
        goto err;
    }
    s->srp_ctx.srp_Mask = ctx->srp_ctx.srp_Mask;

    return 1;
 err:
    OPENSSL_free(s->srp_ctx.login);
    OPENSSL_free(s->srp_ctx.info);
    BN_free(s->srp_ctx.N);
    BN_free(s->srp_ctx.g);
    BN_free(s->srp_ctx.s);
    BN_free(s->srp_ctx.B);
    BN_free(s->srp_ctx.A);
    BN_free(s->srp_ctx.a);
    BN_free(s->srp_ctx.b);
    BN_free(s->srp_ctx.v);
    memset(&s->srp_ctx, 0, sizeof(s->srp_ctx));
    return 0;
}