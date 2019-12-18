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
struct xxhash64_tfm_ctx {int /*<<< orphan*/  seed; } ;
struct xxhash64_desc_ctx {int /*<<< orphan*/  xxhstate; } ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 struct xxhash64_tfm_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 
 struct xxhash64_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 
 int /*<<< orphan*/  xxh64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xxhash64_init(struct shash_desc *desc)
{
	struct xxhash64_tfm_ctx *tctx = crypto_shash_ctx(desc->tfm);
	struct xxhash64_desc_ctx *dctx = shash_desc_ctx(desc);

	xxh64_reset(&dctx->xxhstate, tctx->seed);

	return 0;
}