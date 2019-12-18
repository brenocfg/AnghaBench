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
struct crypto_skcipher {int dummy; } ;
struct arc4_ctx {int dummy; } ;

/* Variables and functions */
 int arc4_setkey (struct arc4_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct arc4_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static int crypto_arc4_setkey(struct crypto_skcipher *tfm, const u8 *in_key,
			      unsigned int key_len)
{
	struct arc4_ctx *ctx = crypto_skcipher_ctx(tfm);

	return arc4_setkey(ctx, in_key, key_len);
}