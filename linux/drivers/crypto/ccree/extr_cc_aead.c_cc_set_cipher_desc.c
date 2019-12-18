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
struct cc_aead_ctx {scalar_t__ flow_mode; scalar_t__ cipher_mode; int enc_keylen; int /*<<< orphan*/  enckey_dma_addr; } ;
struct aead_request {int dummy; } ;
struct TYPE_2__ {int op_type; int /*<<< orphan*/  iv_dma_addr; } ;
struct aead_req_ctx {unsigned int hw_iv_size; TYPE_1__ gen_ctx; } ;

/* Variables and functions */
 unsigned int CC_AES_KEY_SIZE_MAX ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 scalar_t__ DRV_CIPHER_CTR ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE1 ; 
 scalar_t__ S_DIN_to_AES ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,scalar_t__) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,scalar_t__) ; 
 int /*<<< orphan*/  set_key_size_aes (struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_key_size_des (struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_set_cipher_desc(struct aead_request *req,
			       struct cc_hw_desc desc[],
			       unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int hw_iv_size = req_ctx->hw_iv_size;
	unsigned int idx = *seq_size;
	int direct = req_ctx->gen_ctx.op_type;

	/* Setup cipher state */
	hw_desc_init(&desc[idx]);
	set_cipher_config0(&desc[idx], direct);
	set_flow_mode(&desc[idx], ctx->flow_mode);
	set_din_type(&desc[idx], DMA_DLLI, req_ctx->gen_ctx.iv_dma_addr,
		     hw_iv_size, NS_BIT);
	if (ctx->cipher_mode == DRV_CIPHER_CTR)
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE1);
	else
		set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	set_cipher_mode(&desc[idx], ctx->cipher_mode);
	idx++;

	/* Setup enc. key */
	hw_desc_init(&desc[idx]);
	set_cipher_config0(&desc[idx], direct);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	set_flow_mode(&desc[idx], ctx->flow_mode);
	if (ctx->flow_mode == S_DIN_to_AES) {
		set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
			     ((ctx->enc_keylen == 24) ? CC_AES_KEY_SIZE_MAX :
			      ctx->enc_keylen), NS_BIT);
		set_key_size_aes(&desc[idx], ctx->enc_keylen);
	} else {
		set_din_type(&desc[idx], DMA_DLLI, ctx->enckey_dma_addr,
			     ctx->enc_keylen, NS_BIT);
		set_key_size_des(&desc[idx], ctx->enc_keylen);
	}
	set_cipher_mode(&desc[idx], ctx->cipher_mode);
	idx++;

	*seq_size = idx;
}