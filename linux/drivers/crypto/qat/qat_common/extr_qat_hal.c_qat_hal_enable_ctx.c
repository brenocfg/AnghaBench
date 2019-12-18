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
 unsigned int CE_ENABLE_BITPOS ; 
 unsigned int CE_INUSE_CONTEXTS ; 
 int /*<<< orphan*/  CTX_ENABLES ; 
 unsigned int IGNORE_W1C_MASK ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qat_hal_wr_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void qat_hal_enable_ctx(struct icp_qat_fw_loader_handle *handle,
			       unsigned char ae, unsigned int ctx_mask)
{
	unsigned int ctx;

	ctx = qat_hal_rd_ae_csr(handle, ae, CTX_ENABLES);
	ctx &= IGNORE_W1C_MASK;
	ctx_mask &= (ctx & CE_INUSE_CONTEXTS) ? 0x55 : 0xFF;
	ctx |= (ctx_mask << CE_ENABLE_BITPOS);
	qat_hal_wr_ae_csr(handle, ae, CTX_ENABLES, ctx);
}