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
struct fsl_edma_hw_tcd {void* csr; void* biter; void* dlast_sga; void* doff; void* citer; void* slast; void* nbytes; void* soff; void* attr; void* daddr; void* saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDMA_TCD_BITER_BITER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDMA_TCD_CITER_CITER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDMA_TCD_CSR_D_REQ ; 
 int /*<<< orphan*/  EDMA_TCD_CSR_E_SG ; 
 int /*<<< orphan*/  EDMA_TCD_CSR_INT_MAJOR ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void fsl_edma_fill_tcd(struct fsl_edma_hw_tcd *tcd, u32 src, u32 dst,
		       u16 attr, u16 soff, u32 nbytes, u32 slast, u16 citer,
		       u16 biter, u16 doff, u32 dlast_sga, bool major_int,
		       bool disable_req, bool enable_sg)
{
	u16 csr = 0;

	/*
	 * eDMA hardware SGs require the TCDs to be stored in little
	 * endian format irrespective of the register endian model.
	 * So we put the value in little endian in memory, waiting
	 * for fsl_edma_set_tcd_regs doing the swap.
	 */
	tcd->saddr = cpu_to_le32(src);
	tcd->daddr = cpu_to_le32(dst);

	tcd->attr = cpu_to_le16(attr);

	tcd->soff = cpu_to_le16(soff);

	tcd->nbytes = cpu_to_le32(nbytes);
	tcd->slast = cpu_to_le32(slast);

	tcd->citer = cpu_to_le16(EDMA_TCD_CITER_CITER(citer));
	tcd->doff = cpu_to_le16(doff);

	tcd->dlast_sga = cpu_to_le32(dlast_sga);

	tcd->biter = cpu_to_le16(EDMA_TCD_BITER_BITER(biter));
	if (major_int)
		csr |= EDMA_TCD_CSR_INT_MAJOR;

	if (disable_req)
		csr |= EDMA_TCD_CSR_D_REQ;

	if (enable_sg)
		csr |= EDMA_TCD_CSR_E_SG;

	tcd->csr = cpu_to_le16(csr);
}