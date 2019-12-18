#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ err_stack; int /*<<< orphan*/  used; int /*<<< orphan*/  stack; scalar_t__ too_many; } ;
typedef  TYPE_1__ BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_CTX_START ; 
 int /*<<< orphan*/  BN_R_TOO_MANY_TEMPORARY_VARIABLES ; 
 int /*<<< orphan*/  BN_STACK_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTXDBG_ENTRY (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  CTXDBG_EXIT (TYPE_1__*) ; 

void BN_CTX_start(BN_CTX *ctx)
{
    CTXDBG_ENTRY("BN_CTX_start", ctx);
    /* If we're already overflowing ... */
    if (ctx->err_stack || ctx->too_many)
        ctx->err_stack++;
    /* (Try to) get a new frame pointer */
    else if (!BN_STACK_push(&ctx->stack, ctx->used)) {
        BNerr(BN_F_BN_CTX_START, BN_R_TOO_MANY_TEMPORARY_VARIABLES);
        ctx->err_stack++;
    }
    CTXDBG_EXIT(ctx);
}