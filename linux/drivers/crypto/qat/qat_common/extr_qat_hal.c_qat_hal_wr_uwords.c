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
typedef  int uint64_t ;
struct icp_qat_fw_loader_handle {int dummy; } ;

/* Variables and functions */
 unsigned int UA_ECS ; 
 int /*<<< orphan*/  USTORE_ADDRESS ; 
 int /*<<< orphan*/  USTORE_DATA_LOWER ; 
 int /*<<< orphan*/  USTORE_DATA_UPPER ; 
 unsigned int qat_hal_rd_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ) ; 
 int qat_hal_set_uword_ecc (int) ; 
 int /*<<< orphan*/  qat_hal_wr_ae_csr (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,unsigned int) ; 

void qat_hal_wr_uwords(struct icp_qat_fw_loader_handle *handle,
		       unsigned char ae, unsigned int uaddr,
		       unsigned int words_num, uint64_t *uword)
{
	unsigned int ustore_addr;
	unsigned int i;

	ustore_addr = qat_hal_rd_ae_csr(handle, ae, USTORE_ADDRESS);
	uaddr |= UA_ECS;
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, uaddr);
	for (i = 0; i < words_num; i++) {
		unsigned int uwrd_lo, uwrd_hi;
		uint64_t tmp;

		tmp = qat_hal_set_uword_ecc(uword[i]);
		uwrd_lo = (unsigned int)(tmp & 0xffffffff);
		uwrd_hi = (unsigned int)(tmp >> 0x20);
		qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_LOWER, uwrd_lo);
		qat_hal_wr_ae_csr(handle, ae, USTORE_DATA_UPPER, uwrd_hi);
	}
	qat_hal_wr_ae_csr(handle, ae, USTORE_ADDRESS, ustore_addr);
}