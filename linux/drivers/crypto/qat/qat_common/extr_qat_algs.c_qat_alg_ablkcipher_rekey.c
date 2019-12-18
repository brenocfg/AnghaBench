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
typedef  int /*<<< orphan*/  u8 ;
struct qat_alg_ablkcipher_ctx {int /*<<< orphan*/  dec_fw_req; int /*<<< orphan*/  enc_fw_req; int /*<<< orphan*/ * dec_cd; int /*<<< orphan*/ * enc_cd; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qat_alg_ablkcipher_init_sessions (struct qat_alg_ablkcipher_ctx*,int /*<<< orphan*/  const*,unsigned int,int) ; 

__attribute__((used)) static int qat_alg_ablkcipher_rekey(struct qat_alg_ablkcipher_ctx *ctx,
				    const u8 *key, unsigned int keylen,
				    int mode)
{
	memset(ctx->enc_cd, 0, sizeof(*ctx->enc_cd));
	memset(ctx->dec_cd, 0, sizeof(*ctx->dec_cd));
	memset(&ctx->enc_fw_req, 0, sizeof(ctx->enc_fw_req));
	memset(&ctx->dec_fw_req, 0, sizeof(ctx->dec_fw_req));

	return qat_alg_ablkcipher_init_sessions(ctx, key, keylen, mode);
}