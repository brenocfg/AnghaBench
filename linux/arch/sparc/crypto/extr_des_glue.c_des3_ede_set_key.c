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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct des3_ede_sparc64_ctx {int /*<<< orphan*/ * decrypt_expkey; int /*<<< orphan*/ * encrypt_expkey; } ;
struct crypto_tfm {int dummy; } ;
typedef  int /*<<< orphan*/  k3 ;
typedef  int /*<<< orphan*/  k2 ;
typedef  int /*<<< orphan*/  k1 ;

/* Variables and functions */
 int DES_EXPKEY_WORDS ; 
 int /*<<< orphan*/  DES_KEY_SIZE ; 
 int crypto_des3_ede_verify_key (struct crypto_tfm*,int /*<<< orphan*/  const*) ; 
 struct des3_ede_sparc64_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  des_sparc64_key_expand (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  encrypt_to_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int des3_ede_set_key(struct crypto_tfm *tfm, const u8 *key,
			    unsigned int keylen)
{
	struct des3_ede_sparc64_ctx *dctx = crypto_tfm_ctx(tfm);
	u64 k1[DES_EXPKEY_WORDS / 2];
	u64 k2[DES_EXPKEY_WORDS / 2];
	u64 k3[DES_EXPKEY_WORDS / 2];
	int err;

	err = crypto_des3_ede_verify_key(tfm, key);
	if (err)
		return err;

	des_sparc64_key_expand((const u32 *)key, k1);
	key += DES_KEY_SIZE;
	des_sparc64_key_expand((const u32 *)key, k2);
	key += DES_KEY_SIZE;
	des_sparc64_key_expand((const u32 *)key, k3);

	memcpy(&dctx->encrypt_expkey[0], &k1[0], sizeof(k1));
	encrypt_to_decrypt(&dctx->encrypt_expkey[DES_EXPKEY_WORDS / 2], &k2[0]);
	memcpy(&dctx->encrypt_expkey[(DES_EXPKEY_WORDS / 2) * 2],
	       &k3[0], sizeof(k3));

	encrypt_to_decrypt(&dctx->decrypt_expkey[0], &k3[0]);
	memcpy(&dctx->decrypt_expkey[DES_EXPKEY_WORDS / 2],
	       &k2[0], sizeof(k2));
	encrypt_to_decrypt(&dctx->decrypt_expkey[(DES_EXPKEY_WORDS / 2) * 2],
			   &k1[0]);

	return 0;
}