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
struct iproc_ctx_s {int /*<<< orphan*/  cipher_type; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIPHER_TYPE_DES ; 
 struct iproc_ctx_s* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int verify_ablkcipher_des_key (struct crypto_ablkcipher*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int des_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
		      unsigned int keylen)
{
	struct iproc_ctx_s *ctx = crypto_ablkcipher_ctx(cipher);
	int err;

	err = verify_ablkcipher_des_key(cipher, key);
	if (err)
		return err;

	ctx->cipher_type = CIPHER_TYPE_DES;
	return 0;
}