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
 unsigned int CSR_RETRY_TIMES ; 
 int EFAULT ; 
 int GET_AE_CSR (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 
 int LCS_STATUS ; 
 int /*<<< orphan*/  LOCAL_CSR_STATUS ; 
 int /*<<< orphan*/  SET_AE_CSR (struct icp_qat_fw_loader_handle*,unsigned char,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int qat_hal_wr_ae_csr(struct icp_qat_fw_loader_handle *handle,
			     unsigned char ae, unsigned int csr,
			     unsigned int value)
{
	unsigned int iterations = CSR_RETRY_TIMES;

	do {
		SET_AE_CSR(handle, ae, csr, value);
		if (!(GET_AE_CSR(handle, ae, LOCAL_CSR_STATUS) & LCS_STATUS))
			return 0;
	} while (iterations--);

	pr_err("QAT: Write CSR Timeout\n");
	return -EFAULT;
}