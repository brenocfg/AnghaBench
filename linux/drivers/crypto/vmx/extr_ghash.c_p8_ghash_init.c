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
struct shash_desc {int dummy; } ;
struct p8_ghash_desc_ctx {int /*<<< orphan*/  shash; scalar_t__ bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GHASH_DIGEST_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct p8_ghash_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int p8_ghash_init(struct shash_desc *desc)
{
	struct p8_ghash_desc_ctx *dctx = shash_desc_ctx(desc);

	dctx->bytes = 0;
	memset(dctx->shash, 0, GHASH_DIGEST_SIZE);
	return 0;
}