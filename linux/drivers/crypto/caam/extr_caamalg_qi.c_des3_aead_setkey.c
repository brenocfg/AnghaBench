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
struct crypto_authenc_keys {int /*<<< orphan*/  enckeylen; int /*<<< orphan*/  enckey; } ;
struct crypto_aead {int dummy; } ;
typedef  int /*<<< orphan*/  keys ;

/* Variables and functions */
 int aead_setkey (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int) ; 
 int crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_authenc_keys*,int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ verify_aead_des3_key (struct crypto_aead*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int des3_aead_setkey(struct crypto_aead *aead, const u8 *key,
			    unsigned int keylen)
{
	struct crypto_authenc_keys keys;
	int err;

	err = crypto_authenc_extractkeys(&keys, key, keylen);
	if (unlikely(err))
		return err;

	err = verify_aead_des3_key(aead, keys.enckey, keys.enckeylen) ?:
	      aead_setkey(aead, key, keylen);

	memzero_explicit(&keys, sizeof(keys));
	return err;
}