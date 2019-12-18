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
 int nitrox_skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ verify_skcipher_des3_key (struct crypto_skcipher*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int nitrox_3des_setkey(struct crypto_skcipher *cipher,
			      const u8 *key, unsigned int keylen)
{
	return verify_skcipher_des3_key(cipher, key) ?:
	       nitrox_skcipher_setkey(cipher, 0, key, keylen);
}