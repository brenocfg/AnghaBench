#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * md_ctx; int /*<<< orphan*/ * o_ctx; int /*<<< orphan*/ * i_ctx; } ;
typedef  TYPE_1__ HMAC_CTX ;

/* Variables and functions */
 void* EVP_MD_CTX_new () ; 

__attribute__((used)) static int hmac_ctx_alloc_mds(HMAC_CTX *ctx)
{
    if (ctx->i_ctx == NULL)
        ctx->i_ctx = EVP_MD_CTX_new();
    if (ctx->i_ctx == NULL)
        return 0;
    if (ctx->o_ctx == NULL)
        ctx->o_ctx = EVP_MD_CTX_new();
    if (ctx->o_ctx == NULL)
        return 0;
    if (ctx->md_ctx == NULL)
        ctx->md_ctx = EVP_MD_CTX_new();
    if (ctx->md_ctx == NULL)
        return 0;
    return 1;
}