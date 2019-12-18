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
struct s390_aes_ctx {unsigned int key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  fc; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int /*<<< orphan*/  CPACF_KMA_GCM_AES_128 ; 
 int /*<<< orphan*/  CPACF_KMA_GCM_AES_192 ; 
 int /*<<< orphan*/  CPACF_KMA_GCM_AES_256 ; 
 int EINVAL ; 
 struct s390_aes_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int gcm_aes_setkey(struct crypto_aead *tfm, const u8 *key,
			  unsigned int keylen)
{
	struct s390_aes_ctx *ctx = crypto_aead_ctx(tfm);

	switch (keylen) {
	case AES_KEYSIZE_128:
		ctx->fc = CPACF_KMA_GCM_AES_128;
		break;
	case AES_KEYSIZE_192:
		ctx->fc = CPACF_KMA_GCM_AES_192;
		break;
	case AES_KEYSIZE_256:
		ctx->fc = CPACF_KMA_GCM_AES_256;
		break;
	default:
		return -EINVAL;
	}

	memcpy(ctx->key, key, keylen);
	ctx->key_len = keylen;
	return 0;
}