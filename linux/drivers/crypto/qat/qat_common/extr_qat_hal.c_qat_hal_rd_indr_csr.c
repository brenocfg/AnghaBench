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
struct icp_qat_fw_loader_handle {int dummy; } ;

/* Variables and functions */
 unsigned int CSR_CTX_POINTER ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  qat_hal_wr_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int qat_hal_rd_indr_csr(struct icp_qat_fw_loader_handle *handle,
				unsigned char ae, unsigned char ctx,
				unsigned int ae_csr)
{
	unsigned int cur_ctx, csr_val;

	cur_ctx = qat_hal_rd_ae_csr(handle, ae, CSR_CTX_POINTER);
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, ctx);
	csr_val = qat_hal_rd_ae_csr(handle, ae, ae_csr);
	qat_hal_wr_ae_csr(handle, ae, CSR_CTX_POINTER, cur_ctx);

	return csr_val;
}