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
typedef  int /*<<< orphan*/  uint8_t ;
struct qat_alg_aead_ctx {int /*<<< orphan*/  dec_fw_req; int /*<<< orphan*/  enc_fw_req; int /*<<< orphan*/ * dec_cd; int /*<<< orphan*/ * enc_cd; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICP_QAT_HW_CIPHER_CBC_MODE ; 
 struct qat_alg_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qat_alg_aead_init_sessions (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_alg_aead_rekey(struct crypto_aead *tfm, const uint8_t *key,
			      unsigned int keylen)
{
	struct qat_alg_aead_ctx *ctx = crypto_aead_ctx(tfm);

	memset(ctx->enc_cd, 0, sizeof(*ctx->enc_cd));
	memset(ctx->dec_cd, 0, sizeof(*ctx->dec_cd));
	memset(&ctx->enc_fw_req, 0, sizeof(ctx->enc_fw_req));
	memset(&ctx->dec_fw_req, 0, sizeof(ctx->dec_fw_req));

	return qat_alg_aead_init_sessions(tfm, key, keylen,
					  ICP_QAT_HW_CIPHER_CBC_MODE);
}