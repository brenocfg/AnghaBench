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
struct cryptd_hash_ctx {int /*<<< orphan*/  refcnt; } ;
struct cryptd_ahash {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct cryptd_hash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_ahash (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void cryptd_free_ahash(struct cryptd_ahash *tfm)
{
	struct cryptd_hash_ctx *ctx = crypto_ahash_ctx(&tfm->base);

	if (refcount_dec_and_test(&ctx->refcnt))
		crypto_free_ahash(&tfm->base);
}