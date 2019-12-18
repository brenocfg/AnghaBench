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
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int stm32_cryp_setkey (struct crypto_ablkcipher*,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ verify_ablkcipher_des3_key (struct crypto_ablkcipher*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int stm32_cryp_tdes_setkey(struct crypto_ablkcipher *tfm, const u8 *key,
				  unsigned int keylen)
{
	return verify_ablkcipher_des3_key(tfm, key) ?:
	       stm32_cryp_setkey(tfm, key, keylen);
}