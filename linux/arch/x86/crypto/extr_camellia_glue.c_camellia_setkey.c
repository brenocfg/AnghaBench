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
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;

/* Variables and functions */
 int __camellia_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int camellia_setkey(struct crypto_tfm *tfm, const u8 *key,
			   unsigned int key_len)
{
	return __camellia_setkey(crypto_tfm_ctx(tfm), key, key_len,
				 &tfm->crt_flags);
}