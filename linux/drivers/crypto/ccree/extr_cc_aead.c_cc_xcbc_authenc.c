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
struct cc_aead_ctx {int /*<<< orphan*/  flow_mode; } ;
struct aead_request {int dummy; } ;
struct TYPE_2__ {int op_type; } ;
struct aead_req_ctx {scalar_t__ is_single_pass; TYPE_1__ gen_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIN_HASH ; 
 int DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 unsigned int cc_get_data_flow (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cc_proc_authen_desc (struct aead_request*,int /*<<< orphan*/ ,struct cc_hw_desc*,unsigned int*,int) ; 
 int /*<<< orphan*/  cc_proc_cipher (struct aead_request*,struct cc_hw_desc*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  cc_proc_cipher_desc (struct aead_request*,unsigned int,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_proc_digest_desc (struct aead_request*,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_proc_header_desc (struct aead_request*,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_set_cipher_desc (struct aead_request*,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_set_xcbc_desc (struct aead_request*,struct cc_hw_desc*,unsigned int*) ; 
 struct cc_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 

__attribute__((used)) static void
cc_xcbc_authenc(struct aead_request *req, struct cc_hw_desc desc[],
		unsigned int *seq_size)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct cc_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	int direct = req_ctx->gen_ctx.op_type;
	unsigned int data_flow_mode =
		cc_get_data_flow(direct, ctx->flow_mode,
				 req_ctx->is_single_pass);

	if (req_ctx->is_single_pass) {
		/**
		 * Single-pass flow
		 */
		cc_set_xcbc_desc(req, desc, seq_size);
		cc_set_cipher_desc(req, desc, seq_size);
		cc_proc_header_desc(req, desc, seq_size);
		cc_proc_cipher_desc(req, data_flow_mode, desc, seq_size);
		cc_proc_digest_desc(req, desc, seq_size);
		return;
	}

	/**
	 * Double-pass flow
	 * Fallback for unsupported single-pass modes,
	 * i.e. using assoc. data of non-word-multiple
	 */
	if (direct == DRV_CRYPTO_DIRECTION_ENCRYPT) {
		/* encrypt first.. */
		cc_proc_cipher(req, desc, seq_size, data_flow_mode);
		/* authenc after.. */
		cc_set_xcbc_desc(req, desc, seq_size);
		cc_proc_authen_desc(req, DIN_HASH, desc, seq_size, direct);
		cc_proc_digest_desc(req, desc, seq_size);
	} else { /*DECRYPT*/
		/* authenc first.. */
		cc_set_xcbc_desc(req, desc, seq_size);
		cc_proc_authen_desc(req, DIN_HASH, desc, seq_size, direct);
		/* decrypt after..*/
		cc_proc_cipher(req, desc, seq_size, data_flow_mode);
		/* read the digest result with setting the completion bit
		 * must be after the cipher operation
		 */
		cc_proc_digest_desc(req, desc, seq_size);
	}
}