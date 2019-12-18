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
struct icp_qat_fw_loader_handle {TYPE_1__* hal_handle; } ;
struct TYPE_2__ {unsigned int ae_mask; unsigned int slice_mask; unsigned char ae_max_num; int upc_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_ENABLE ; 
 int /*<<< orphan*/  CTX_ARB_CNTL ; 
 int /*<<< orphan*/  CTX_ENABLES ; 
 int /*<<< orphan*/  CTX_STS_INDIRECT ; 
 int EFAULT ; 
 unsigned int GET_GLB_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_GLOBAL_CLK_ENABLE ; 
 int /*<<< orphan*/  ICP_QAT_UCLO_AE_ALL_CTX ; 
 int /*<<< orphan*/  ICP_RESET ; 
 int /*<<< orphan*/  INIT_CCENABLE_VALUE ; 
 int /*<<< orphan*/  INIT_CTX_ARB_VALUE ; 
 int /*<<< orphan*/  INIT_CTX_ENABLE_VALUE ; 
 int INIT_PC_VALUE ; 
 int /*<<< orphan*/  INIT_SIG_EVENTS_VALUE ; 
 int /*<<< orphan*/  INIT_WAKEUP_EVENTS_VALUE ; 
 unsigned int RST_CSR_AE_LSB ; 
 unsigned int RST_CSR_QAT_LSB ; 
 int /*<<< orphan*/  SET_GLB_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SHRAM_INIT_CYCLES ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ qat_hal_check_ae_alive (struct icp_qat_fw_loader_handle*) ; 
 scalar_t__ qat_hal_init_esram (struct icp_qat_fw_loader_handle*) ; 
 int /*<<< orphan*/  qat_hal_put_sig_event (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_put_wakeup_event (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_reset_timestamp (struct icp_qat_fw_loader_handle*) ; 
 scalar_t__ qat_hal_wait_cycles (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_wr_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_wr_indr_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int qat_hal_clr_reset(struct icp_qat_fw_loader_handle *handle)
{
	unsigned int ae_reset_csr;
	unsigned char ae;
	unsigned int clk_csr;
	unsigned int times = 100;
	unsigned int csr;

	/* write to the reset csr */
	ae_reset_csr = GET_GLB_CSR(handle, ICP_RESET);
	ae_reset_csr &= ~(handle->hal_handle->ae_mask << RST_CSR_AE_LSB);
	ae_reset_csr &= ~(handle->hal_handle->slice_mask << RST_CSR_QAT_LSB);
	do {
		SET_GLB_CSR(handle, ICP_RESET, ae_reset_csr);
		if (!(times--))
			goto out_err;
		csr = GET_GLB_CSR(handle, ICP_RESET);
	} while ((handle->hal_handle->ae_mask |
		 (handle->hal_handle->slice_mask << RST_CSR_QAT_LSB)) & csr);
	/* enable clock */
	clk_csr = GET_GLB_CSR(handle, ICP_GLOBAL_CLK_ENABLE);
	clk_csr |= handle->hal_handle->ae_mask << 0;
	clk_csr |= handle->hal_handle->slice_mask << 20;
	SET_GLB_CSR(handle, ICP_GLOBAL_CLK_ENABLE, clk_csr);
	if (qat_hal_check_ae_alive(handle))
		goto out_err;

	/* Set undefined power-up/reset states to reasonable default values */
	for (ae = 0; ae < handle->hal_handle->ae_max_num; ae++) {
		qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES,
				  INIT_CTX_ENABLE_VALUE);
		qat_hal_wr_indr_csr(handle, ae, ICP_QAT_UCLO_AE_ALL_CTX,
				    CTX_STS_INDIRECT,
				    handle->hal_handle->upc_mask &
				    INIT_PC_VALUE);
		qat_hal_wr_ae_csr(handle, ae, CTX_ARB_CNTL, INIT_CTX_ARB_VALUE);
		qat_hal_wr_ae_csr(handle, ae, CC_ENABLE, INIT_CCENABLE_VALUE);
		qat_hal_put_wakeup_event(handle, ae,
					 ICP_QAT_UCLO_AE_ALL_CTX,
					 INIT_WAKEUP_EVENTS_VALUE);
		qat_hal_put_sig_event(handle, ae,
				      ICP_QAT_UCLO_AE_ALL_CTX,
				      INIT_SIG_EVENTS_VALUE);
	}
	if (qat_hal_init_esram(handle))
		goto out_err;
	if (qat_hal_wait_cycles(handle, 0, SHRAM_INIT_CYCLES, 0))
		goto out_err;
	qat_hal_reset_timestamp(handle);

	return 0;
out_err:
	pr_err("QAT: failed to get device out of reset\n");
	return -EFAULT;
}