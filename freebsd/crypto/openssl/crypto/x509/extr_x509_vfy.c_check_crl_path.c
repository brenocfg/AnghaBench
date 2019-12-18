#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  chain; int /*<<< orphan*/  verify_cb; struct TYPE_8__* parent; int /*<<< orphan*/  param; int /*<<< orphan*/  crls; int /*<<< orphan*/  untrusted; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ X509_STORE_CTX ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  X509_STORE_CTX_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_STORE_CTX_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_CTX_set0_param (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int X509_verify_cert (TYPE_1__*) ; 
 int check_crl_chain (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_crl_path(X509_STORE_CTX *ctx, X509 *x)
{
    X509_STORE_CTX crl_ctx;
    int ret;

    /* Don't allow recursive CRL path validation */
    if (ctx->parent)
        return 0;
    if (!X509_STORE_CTX_init(&crl_ctx, ctx->ctx, x, ctx->untrusted))
        return -1;

    crl_ctx.crls = ctx->crls;
    /* Copy verify params across */
    X509_STORE_CTX_set0_param(&crl_ctx, ctx->param);

    crl_ctx.parent = ctx;
    crl_ctx.verify_cb = ctx->verify_cb;

    /* Verify CRL issuer */
    ret = X509_verify_cert(&crl_ctx);
    if (ret <= 0)
        goto err;

    /* Check chain is acceptable */
    ret = check_crl_chain(ctx, ctx->chain, crl_ctx.chain);
 err:
    X509_STORE_CTX_cleanup(&crl_ctx);
    return ret;
}