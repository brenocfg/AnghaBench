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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct iproc_ctx_s {int max_payload; int /*<<< orphan*/  cipher_type; TYPE_1__ cipher; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 scalar_t__ CIPHER_MODE_XTS ; 
 int /*<<< orphan*/  CIPHER_TYPE_AES128 ; 
 int /*<<< orphan*/  CIPHER_TYPE_AES192 ; 
 int /*<<< orphan*/  CIPHER_TYPE_AES256 ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int SPU_MAX_PAYLOAD_INF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct iproc_ctx_s* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 int /*<<< orphan*/  crypto_ablkcipher_set_flags (struct crypto_ablkcipher*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aes_setkey(struct crypto_ablkcipher *cipher, const u8 *key,
		      unsigned int keylen)
{
	struct iproc_ctx_s *ctx = crypto_ablkcipher_ctx(cipher);

	if (ctx->cipher.mode == CIPHER_MODE_XTS)
		/* XTS includes two keys of equal length */
		keylen = keylen / 2;

	switch (keylen) {
	case AES_KEYSIZE_128:
		ctx->cipher_type = CIPHER_TYPE_AES128;
		break;
	case AES_KEYSIZE_192:
		ctx->cipher_type = CIPHER_TYPE_AES192;
		break;
	case AES_KEYSIZE_256:
		ctx->cipher_type = CIPHER_TYPE_AES256;
		break;
	default:
		crypto_ablkcipher_set_flags(cipher, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	WARN_ON((ctx->max_payload != SPU_MAX_PAYLOAD_INF) &&
		((ctx->max_payload % AES_BLOCK_SIZE) != 0));
	return 0;
}