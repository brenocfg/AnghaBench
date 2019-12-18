#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int* arc4; } ;
struct n2_cipher_context {int /*<<< orphan*/  enc_type; TYPE_1__ key; } ;
struct n2_cipher_alg {int /*<<< orphan*/  enc_type; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 struct n2_cipher_context* crypto_tfm_ctx (struct crypto_tfm*) ; 
 struct n2_cipher_alg* n2_cipher_alg (struct crypto_tfm*) ; 

__attribute__((used)) static int n2_arc4_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
			  unsigned int keylen)
{
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct n2_cipher_context *ctx = crypto_tfm_ctx(tfm);
	struct n2_cipher_alg *n2alg = n2_cipher_alg(tfm);
	u8 *s = ctx->key.arc4;
	u8 *x = s + 256;
	u8 *y = x + 1;
	int i, j, k;

	ctx->enc_type = n2alg->enc_type;

	j = k = 0;
	*x = 0;
	*y = 0;
	for (i = 0; i < 256; i++)
		s[i] = i;
	for (i = 0; i < 256; i++) {
		u8 a = s[i];
		j = (j + key[k] + a) & 0xff;
		s[i] = s[j];
		s[j] = a;
		if (++k >= keylen)
			k = 0;
	}

	return 0;
}