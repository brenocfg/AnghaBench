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
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ALGO_SHA256 ; 
 int hash_setkey (struct crypto_ahash*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hmac_sha256_setkey(struct crypto_ahash *tfm,
			      const u8 *key, unsigned int keylen)
{
	return hash_setkey(tfm, key, keylen, HASH_ALGO_SHA256);
}