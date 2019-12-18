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
struct crypto_aead {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_aead_ctx {int enc_keylen; int authsize; int /*<<< orphan*/  drvdata; int /*<<< orphan*/  enckey_dma_addr; } ;
struct aead_request {int dummy; } ;
struct TYPE_2__ {scalar_t__ op_type; int /*<<< orphan*/  iv_dma_addr; } ;
struct aead_req_ctx {scalar_t__ assoclen; int ccm_hdr_size; int /*<<< orphan*/  mac_buf_dma_addr; int /*<<< orphan*/  ccm_iv0_dma_addr; scalar_t__ cryptlen; int /*<<< orphan*/  ccm_adata_sg; TYPE_1__ gen_ctx; int /*<<< orphan*/  icv_dma_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 unsigned int AES_and_HASH ; 
 unsigned int AES_to_HASH_and_DOUT ; 
 int CC_AES_KEY_SIZE_MAX ; 
 int /*<<< orphan*/  DESC_DIRECTION_ENCRYPT_ENCRYPT ; 
 int /*<<< orphan*/  DIN_AES_DOUT ; 
 int /*<<< orphan*/  DIN_HASH ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DRV_CIPHER_CBC_MAC ; 
 int /*<<< orphan*/  DRV_CIPHER_CTR ; 
 scalar_t__ DRV_CRYPTO_DIRECTION_DECRYPT ; 
 int /*<<< orphan*/  DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int /*<<< orphan*/  HASH_DIGEST_RESULT_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE1 ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE0 ; 
 int /*<<< orphan*/  S_DIN_to_AES ; 
 int /*<<< orphan*/  S_DIN_to_HASH ; 
 int /*<<< orphan*/  S_HASH_to_DOUT ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  cc_proc_cipher_desc (struct aead_request*,unsigned int,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_set_assoc_desc (struct aead_request*,int /*<<< orphan*/ ,struct cc_hw_desc*,unsigned int*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_aes_not_hash_mode (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dout_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,int) ; 
 int /*<<< orphan*/  set_queue_last_ind (int /*<<< orphan*/ ,struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cc_ccm(struct aead_request *req, struct cc_hw_desc desc[],
		  unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int idx = *seq_size;
	unsigned int cipher_flow_mode;
	dma_addr_t mac_result;

	if (req_ctx->gen_ctx.op_type == DRV_CRYPTO_DIRECTION_DECRYPT) {
		cipher_flow_mode = AES_to_HASH_and_DOUT;
		mac_result = req_ctx->mac_buf_dma_addr;
	} else { /* Encrypt */
		cipher_flow_mode = AES_and_HASH;
		mac_result = req_ctx->icv_dma_addr;
	}

	/* load key */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CTR);
	set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
		     ((ctx->enc_keylen == 24) ?  CC_AES_KEY_SIZE_MAX :
		      ctx->enc_keylen), NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_cipher_config0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* load ctr state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CTR);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_din_type(&desc[idx], DMA_DLLI,
		     req_ctx->gen_ctx.iv_dma_addr, AES_BLOCK_SIZE, NS_BIT);
	set_cipher_config0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	/* load MAC key */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CBC_MAC);
	set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
		     ((ctx->enc_keylen == 24) ?  CC_AES_KEY_SIZE_MAX :
		      ctx->enc_keylen), NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_cipher_config0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* load MAC state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CBC_MAC);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->mac_buf_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_cipher_config0(&desc[idx], DESC_DIRECTION_ENCRYPT_ENCRYPT);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* process assoc data */
	if (req_ctx->assoclen > 0) {
		cc_set_assoc_desc(req, DIN_HASH, desc, &idx);
	} else {
		hw_desc_init(&desc[idx]);
		set_din_type(&desc[idx], DMA_DLLI,
			     sg_dma_address(&req_ctx->ccm_adata_sg),
			     AES_BLOCK_SIZE + req_ctx->ccm_hdr_size, NS_BIT);
		set_flow_mode(&desc[idx], DIN_HASH);
		idx++;
	}

	/* process the cipher */
	if (req_ctx->cryptlen)
		cc_proc_cipher_desc(req, cipher_flow_mode, desc, &idx);

	/* Read temporal MAC */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CBC_MAC);
	set_dout_dlli(&desc[idx], req_ctx->mac_buf_dma_addr, ctx->authsize,
		      NS_BIT, 0);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_cipher_config0(&desc[idx], HASH_DIGEST_RESULT_LITTLE_ENDIAN);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_aes_not_hash_mode(&desc[idx]);
	idx++;

	/* load AES-CTR state (for last MAC calculation)*/
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], DRV_CIPHER_CTR);
	set_cipher_config0(&desc[idx], DRV_CRYPTO_DIRECTION_ENCRYPT);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->ccm_iv0_dma_addr,
		     AES_BLOCK_SIZE, NS_BIT);
	set_key_size_aes(&desc[idx], ctx->enc_keylen);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	set_flow_mode(&desc[idx], S_DIN_to_AES);
	idx++;

	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_dout_no_dma(&desc[idx], 0, 0, 1);
	idx++;

	/* encrypt the "T" value and store MAC in mac_state */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->mac_buf_dma_addr,
		     ctx->authsize, NS_BIT);
	set_dout_dlli(&desc[idx], mac_result, ctx->authsize, NS_BIT, 1);
	set_queue_last_ind(ctx->drvdata, &desc[idx]);
	set_flow_mode(&desc[idx], DIN_AES_DOUT);
	idx++;

	*seq_size = idx;
	return 0;
}