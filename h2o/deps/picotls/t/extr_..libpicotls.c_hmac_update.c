#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_picotls_hmac_context_t {TYPE_1__* hash; } ;
typedef  int /*<<< orphan*/  ptls_hash_context_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* update ) (TYPE_1__*,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,void const*,size_t) ; 

__attribute__((used)) static void hmac_update(ptls_hash_context_t *_ctx, const void *src, size_t len)
{
    struct st_picotls_hmac_context_t *ctx = (struct st_picotls_hmac_context_t *)_ctx;
    ctx->hash->update(ctx->hash, src, len);
}