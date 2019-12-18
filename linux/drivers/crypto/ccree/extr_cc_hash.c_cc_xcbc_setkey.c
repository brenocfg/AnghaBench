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
struct device {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct TYPE_2__ {unsigned int keylen; int /*<<< orphan*/  key; int /*<<< orphan*/  key_dma_addr; } ;
struct cc_hash_ctx {int is_hmac; TYPE_1__ key_params; int /*<<< orphan*/  drvdata; scalar_t__ opad_tmp_keys_dma_addr; } ;
struct cc_crypto_req {int dummy; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int /*<<< orphan*/  CC_AES_128_BIT_KEY_SIZE ; 
 int CC_MAX_HASH_SEQ_LEN ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int /*<<< orphan*/  DIN_AES_DOUT ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DRV_CIPHER_ECB ; 
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  S_DIN_to_AES ; 
 scalar_t__ XCBC_MAC_K1_OFFSET ; 
 scalar_t__ XCBC_MAC_K2_OFFSET ; 
 scalar_t__ XCBC_MAC_K3_OFFSET ; 
 int cc_send_sync_request (int /*<<< orphan*/ ,struct cc_crypto_req*,struct cc_hw_desc*,unsigned int) ; 
 struct cc_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_const (struct cc_hw_desc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_xcbc_setkey(struct crypto_ahash *ahash,
			  const u8 *key, unsigned int keylen)
{
	struct cc_crypto_req cc_req = {};
	struct cc_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	struct device *dev = drvdata_to_dev(ctx->drvdata);
	int rc = 0;
	unsigned int idx = 0;
	struct cc_hw_desc desc[CC_MAX_HASH_SEQ_LEN];

	dev_dbg(dev, "===== setkey (%d) ====\n", keylen);

	switch (keylen) {
	case AES_KEYSIZE_128:
	case AES_KEYSIZE_192:
	case AES_KEYSIZE_256:
		break;
	default:
		return -EINVAL;
	}

	ctx->key_params.keylen = keylen;

	ctx->key_params.key = kmemdup(key, keylen, GFP_KERNEL);
	if (!ctx->key_params.key)
		return -ENOMEM;

	ctx->key_params.key_dma_addr =
		dma_map_single(dev, ctx->key_params.key, keylen, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, ctx->key_params.key_dma_addr)) {
		dev_err(dev, "Mapping key va=0x%p len=%u for DMA failed\n",
			key, keylen);
		kzfree(ctx->key_params.key);
		return -ENOMEM;
	}
	dev_dbg(dev, "mapping key-buffer: key_dma_addr=%pad keylen=%u\n",
		&ctx->key_params.key_dma_addr, ctx->key_params.keylen);

	ctx->is_hmac = true;
	/* 1. Load the AES key */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, ctx->key_params.key_dma_addr,
		     keylen, NS_BIT);
	set_cipher_mode(&desc[idx], DRV_CIPHER_ECB);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_DIRECTION_ENCRYPT);
	set_key_size_aes(&desc[idx], keylen);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_const(&desc[idx], 0x01010101, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	set_dout_dlli(&desc[idx],
		      (ctx->opad_tmp_keys_dma_addr + XCBC_MAC_K1_OFFSET),
		      CC_AES_128_BIT_KEY_SIZE, NS_BIT, 0);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_const(&desc[idx], 0x02020202, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	set_dout_dlli(&desc[idx],
		      (ctx->opad_tmp_keys_dma_addr + XCBC_MAC_K2_OFFSET),
		      CC_AES_128_BIT_KEY_SIZE, NS_BIT, 0);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_const(&desc[idx], 0x03030303, CC_AES_128_BIT_KEY_SIZE);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	set_dout_dlli(&desc[idx],
		      (ctx->opad_tmp_keys_dma_addr + XCBC_MAC_K3_OFFSET),
		      CC_AES_128_BIT_KEY_SIZE, NS_BIT, 0);
	idx++;

	rc = cc_send_sync_request(ctx->drvdata, &cc_req, desc, idx);

	if (rc)
		crypto_ahash_set_flags(ahash, CRYPTO_TFM_RES_BAD_KEY_LEN);

	dma_unmap_single(dev, ctx->key_params.key_dma_addr,
			 ctx->key_params.keylen, DMA_TO_DEVICE);
	dev_dbg(dev, "Unmapped key-buffer: key_dma_addr=%pad keylen=%u\n",
		&ctx->key_params.key_dma_addr, ctx->key_params.keylen);

	kzfree(ctx->key_params.key);

	return rc;
}