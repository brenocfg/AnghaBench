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
typedef  scalar_t__ u32 ;
struct rk_crypto_info {scalar_t__ reg; int /*<<< orphan*/  async_req; } ;
struct rk_cipher_ctx {int mode; scalar_t__ keylen; } ;
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;
struct ablkcipher_request {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 scalar_t__ AES_KEYSIZE_192 ; 
 scalar_t__ AES_KEYSIZE_256 ; 
 int /*<<< orphan*/  CRYPTO_WRITE (struct rk_crypto_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ DES_BLOCK_SIZE ; 
 int RK_CRYPTO_AES_192BIT_key ; 
 int RK_CRYPTO_AES_256BIT_key ; 
 int RK_CRYPTO_AES_BYTESWAP_IV ; 
 int RK_CRYPTO_AES_BYTESWAP_KEY ; 
 int /*<<< orphan*/  RK_CRYPTO_AES_CTRL ; 
 int RK_CRYPTO_AES_FIFO_MODE ; 
 scalar_t__ RK_CRYPTO_AES_IV_0 ; 
 int RK_CRYPTO_AES_KEY_CHANGE ; 
 scalar_t__ RK_CRYPTO_BCDMA_DONE_ENA ; 
 scalar_t__ RK_CRYPTO_BCDMA_ERR_ENA ; 
 scalar_t__ RK_CRYPTO_BYTESWAP_BRFIFO ; 
 scalar_t__ RK_CRYPTO_BYTESWAP_BTFIFO ; 
 int /*<<< orphan*/  RK_CRYPTO_CONF ; 
 scalar_t__ RK_CRYPTO_DESSEL ; 
 int /*<<< orphan*/  RK_CRYPTO_INTENA ; 
 int RK_CRYPTO_TDES_BYTESWAP_IV ; 
 int RK_CRYPTO_TDES_BYTESWAP_KEY ; 
 int /*<<< orphan*/  RK_CRYPTO_TDES_CTRL ; 
 int RK_CRYPTO_TDES_FIFO_MODE ; 
 scalar_t__ RK_CRYPTO_TDES_IV_0 ; 
 struct ablkcipher_request* ablkcipher_request_cast (int /*<<< orphan*/ ) ; 
 struct rk_cipher_ctx* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 
 scalar_t__ crypto_ablkcipher_ivsize (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 struct crypto_tfm* crypto_ablkcipher_tfm (struct crypto_ablkcipher*) ; 
 scalar_t__ crypto_tfm_alg_blocksize (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rk_ablk_hw_init(struct rk_crypto_info *dev)
{
	struct ablkcipher_request *req =
		ablkcipher_request_cast(dev->async_req);
	struct crypto_ablkcipher *cipher = crypto_ablkcipher_reqtfm(req);
	struct crypto_tfm *tfm = crypto_ablkcipher_tfm(cipher);
	struct rk_cipher_ctx *ctx = crypto_ablkcipher_ctx(cipher);
	u32 ivsize, block, conf_reg = 0;

	block = crypto_tfm_alg_blocksize(tfm);
	ivsize = crypto_ablkcipher_ivsize(cipher);

	if (block == DES_BLOCK_SIZE) {
		ctx->mode |= RK_CRYPTO_TDES_FIFO_MODE |
			     RK_CRYPTO_TDES_BYTESWAP_KEY |
			     RK_CRYPTO_TDES_BYTESWAP_IV;
		CRYPTO_WRITE(dev, RK_CRYPTO_TDES_CTRL, ctx->mode);
		memcpy_toio(dev->reg + RK_CRYPTO_TDES_IV_0, req->info, ivsize);
		conf_reg = RK_CRYPTO_DESSEL;
	} else {
		ctx->mode |= RK_CRYPTO_AES_FIFO_MODE |
			     RK_CRYPTO_AES_KEY_CHANGE |
			     RK_CRYPTO_AES_BYTESWAP_KEY |
			     RK_CRYPTO_AES_BYTESWAP_IV;
		if (ctx->keylen == AES_KEYSIZE_192)
			ctx->mode |= RK_CRYPTO_AES_192BIT_key;
		else if (ctx->keylen == AES_KEYSIZE_256)
			ctx->mode |= RK_CRYPTO_AES_256BIT_key;
		CRYPTO_WRITE(dev, RK_CRYPTO_AES_CTRL, ctx->mode);
		memcpy_toio(dev->reg + RK_CRYPTO_AES_IV_0, req->info, ivsize);
	}
	conf_reg |= RK_CRYPTO_BYTESWAP_BTFIFO |
		    RK_CRYPTO_BYTESWAP_BRFIFO;
	CRYPTO_WRITE(dev, RK_CRYPTO_CONF, conf_reg);
	CRYPTO_WRITE(dev, RK_CRYPTO_INTENA,
		     RK_CRYPTO_BCDMA_ERR_ENA | RK_CRYPTO_BCDMA_DONE_ENA);
}