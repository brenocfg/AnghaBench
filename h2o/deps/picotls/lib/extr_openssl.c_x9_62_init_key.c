#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct st_x9_62_keyex_context_t {int /*<<< orphan*/  super; int /*<<< orphan*/ * privkey; } ;
typedef  int /*<<< orphan*/  ptls_key_exchange_context_t ;
typedef  int /*<<< orphan*/  ptls_key_exchange_algorithm_t ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int x9_62_create_context (int /*<<< orphan*/ *,struct st_x9_62_keyex_context_t**) ; 
 int /*<<< orphan*/  x9_62_free_context (struct st_x9_62_keyex_context_t*) ; 
 int x9_62_setup_pubkey (struct st_x9_62_keyex_context_t*) ; 

__attribute__((used)) static int x9_62_init_key(ptls_key_exchange_algorithm_t *algo, ptls_key_exchange_context_t **_ctx, EC_KEY *eckey)
{
    struct st_x9_62_keyex_context_t *ctx = NULL;
    int ret;

    if ((ret = x9_62_create_context(algo, &ctx)) != 0)
        goto Exit;
    ctx->privkey = eckey;
    if ((ret = x9_62_setup_pubkey(ctx)) != 0)
        goto Exit;
    ret = 0;

Exit:
    if (ret == 0) {
        *_ctx = &ctx->super;
    } else {
        if (ctx != NULL)
            x9_62_free_context(ctx);
        *_ctx = NULL;
    }
    return ret;
}