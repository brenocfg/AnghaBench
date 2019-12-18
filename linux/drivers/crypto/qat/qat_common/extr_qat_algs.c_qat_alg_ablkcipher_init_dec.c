#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  content_desc_addr; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct icp_qat_fw_comn_req_hdr_cd_pars {TYPE_2__ u; } ;
struct icp_qat_fw_la_bulk_req {struct icp_qat_fw_comn_req_hdr_cd_pars cd_pars; } ;
struct qat_alg_ablkcipher_ctx {int /*<<< orphan*/  dec_cd_paddr; struct icp_qat_fw_la_bulk_req dec_fw_req; struct icp_qat_hw_cipher_algo_blk* dec_cd; } ;
struct TYPE_7__ {int /*<<< orphan*/  val; } ;
struct TYPE_8__ {TYPE_3__ cipher_config; } ;
struct icp_qat_hw_cipher_algo_blk {TYPE_4__ aes; } ;

/* Variables and functions */
 int ICP_QAT_HW_CIPHER_CTR_MODE ; 
 int /*<<< orphan*/  QAT_AES_HW_CONFIG_DEC (int,int) ; 
 int /*<<< orphan*/  QAT_AES_HW_CONFIG_ENC (int,int) ; 
 int /*<<< orphan*/  qat_alg_ablkcipher_init_com (struct qat_alg_ablkcipher_ctx*,struct icp_qat_fw_la_bulk_req*,struct icp_qat_hw_cipher_algo_blk*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void qat_alg_ablkcipher_init_dec(struct qat_alg_ablkcipher_ctx *ctx,
					int alg, const uint8_t *key,
					unsigned int keylen, int mode)
{
	struct icp_qat_hw_cipher_algo_blk *dec_cd = ctx->dec_cd;
	struct icp_qat_fw_la_bulk_req *req = &ctx->dec_fw_req;
	struct icp_qat_fw_comn_req_hdr_cd_pars *cd_pars = &req->cd_pars;

	qat_alg_ablkcipher_init_com(ctx, req, dec_cd, key, keylen);
	cd_pars->u.s.content_desc_addr = ctx->dec_cd_paddr;

	if (mode != ICP_QAT_HW_CIPHER_CTR_MODE)
		dec_cd->aes.cipher_config.val =
					QAT_AES_HW_CONFIG_DEC(alg, mode);
	else
		dec_cd->aes.cipher_config.val =
					QAT_AES_HW_CONFIG_ENC(alg, mode);
}