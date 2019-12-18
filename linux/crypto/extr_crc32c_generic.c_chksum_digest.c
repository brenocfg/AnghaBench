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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct chksum_ctx {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int __chksum_finup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 struct chksum_ctx* crypto_shash_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chksum_digest(struct shash_desc *desc, const u8 *data,
			 unsigned int length, u8 *out)
{
	struct chksum_ctx *mctx = crypto_shash_ctx(desc->tfm);

	return __chksum_finup(&mctx->key, data, length, out);
}