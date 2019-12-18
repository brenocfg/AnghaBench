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
struct cc_hw_desc {int dummy; } ;
struct cc_hash_ctx {int /*<<< orphan*/  hash_len; int /*<<< orphan*/  hash_mode; int /*<<< orphan*/  hw_mode; int /*<<< orphan*/  inter_digestsize; } ;
struct ahash_req_ctx {int /*<<< orphan*/  digest_bytes_len_dma_addr; int /*<<< orphan*/  digest_buff_dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIN_HASH ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 int /*<<< orphan*/  HASH_PADDING_DISABLED ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE0 ; 
 int /*<<< orphan*/  S_DIN_to_HASH ; 
 int /*<<< orphan*/  cc_set_desc (struct ahash_req_ctx*,struct cc_hash_ctx*,int /*<<< orphan*/ ,struct cc_hw_desc*,int,unsigned int*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config1 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hash_cipher_mode (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cc_restore_hash(struct cc_hw_desc *desc, struct cc_hash_ctx *ctx,
			   struct ahash_req_ctx *state, unsigned int idx)
{
	/* Restore hash digest */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_din_type(&desc[idx], DMA_DLLI, state->digest_buff_dma_addr,
		     ctx->inter_digestsize, NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Restore hash current length */
	hw_desc_init(&desc[idx]);
	set_hash_cipher_mode(&desc[idx], ctx->hw_mode, ctx->hash_mode);
	set_cipher_config1(&desc[idx], HASH_PADDING_DISABLED);
	set_din_type(&desc[idx], DMA_DLLI, state->digest_bytes_len_dma_addr,
		     ctx->hash_len, NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	cc_set_desc(state, ctx, DIN_HASH, desc, false, &idx);

	return idx;
}