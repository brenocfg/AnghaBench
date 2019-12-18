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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DES3_ECB ; 
 int cvm_setkey (struct crypto_ablkcipher*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ verify_ablkcipher_des3_key (struct crypto_ablkcipher*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int cvm_ecb_des3_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
			       u32 keylen)
{
	return verify_ablkcipher_des3_key(cipher, key) ?:
	       cvm_setkey(cipher, key, keylen, DES3_ECB);
}