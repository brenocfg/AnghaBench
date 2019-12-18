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
struct TYPE_6__ {int error_depth; scalar_t__ parent; int /*<<< orphan*/  chain; TYPE_1__* param; } ;
typedef  TYPE_2__ X509_STORE_CTX ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int X509_V_FLAG_CRL_CHECK ; 
 int X509_V_FLAG_CRL_CHECK_ALL ; 
 int check_cert (TYPE_2__*) ; 
 int sk_X509_num (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_revocation(X509_STORE_CTX *ctx)
{
    int i = 0, last = 0, ok = 0;
    if (!(ctx->param->flags & X509_V_FLAG_CRL_CHECK))
        return 1;
    if (ctx->param->flags & X509_V_FLAG_CRL_CHECK_ALL)
        last = sk_X509_num(ctx->chain) - 1;
    else {
        /* If checking CRL paths this isn't the EE certificate */
        if (ctx->parent)
            return 1;
        last = 0;
    }
    for (i = 0; i <= last; i++) {
        ctx->error_depth = i;
        ok = check_cert(ctx);
        if (!ok)
            return ok;
    }
    return 1;
}