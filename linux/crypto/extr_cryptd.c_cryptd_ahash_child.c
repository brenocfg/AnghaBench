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
struct crypto_shash {int dummy; } ;
struct cryptd_hash_ctx {struct crypto_shash* child; } ;
struct cryptd_ahash {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct cryptd_hash_ctx* crypto_ahash_ctx (int /*<<< orphan*/ *) ; 

struct crypto_shash *cryptd_ahash_child(struct cryptd_ahash *tfm)
{
	struct cryptd_hash_ctx *ctx = crypto_ahash_ctx(&tfm->base);

	return ctx->child;
}