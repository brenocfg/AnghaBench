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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct padlock_sha_desc {TYPE_1__ fallback; } ;
struct padlock_sha_ctx {int /*<<< orphan*/  fallback; } ;

/* Variables and functions */
 struct padlock_sha_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 int crypto_shash_init (TYPE_1__*) ; 
 struct padlock_sha_desc* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int padlock_sha_init(struct shash_desc *desc)
{
	struct padlock_sha_desc *dctx = shash_desc_ctx(desc);
	struct padlock_sha_ctx *ctx = crypto_shash_ctx(desc->tfm);

	dctx->fallback.tfm = ctx->fallback;
	return crypto_shash_init(&dctx->fallback);
}