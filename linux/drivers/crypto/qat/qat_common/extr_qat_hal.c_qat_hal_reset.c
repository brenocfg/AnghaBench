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
struct TYPE_2__ {unsigned int ae_mask; unsigned int slice_mask; } ;

/* Variables and functions */
 unsigned int GET_GLB_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_RESET ; 
 unsigned int RST_CSR_AE_LSB ; 
 unsigned int RST_CSR_QAT_LSB ; 
 int /*<<< orphan*/  SET_GLB_CSR (struct icp_qat_fw_loader_handle*,int /*<<< orphan*/ ,unsigned int) ; 

void qat_hal_reset(struct icp_qat_fw_loader_handle *handle)
{
	unsigned int ae_reset_csr;

	ae_reset_csr = GET_GLB_CSR(handle, ICP_RESET);
	ae_reset_csr |= handle->hal_handle->ae_mask << RST_CSR_AE_LSB;
	ae_reset_csr |= handle->hal_handle->slice_mask << RST_CSR_QAT_LSB;
	SET_GLB_CSR(handle, ICP_RESET, ae_reset_csr);
}