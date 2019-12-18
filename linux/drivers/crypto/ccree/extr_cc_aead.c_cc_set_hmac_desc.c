#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_aead {int dummy; } ;
struct cc_hw_desc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ipad_opad_dma_addr; } ;
struct TYPE_4__ {TYPE_1__ hmac; } ;
struct cc_aead_ctx {scalar_t__ auth_mode; int /*<<< orphan*/  hash_len; int /*<<< orphan*/  drvdata; TYPE_2__ auth_state; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 unsigned int CC_SHA1_DIGEST_SIZE ; 
 unsigned int CC_SHA256_DIGEST_SIZE ; 
 int /*<<< orphan*/  DMA_DLLI ; 
 unsigned int DRV_HASH_HW_SHA1 ; 
 unsigned int DRV_HASH_HW_SHA256 ; 
 scalar_t__ DRV_HASH_SHA1 ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_LOAD_KEY0 ; 
 int /*<<< orphan*/  SETUP_LOAD_STATE0 ; 
 int /*<<< orphan*/  S_DIN_to_HASH ; 
 int /*<<< orphan*/  cc_digest_len_addr (int /*<<< orphan*/ ,unsigned int) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_din_sram (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_din_type (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_set_hmac_desc(struct aead_request *req, struct cc_hw_desc desc[],
			     unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	unsigned int hash_mode = (ctx->auth_mode == DRV_HASH_SHA1) ?
				DRV_HASH_HW_SHA1 : DRV_HASH_HW_SHA256;
	unsigned int digest_size = (ctx->auth_mode == DRV_HASH_SHA1) ?
				CC_SHA1_DIGEST_SIZE : CC_SHA256_DIGEST_SIZE;
	unsigned int idx = *seq_size;

	/* Loading hash ipad xor key state */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_din_type(&desc[idx], DMA_DLLI,
		     ctx->auth_state.hmac.ipad_opad_dma_addr, digest_size,
		     NS_BIT);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_STATE0);
	idx++;

	/* Load init. digest len (64 bytes) */
	hw_desc_init(&desc[idx]);
	set_cipher_mode(&desc[idx], hash_mode);
	set_din_sram(&desc[idx], cc_digest_len_addr(ctx->drvdata, hash_mode),
		     ctx->hash_len);
	set_flow_mode(&desc[idx], S_DIN_to_HASH);
	set_setup_mode(&desc[idx], SETUP_LOAD_KEY0);
	idx++;

	*seq_size = idx;
}