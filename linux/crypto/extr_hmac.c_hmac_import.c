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
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct hmac_ctx {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int crypto_shash_import (struct shash_desc*,void const*) ; 
 struct hmac_ctx* hmac_ctx (int /*<<< orphan*/ ) ; 
 struct shash_desc* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int hmac_import(struct shash_desc *pdesc, const void *in)
{
	struct shash_desc *desc = shash_desc_ctx(pdesc);
	struct hmac_ctx *ctx = hmac_ctx(pdesc->tfm);

	desc->tfm = ctx->hash;

	return crypto_shash_import(desc, in);
}