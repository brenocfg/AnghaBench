#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct st_x9_62_keyex_context_t* base; } ;
struct TYPE_4__ {TYPE_1__ pubkey; } ;
struct st_x9_62_keyex_context_t {int /*<<< orphan*/ * bn_ctx; int /*<<< orphan*/ * privkey; TYPE_2__ super; } ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct st_x9_62_keyex_context_t*) ; 

__attribute__((used)) static void x9_62_free_context(struct st_x9_62_keyex_context_t *ctx)
{
    free(ctx->super.pubkey.base);
    if (ctx->privkey != NULL)
        EC_KEY_free(ctx->privkey);
    if (ctx->bn_ctx != NULL)
        BN_CTX_free(ctx->bn_ctx);
    free(ctx);
}