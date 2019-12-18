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
typedef  int /*<<< orphan*/  uint8_t ;
struct qat_alg_ablkcipher_ctx {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  key; } ;
struct icp_qat_hw_cipher_algo_blk {TYPE_1__ aes; } ;
struct icp_qat_fw_comn_req_hdr {int /*<<< orphan*/  service_cmd_id; } ;
struct TYPE_5__ {int content_desc_params_sz; } ;
struct TYPE_6__ {TYPE_2__ s; } ;
struct icp_qat_fw_comn_req_hdr_cd_pars {TYPE_3__ u; } ;
struct icp_qat_fw_la_bulk_req {int /*<<< orphan*/  cd_ctrl; struct icp_qat_fw_comn_req_hdr comn_hdr; struct icp_qat_fw_comn_req_hdr_cd_pars cd_pars; } ;
struct icp_qat_fw_cipher_cd_ctrl_hdr {unsigned int cipher_key_sz; int cipher_state_sz; scalar_t__ cipher_cfg_offset; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  ICP_QAT_FW_COMN_CURR_ID_SET (struct icp_qat_fw_cipher_cd_ctrl_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_QAT_FW_COMN_NEXT_ID_SET (struct icp_qat_fw_cipher_cd_ctrl_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_CMD_CIPHER ; 
 int /*<<< orphan*/  ICP_QAT_FW_SLICE_CIPHER ; 
 int /*<<< orphan*/  ICP_QAT_FW_SLICE_DRAM_WR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  qat_alg_init_common_hdr (struct icp_qat_fw_comn_req_hdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qat_alg_ablkcipher_init_com(struct qat_alg_ablkcipher_ctx *ctx,
					struct icp_qat_fw_la_bulk_req *req,
					struct icp_qat_hw_cipher_algo_blk *cd,
					const uint8_t *key, unsigned int keylen)
{
	struct icp_qat_fw_comn_req_hdr_cd_pars *cd_pars = &req->cd_pars;
	struct icp_qat_fw_comn_req_hdr *header = &req->comn_hdr;
	struct icp_qat_fw_cipher_cd_ctrl_hdr *cd_ctrl = (void *)&req->cd_ctrl;

	memcpy(cd->aes.key, key, keylen);
	qat_alg_init_common_hdr(header, 0);
	header->service_cmd_id = ICP_QAT_FW_LA_CMD_CIPHER;
	cd_pars->u.s.content_desc_params_sz =
				sizeof(struct icp_qat_hw_cipher_algo_blk) >> 3;
	/* Cipher CD config setup */
	cd_ctrl->cipher_key_sz = keylen >> 3;
	cd_ctrl->cipher_state_sz = AES_BLOCK_SIZE >> 3;
	cd_ctrl->cipher_cfg_offset = 0;
	ICP_QAT_FW_COMN_CURR_ID_SET(cd_ctrl, ICP_QAT_FW_SLICE_CIPHER);
	ICP_QAT_FW_COMN_NEXT_ID_SET(cd_ctrl, ICP_QAT_FW_SLICE_DRAM_WR);
}