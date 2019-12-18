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
 int /*<<< orphan*/  ICP_QAT_HW_CIPHER_XTS_MODE ; 
 int qat_alg_ablkcipher_setkey (struct crypto_ablkcipher*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_alg_ablkcipher_xts_setkey(struct crypto_ablkcipher *tfm,
					 const u8 *key, unsigned int keylen)
{
	return qat_alg_ablkcipher_setkey(tfm, key, keylen,
					 ICP_QAT_HW_CIPHER_XTS_MODE);
}