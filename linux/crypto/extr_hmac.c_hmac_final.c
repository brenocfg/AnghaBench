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
struct shash_desc {struct crypto_shash* tfm; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 char* crypto_shash_ctx_aligned (struct crypto_shash*) ; 
 int crypto_shash_digestsize (struct crypto_shash*) ; 
 scalar_t__ crypto_shash_final (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int crypto_shash_finup (struct shash_desc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_shash_import (struct shash_desc*,char*) ; 
 int crypto_shash_statesize (struct crypto_shash*) ; 
 struct shash_desc* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int hmac_final(struct shash_desc *pdesc, u8 *out)
{
	struct crypto_shash *parent = pdesc->tfm;
	int ds = crypto_shash_digestsize(parent);
	int ss = crypto_shash_statesize(parent);
	char *opad = crypto_shash_ctx_aligned(parent) + ss;
	struct shash_desc *desc = shash_desc_ctx(pdesc);

	return crypto_shash_final(desc, out) ?:
	       crypto_shash_import(desc, opad) ?:
	       crypto_shash_finup(desc, out, ds, out);
}