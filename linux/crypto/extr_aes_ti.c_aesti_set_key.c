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
struct crypto_tfm {int dummy; } ;
struct crypto_aes_ctx {int dummy; } ;

/* Variables and functions */
 int aes_expandkey (struct crypto_aes_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct crypto_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int aesti_set_key(struct crypto_tfm *tfm, const u8 *in_key,
			 unsigned int key_len)
{
	struct crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	return aes_expandkey(ctx, in_key, key_len);
}