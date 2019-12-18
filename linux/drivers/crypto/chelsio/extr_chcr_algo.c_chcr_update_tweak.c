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
struct crypto_aes_ctx {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct chcr_blkcipher_req_ctx {int last_req_len; int /*<<< orphan*/  iv; } ;
struct ablkcipher_request {int dummy; } ;
struct ablk_ctx {int enckey_len; int /*<<< orphan*/ * key; } ;
typedef  int /*<<< orphan*/  le128 ;
typedef  int /*<<< orphan*/  aes ;

/* Variables and functions */
 struct ablk_ctx* ABLK_CTX (int /*<<< orphan*/ ) ; 
 int AES_BLOCK_SIZE ; 
 struct chcr_blkcipher_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  aes_decrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aes_encrypt (struct crypto_aes_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int aes_expandkey (struct crypto_aes_ctx*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  c_ctx (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  gf128mul_x8_ble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gf128mul_x_ble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_aes_ctx*,int) ; 

__attribute__((used)) static int chcr_update_tweak(struct ablkcipher_request *req, u8 *iv,
			     u32 isfinal)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct ablk_ctx *ablkctx = ABLK_CTX(c_ctx(tfm));
	struct chcr_blkcipher_req_ctx *reqctx = ablkcipher_request_ctx(req);
	struct crypto_aes_ctx aes;
	int ret, i;
	u8 *key;
	unsigned int keylen;
	int round = reqctx->last_req_len / AES_BLOCK_SIZE;
	int round8 = round / 8;

	memcpy(iv, reqctx->iv, AES_BLOCK_SIZE);

	keylen = ablkctx->enckey_len / 2;
	key = ablkctx->key + keylen;
	ret = aes_expandkey(&aes, key, keylen);
	if (ret)
		return ret;
	aes_encrypt(&aes, iv, iv);
	for (i = 0; i < round8; i++)
		gf128mul_x8_ble((le128 *)iv, (le128 *)iv);

	for (i = 0; i < (round % 8); i++)
		gf128mul_x_ble((le128 *)iv, (le128 *)iv);

	if (!isfinal)
		aes_decrypt(&aes, iv, iv);

	memzero_explicit(&aes, sizeof(aes));
	return 0;
}