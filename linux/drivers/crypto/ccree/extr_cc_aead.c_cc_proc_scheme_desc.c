#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct crypto_aead {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_aead_handle {int /*<<< orphan*/  sram_workspace_addr; } ;
struct TYPE_4__ {scalar_t__ ipad_opad_dma_addr; } ;
struct TYPE_5__ {TYPE_1__ hmac; } ;
struct cc_aead_ctx {scalar_t__ auth_mode; unsigned int hash_len; TYPE_3__* drvdata; TYPE_2__ auth_state; } ;
struct aead_request {int dummy; } ;
struct TYPE_6__ {struct cc_aead_handle* aead_handle; } ;

/* Variables and functions */
 unsigned int CC_SHA1_DIGEST_SIZE ; 
 unsigned int CC_SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  DIN_HASH ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  DO_PAD ; 
 unsigned int DRV_HASH_HW_SHA1 ; 
 unsigned int DRV_HASH_HW_SHA256 ; 
 scalar_t__ DRV_HASH_SHA1 ; 
 int /*<<< orphan*/  HASH_DIGEST_RESULT_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  HASH_PADDING_ENABLED ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE0 ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE0 ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE1 ; 
 int /*<<< orphan*/  S_DIN_to_HASH ; 
 int /*<<< orphan*/  S_HASH_to_DOUT ; 
 int /*<<< orphan*/  cc_digest_len_addr (TYPE_3__*,unsigned int) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_config1 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_do (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_din_sram (struct cc_hw_desc*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_sram (struct cc_hw_desc*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_proc_scheme_desc(struct aead_request *req,
				struct cc_hw_desc desc[],
				unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct cc_aead_handle *aead_handle = ctx->drvdata->aead_handle;
	unsigned int hash_mode = (ctx->auth_mode == DRV_HASH_SHA1) ?
				DRV_HASH_HW_SHA1 : DRV_HASH_HW_SHA256;
	unsigned int digest_size = (ctx->auth_mode == DRV_HASH_SHA1) ?
				CC_SHA1_DIGEST_SIZE : CC_SHA256_DIGEST_SIZE;
	unsigned int idx = *seq_size;

	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_dout_sram(&desc[idx], aead_handle->sram_workspace_addr,
		      ctx->hash_len);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE1);
	set_cipher_do(&desc[idx], DO_PAD);
	idx++;

	/* Get final ICV result */
	hw_desc_init(&desc[idx]);
	set_dout_sram(&desc[idx], aead_handle->sram_workspace_addr,
		      digest_size);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	set_cipher_config0(&desc[idx], HASH_DIGEST_RESULT_LITTLE_ENDIAN);
	set_cipher_mode(&desc[idx], hash_mode);
	idx++;

	/* Loading hash opad xor key state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_din_type(&desc[idx], DMA_DLLI,
		     (ctx->auth_state.hmac.ipad_opad_dma_addr + digest_size),
		     digest_size, NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load init. digest len (64 bytes) */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_din_sram(&desc[idx], cc_digest_len_addr(ctx->drvdata, hash_mode),
		     ctx->hash_len);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Perform HASH update */
	hw_desc_init(&desc[idx]);
	set_din_sram(&desc[idx], aead_handle->sram_workspace_addr,
		     digest_size);
	set_flow_mode(&desc[idx], DIN_HASH);
	idx++;

	*seq_size = idx;
}