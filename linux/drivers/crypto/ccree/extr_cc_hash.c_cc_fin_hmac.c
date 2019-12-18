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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_ahash {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct cc_hash_ctx {int /*<<< orphan*/  hash_len; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  drvdata; int /*<<< orphan*/  hw_mode; int /*<<< orphan*/  inter_digestsize; } ;
struct ahash_request {int dummy; } ;
struct ahash_req_ctx {int /*<<< orphan*/  digest_buff_dma_addr; int /*<<< orphan*/  opad_digest_dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIN_HASH ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  HASH_PADDING_ENABLED ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE0 ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE0 ; 
 int /*<<< orphan*/  S_DIN_to_HASH ; 
 int /*<<< orphan*/  S_HASH_to_DOUT ; 
 struct ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  cc_digest_len_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_set_endianity (int /*<<< orphan*/ ,struct cc_hw_desc*) ; 
 struct cc_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 int /*<<< orphan*/  crypto_ahash_digestsize (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config1 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_din_sram (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dout_no_dma (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_fin_hmac(struct cc_hw_desc *desc, struct ahash_request *req,
		       int idx)
{
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct cc_hash_ctx *ctx = crypto_ahash_ctx(tfm);
	u32 digestsize = crypto_ahash_digestsize(tfm);

	/* store the hash digest result in the context */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	set_dout_dlli(&desc[idx], state->digest_buff_dma_addr, digestsize,
		      NS_BIT, 0);
	set_flow_mode(&desc[idx], S_HASH_to_DOUT);
	cc_set_endianity(ctx->hash_mode, &desc[idx]);
	set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
	idx++;

	/* Loading hash opad xor key state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	set_din_type(&desc[idx], DMA_DLLI, state->opad_digest_dma_addr,
		     ctx->inter_digestsize, NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load the hash current length */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], ctx->hw_mode);
	set_din_sram(&desc[idx],
		     cc_digest_len_addr(ctx->drvdata, ctx->hash_mode),
		     ctx->hash_len);
	set_cipher_config1(&desc[idx], HASH_PADDING_ENABLED);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	/* Memory Barrier: wait for IPAD/OPAD axi write to complete */
	hw_desc_init(&desc[idx]);
	set_din_no_dma(&desc[idx], 0, 0xfffff0);
	set_dout_no_dma(&desc[idx], 0, 0, 1);
	idx++;

	/* Perform HASH update */
	hw_desc_init(&desc[idx]);
	set_din_type(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr,
		     digestsize, NS_BIT);
	set_flow_mode(&desc[idx], DIN_HASH);
	idx++;

	return idx;
}