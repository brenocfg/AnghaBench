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
struct icp_qat_simg_ae_mode {unsigned int ae_mask; } ;
struct icp_qat_fw_loader_handle {TYPE_1__* hal_handle; } ;
struct icp_qat_fw_auth_desc {int dummy; } ;
struct icp_qat_css_hdr {int dummy; } ;
struct icp_qat_auth_chunk {int dummy; } ;
struct TYPE_2__ {unsigned int ae_max_num; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int FCU_AUTH_STS_MASK ; 
 int /*<<< orphan*/  FCU_CONTROL ; 
 unsigned int FCU_CTRL_AE_POS ; 
 unsigned int FCU_CTRL_CMD_LOAD ; 
 unsigned int FCU_LOADED_AE_POS ; 
 int /*<<< orphan*/  FCU_STATUS ; 
 unsigned int FCU_STS_LOAD_DONE ; 
 int FW_AUTH_MAX_RETRY ; 
 int /*<<< orphan*/  FW_AUTH_WAIT_PERIOD ; 
 unsigned int GET_CAP_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ) ; 
 scalar_t__ ICP_QAT_CSS_FWSK_PUB_LEN ; 
 scalar_t__ ICP_QAT_CSS_SIGNATURE_LEN ; 
 int /*<<< orphan*/  SET_CAP_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ qat_hal_check_ae_active (struct icp_qat_fw_loader_handle*,unsigned int) ; 

__attribute__((used)) static int qat_uclo_load_fw(struct icp_qat_fw_loader_handle *handle,
			    struct icp_qat_fw_auth_desc *desc)
{
	unsigned int i;
	unsigned int fcu_sts;
	struct icp_qat_simg_ae_mode *virt_addr;
	unsigned int fcu_loaded_ae_pos = FCU_LOADED_AE_POS;

	virt_addr = (void *)((uintptr_t)desc +
		     sizeof(struct icp_qat_auth_chunk) +
		     sizeof(struct icp_qat_css_hdr) +
		     ICP_QAT_CSS_FWSK_PUB_LEN +
		     ICP_QAT_CSS_SIGNATURE_LEN);
	for (i = 0; i < handle->hal_handle->ae_max_num; i++) {
		int retry = 0;

		if (!((virt_addr->ae_mask >> i) & 0x1))
			continue;
		if (qat_hal_check_ae_active(handle, i)) {
			pr_err("QAT: AE %d is active\n", i);
			return -EINVAL;
		}
		SET_CAP_CSR(handle, FCU_CONTROL,
			    (FCU_CTRL_CMD_LOAD | (i << FCU_CTRL_AE_POS)));

		do {
			msleep(FW_AUTH_WAIT_PERIOD);
			fcu_sts = GET_CAP_CSR(handle, FCU_STATUS);
			if (((fcu_sts & FCU_AUTH_STS_MASK) ==
			    FCU_STS_LOAD_DONE) &&
			    ((fcu_sts >> fcu_loaded_ae_pos) & (1 << i)))
				break;
		} while (retry++ < FW_AUTH_MAX_RETRY);
		if (retry > FW_AUTH_MAX_RETRY) {
			pr_err("QAT: firmware load failed timeout %x\n", retry);
			return -EINVAL;
		}
	}
	return 0;
}