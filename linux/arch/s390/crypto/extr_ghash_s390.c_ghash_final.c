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
typedef  int /*<<< orphan*/  u8 ;
struct shash_desc {int dummy; } ;
struct ghash_desc_ctx {int /*<<< orphan*/  icv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GHASH_BLOCK_SIZE ; 
 int ghash_flush (struct ghash_desc_ctx*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ghash_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int ghash_final(struct shash_desc *desc, u8 *dst)
{
	struct ghash_desc_ctx *dctx = shash_desc_ctx(desc);
	int ret;

	ret = ghash_flush(dctx);
	if (!ret)
		memcpy(dst, dctx->icv, GHASH_BLOCK_SIZE);
	return ret;
}