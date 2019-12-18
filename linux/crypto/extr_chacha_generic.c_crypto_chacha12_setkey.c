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

/* Variables and functions */
 int chacha_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,unsigned int,int) ; 

int crypto_chacha12_setkey(struct crypto_skcipher *tfm, const u8 *key,
			   unsigned int keysize)
{
	return chacha_setkey(tfm, key, keysize, 12);
}