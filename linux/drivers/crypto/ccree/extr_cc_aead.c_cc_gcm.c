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
struct cc_hw_desc {int dummy; } ;
struct aead_request {int dummy; } ;
struct TYPE_2__ {scalar_t__ op_type; } ;
struct aead_req_ctx {scalar_t__ assoclen; scalar_t__ cryptlen; scalar_t__ plaintext_authenticate_only; TYPE_1__ gen_ctx; } ;

/* Variables and functions */
 unsigned int AES_and_HASH ; 
 unsigned int AES_to_HASH_and_DOUT ; 
 unsigned int BYPASS ; 
 int /*<<< orphan*/  DIN_HASH ; 
 scalar_t__ DRV_CRYPTO_DIRECTION_DECRYPT ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  cc_proc_cipher_desc (struct aead_request*,unsigned int,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_proc_gcm_result (struct aead_request*,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_set_assoc_desc (struct aead_request*,int /*<<< orphan*/ ,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_set_gctr_desc (struct aead_request*,struct cc_hw_desc*,unsigned int*) ; 
 int /*<<< orphan*/  cc_set_ghash_desc (struct aead_request*,struct cc_hw_desc*,unsigned int*) ; 

__attribute__((used)) static int cc_gcm(struct aead_request *req, struct cc_hw_desc desc[],
		  unsigned int *seq_size)
{
	struct aead_req_ctx *req_ctx = aead_request_ctx(req);
	unsigned int cipher_flow_mode;

	if (req_ctx->gen_ctx.op_type == DRV_CRYPTO_DIRECTION_DECRYPT) {
		cipher_flow_mode = AES_and_HASH;
	} else { /* Encrypt */
		cipher_flow_mode = AES_to_HASH_and_DOUT;
	}

	//in RFC4543 no data to encrypt. just copy data from src to dest.
	if (req_ctx->plaintext_authenticate_only) {
		cc_proc_cipher_desc(req, BYPASS, desc, seq_size);
		cc_set_ghash_desc(req, desc, seq_size);
		/* process(ghash) assoc data */
		cc_set_assoc_desc(req, DIN_HASH, desc, seq_size);
		cc_set_gctr_desc(req, desc, seq_size);
		cc_proc_gcm_result(req, desc, seq_size);
		return 0;
	}

	// for gcm and rfc4106.
	cc_set_ghash_desc(req, desc, seq_size);
	/* process(ghash) assoc data */
	if (req_ctx->assoclen > 0)
		cc_set_assoc_desc(req, DIN_HASH, desc, seq_size);
	cc_set_gctr_desc(req, desc, seq_size);
	/* process(gctr+ghash) */
	if (req_ctx->cryptlen)
		cc_proc_cipher_desc(req, cipher_flow_mode, desc, seq_size);
	cc_proc_gcm_result(req, desc, seq_size);

	return 0;
}