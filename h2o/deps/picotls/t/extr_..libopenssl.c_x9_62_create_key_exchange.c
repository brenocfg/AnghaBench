#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct st_x9_62_keyex_context_t {int /*<<< orphan*/  super; int /*<<< orphan*/ * privkey; } ;
typedef  int /*<<< orphan*/  ptls_key_exchange_context_t ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ ptls_key_exchange_algorithm_t ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int) ; 
 int PTLS_ERROR_LIBRARY ; 
 int /*<<< orphan*/ * ecdh_gerenate_key (int /*<<< orphan*/ *) ; 
 int x9_62_create_context (TYPE_1__*,struct st_x9_62_keyex_context_t**) ; 
 int /*<<< orphan*/  x9_62_free_context (struct st_x9_62_keyex_context_t*) ; 
 int x9_62_setup_pubkey (struct st_x9_62_keyex_context_t*) ; 

__attribute__((used)) static int x9_62_create_key_exchange(ptls_key_exchange_algorithm_t *algo, ptls_key_exchange_context_t **_ctx)
{
    EC_GROUP *group = NULL;
    struct st_x9_62_keyex_context_t *ctx = NULL;
    int ret;

    /* FIXME use a global? */
    if ((group = EC_GROUP_new_by_curve_name((int)algo->data)) == NULL) {
        ret = PTLS_ERROR_LIBRARY;
        goto Exit;
    }
    if ((ret = x9_62_create_context(algo, &ctx)) != 0)
        goto Exit;
    if ((ctx->privkey = ecdh_gerenate_key(group)) == NULL) {
        ret = PTLS_ERROR_LIBRARY;
        goto Exit;
    }
    if ((ret = x9_62_setup_pubkey(ctx)) != 0)
        goto Exit;
    ret = 0;

Exit:
    if (group != NULL)
        EC_GROUP_free(group);
    if (ret == 0) {
        *_ctx = &ctx->super;
    } else {
        if (ctx != NULL)
            x9_62_free_context(ctx);
        *_ctx = NULL;
    }

    return ret;
}