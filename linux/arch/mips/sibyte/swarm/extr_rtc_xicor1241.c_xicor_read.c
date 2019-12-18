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
typedef  int uint8_t ;

/* Variables and functions */
 int M_SMB_BUSY ; 
 int M_SMB_ERROR ; 
 int /*<<< orphan*/  R_SMB_CMD ; 
 int /*<<< orphan*/  R_SMB_DATA ; 
 int /*<<< orphan*/  R_SMB_START ; 
 int /*<<< orphan*/  R_SMB_STATUS ; 
 int /*<<< orphan*/  SMB_CSR (int /*<<< orphan*/ ) ; 
 int V_SMB_ADDR (int /*<<< orphan*/ ) ; 
 int V_SMB_TT_RD1BYTE ; 
 int V_SMB_TT_WR2BYTE ; 
 int /*<<< orphan*/  X1241_CCR_ADDRESS ; 
 int __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xicor_read(uint8_t addr)
{
	while (__raw_readq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	__raw_writeq((addr >> 8) & 0x7, SMB_CSR(R_SMB_CMD));
	__raw_writeq(addr & 0xff, SMB_CSR(R_SMB_DATA));
	__raw_writeq(V_SMB_ADDR(X1241_CCR_ADDRESS) | V_SMB_TT_WR2BYTE,
		     SMB_CSR(R_SMB_START));

	while (__raw_readq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	__raw_writeq(V_SMB_ADDR(X1241_CCR_ADDRESS) | V_SMB_TT_RD1BYTE,
		     SMB_CSR(R_SMB_START));

	while (__raw_readq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	if (__raw_readq(SMB_CSR(R_SMB_STATUS)) & M_SMB_ERROR) {
		/* Clear error bit by writing a 1 */
		__raw_writeq(M_SMB_ERROR, SMB_CSR(R_SMB_STATUS));
		return -1;
	}

	return __raw_readq(SMB_CSR(R_SMB_DATA)) & 0xff;
}