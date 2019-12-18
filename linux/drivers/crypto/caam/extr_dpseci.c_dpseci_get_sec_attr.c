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
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpseci_sec_attr {int /*<<< orphan*/  ptha_acc_num; int /*<<< orphan*/  ccha_acc_num; int /*<<< orphan*/  aes_acc_num; int /*<<< orphan*/  des_acc_num; int /*<<< orphan*/  arc4_acc_num; int /*<<< orphan*/  md_acc_num; int /*<<< orphan*/  rng_acc_num; int /*<<< orphan*/  kasumi_acc_num; int /*<<< orphan*/  pk_acc_num; int /*<<< orphan*/  crc_acc_num; int /*<<< orphan*/  snow_f9_acc_num; int /*<<< orphan*/  snow_f8_acc_num; int /*<<< orphan*/  zuc_enc_acc_num; int /*<<< orphan*/  zuc_auth_acc_num; int /*<<< orphan*/  deco_num; int /*<<< orphan*/  era; int /*<<< orphan*/  minor_rev; int /*<<< orphan*/  major_rev; int /*<<< orphan*/  ip_id; } ;
struct dpseci_rsp_get_sec_attr {int /*<<< orphan*/  ptha_acc_num; int /*<<< orphan*/  ccha_acc_num; int /*<<< orphan*/  aes_acc_num; int /*<<< orphan*/  des_acc_num; int /*<<< orphan*/  arc4_acc_num; int /*<<< orphan*/  md_acc_num; int /*<<< orphan*/  rng_acc_num; int /*<<< orphan*/  kasumi_acc_num; int /*<<< orphan*/  pk_acc_num; int /*<<< orphan*/  crc_acc_num; int /*<<< orphan*/  snow_f9_acc_num; int /*<<< orphan*/  snow_f8_acc_num; int /*<<< orphan*/  zuc_enc_acc_num; int /*<<< orphan*/  zuc_auth_acc_num; int /*<<< orphan*/  deco_num; int /*<<< orphan*/  era; int /*<<< orphan*/  minor_rev; int /*<<< orphan*/  major_rev; int /*<<< orphan*/  ip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPSECI_CMDID_GET_SEC_ATTR ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpseci_get_sec_attr(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			struct dpseci_sec_attr *attr)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpseci_rsp_get_sec_attr *rsp_params;
	int err;

	cmd.header = mc_encode_cmd_header(DPSECI_CMDID_GET_SEC_ATTR,
					  cmd_flags,
					  token);
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	rsp_params = (struct dpseci_rsp_get_sec_attr *)cmd.params;
	attr->ip_id = le16_to_cpu(rsp_params->ip_id);
	attr->major_rev = rsp_params->major_rev;
	attr->minor_rev = rsp_params->minor_rev;
	attr->era = rsp_params->era;
	attr->deco_num = rsp_params->deco_num;
	attr->zuc_auth_acc_num = rsp_params->zuc_auth_acc_num;
	attr->zuc_enc_acc_num = rsp_params->zuc_enc_acc_num;
	attr->snow_f8_acc_num = rsp_params->snow_f8_acc_num;
	attr->snow_f9_acc_num = rsp_params->snow_f9_acc_num;
	attr->crc_acc_num = rsp_params->crc_acc_num;
	attr->pk_acc_num = rsp_params->pk_acc_num;
	attr->kasumi_acc_num = rsp_params->kasumi_acc_num;
	attr->rng_acc_num = rsp_params->rng_acc_num;
	attr->md_acc_num = rsp_params->md_acc_num;
	attr->arc4_acc_num = rsp_params->arc4_acc_num;
	attr->des_acc_num = rsp_params->des_acc_num;
	attr->aes_acc_num = rsp_params->aes_acc_num;
	attr->ccha_acc_num = rsp_params->ccha_acc_num;
	attr->ptha_acc_num = rsp_params->ptha_acc_num;

	return 0;
}