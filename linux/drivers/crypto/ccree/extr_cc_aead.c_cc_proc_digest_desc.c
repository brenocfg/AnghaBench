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
struct cc_aead_ctx {scalar_t__ auth_mode; int /*<<< orphan*/  drvdata; int /*<<< orphan*/  authsize; } ;
struct aead_request {int dummy; } ;
struct TYPE_2__ {int op_type; } ;
struct aead_req_ctx {int /*<<< orphan*/  mac_buf_dma_addr; int /*<<< orphan*/  icv_dma_addr; TYPE_1__ gen_ctx; } ;

/* Variables and functions */
 unsigned int DRV_CIPHER_XCBC_MAC ; 
 int DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 unsigned int DRV_HASH_HW_SHA1 ; 
 unsigned int DRV_HASH_HW_SHA256 ; 
 scalar_t__ DRV_HASH_SHA1 ; 
 scalar_t__ DRV_HASH_XCBC_MAC ; 
 int /*<<< orphan*/  HASH_DIGEST_RESULT_LITTLE_ENDIAN ; 
 int /*<<< orphan*/  HASH_PADDING_DISABLED ; 
 int /*<<< orphan*/  NS_BIT ; 
 int /*<<< orphan*/  SETUP_WRITE_STATE0 ; 
 int /*<<< orphan*/  S_HASH_to_DOUT ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  hw_desc_init (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_aes_not_hash_mode (struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_cipher_config0 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_config1 (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cipher_mode (struct cc_hw_desc*,unsigned int) ; 
 int /*<<< orphan*/  set_dout_dlli (struct cc_hw_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_flow_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_queue_last_ind (int /*<<< orphan*/ ,struct cc_hw_desc*) ; 
 int /*<<< orphan*/  set_setup_mode (struct cc_hw_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cc_proc_digest_desc(struct aead_request *req,
				struct cc_hw_desc desc[],
				unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int idx = *seq_size;
	unsigned int hash_mode = (ctx->auth_mode == DRV_HASH_SHA1) ?
				DRV_HASH_HW_SHA1 : DRV_HASH_HW_SHA256;
	int direct = req_ctx->gen_ctx.op_type;

	/* Get final ICV result */
	if (direct == DRV_CRYPTO_DIRECTION_ENCRYPT) {
		hw_desc_init(&desc[idx]);
		set_flow_mode(&desc[idx], S_HASH_to_DOUT);
		set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
		set_dout_dlli(&desc[idx], req_ctx->icv_dma_addr, ctx->authsize,
			      NS_BIT, 1);
		set_queue_last_ind(ctx->drvdata, &desc[idx]);
		if (ctx->auth_mode == DRV_HASH_XCBC_MAC) {
			set_aes_not_hash_mode(&desc[idx]);
			set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
		} else {
			set_cipher_config0(&desc[idx],
					   HASH_DIGEST_RESULT_LITTLE_ENDIAN);
			set_cipher_mode(&desc[idx], hash_mode);
		}
	} else { /*Decrypt*/
		/* Get ICV out from hardware */
		hw_desc_init(&desc[idx]);
		set_setup_mode(&desc[idx], SETUP_WRITE_STATE0);
		set_flow_mode(&desc[idx], S_HASH_to_DOUT);
		set_dout_dlli(&desc[idx], req_ctx->mac_buf_dma_addr,
			      ctx->authsize, NS_BIT, 1);
		set_queue_last_ind(ctx->drvdata, &desc[idx]);
		set_cipher_config0(&desc[idx],
				   HASH_DIGEST_RESULT_LITTLE_ENDIAN);
		set_cipher_config1(&desc[idx], HASH_PADDING_DISABLED);
		if (ctx->auth_mode == DRV_HASH_XCBC_MAC) {
			set_cipher_mode(&desc[idx], DRV_CIPHER_XCBC_MAC);
			set_aes_not_hash_mode(&desc[idx]);
		} else {
			set_cipher_mode(&desc[idx], hash_mode);
		}
	}

	*seq_size = (++idx);
}