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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_ACX ; 
 int /*<<< orphan*/  PT_BVADDR ; 
 int /*<<< orphan*/  PT_CAUSE ; 
 int /*<<< orphan*/  PT_EPC ; 
 int /*<<< orphan*/  PT_HI ; 
 int /*<<< orphan*/  PT_LO ; 
 int /*<<< orphan*/  PT_MPL ; 
 int /*<<< orphan*/  PT_MTP ; 
 int /*<<< orphan*/  PT_R0 ; 
 int /*<<< orphan*/  PT_R1 ; 
 int /*<<< orphan*/  PT_R10 ; 
 int /*<<< orphan*/  PT_R11 ; 
 int /*<<< orphan*/  PT_R12 ; 
 int /*<<< orphan*/  PT_R13 ; 
 int /*<<< orphan*/  PT_R14 ; 
 int /*<<< orphan*/  PT_R15 ; 
 int /*<<< orphan*/  PT_R16 ; 
 int /*<<< orphan*/  PT_R17 ; 
 int /*<<< orphan*/  PT_R18 ; 
 int /*<<< orphan*/  PT_R19 ; 
 int /*<<< orphan*/  PT_R2 ; 
 int /*<<< orphan*/  PT_R20 ; 
 int /*<<< orphan*/  PT_R21 ; 
 int /*<<< orphan*/  PT_R22 ; 
 int /*<<< orphan*/  PT_R23 ; 
 int /*<<< orphan*/  PT_R24 ; 
 int /*<<< orphan*/  PT_R25 ; 
 int /*<<< orphan*/  PT_R26 ; 
 int /*<<< orphan*/  PT_R27 ; 
 int /*<<< orphan*/  PT_R28 ; 
 int /*<<< orphan*/  PT_R29 ; 
 int /*<<< orphan*/  PT_R3 ; 
 int /*<<< orphan*/  PT_R30 ; 
 int /*<<< orphan*/  PT_R31 ; 
 int /*<<< orphan*/  PT_R4 ; 
 int /*<<< orphan*/  PT_R5 ; 
 int /*<<< orphan*/  PT_R6 ; 
 int /*<<< orphan*/  PT_R7 ; 
 int /*<<< orphan*/  PT_R8 ; 
 int /*<<< orphan*/  PT_R9 ; 
 int /*<<< orphan*/  PT_SIZE ; 
 int /*<<< orphan*/  PT_STATUS ; 
 int /*<<< orphan*/  acx ; 
 int /*<<< orphan*/  cp0_badvaddr ; 
 int /*<<< orphan*/  cp0_cause ; 
 int /*<<< orphan*/  cp0_epc ; 
 int /*<<< orphan*/  cp0_status ; 
 int /*<<< orphan*/  hi ; 
 int /*<<< orphan*/  lo ; 
 int /*<<< orphan*/  mpl ; 
 int /*<<< orphan*/  mtp ; 
 int /*<<< orphan*/  pt_regs ; 
 int /*<<< orphan*/ * regs ; 

void output_ptreg_defines(void)
{
	COMMENT("MIPS pt_regs offsets.");
	OFFSET(PT_R0, pt_regs, regs[0]);
	OFFSET(PT_R1, pt_regs, regs[1]);
	OFFSET(PT_R2, pt_regs, regs[2]);
	OFFSET(PT_R3, pt_regs, regs[3]);
	OFFSET(PT_R4, pt_regs, regs[4]);
	OFFSET(PT_R5, pt_regs, regs[5]);
	OFFSET(PT_R6, pt_regs, regs[6]);
	OFFSET(PT_R7, pt_regs, regs[7]);
	OFFSET(PT_R8, pt_regs, regs[8]);
	OFFSET(PT_R9, pt_regs, regs[9]);
	OFFSET(PT_R10, pt_regs, regs[10]);
	OFFSET(PT_R11, pt_regs, regs[11]);
	OFFSET(PT_R12, pt_regs, regs[12]);
	OFFSET(PT_R13, pt_regs, regs[13]);
	OFFSET(PT_R14, pt_regs, regs[14]);
	OFFSET(PT_R15, pt_regs, regs[15]);
	OFFSET(PT_R16, pt_regs, regs[16]);
	OFFSET(PT_R17, pt_regs, regs[17]);
	OFFSET(PT_R18, pt_regs, regs[18]);
	OFFSET(PT_R19, pt_regs, regs[19]);
	OFFSET(PT_R20, pt_regs, regs[20]);
	OFFSET(PT_R21, pt_regs, regs[21]);
	OFFSET(PT_R22, pt_regs, regs[22]);
	OFFSET(PT_R23, pt_regs, regs[23]);
	OFFSET(PT_R24, pt_regs, regs[24]);
	OFFSET(PT_R25, pt_regs, regs[25]);
	OFFSET(PT_R26, pt_regs, regs[26]);
	OFFSET(PT_R27, pt_regs, regs[27]);
	OFFSET(PT_R28, pt_regs, regs[28]);
	OFFSET(PT_R29, pt_regs, regs[29]);
	OFFSET(PT_R30, pt_regs, regs[30]);
	OFFSET(PT_R31, pt_regs, regs[31]);
	OFFSET(PT_LO, pt_regs, lo);
	OFFSET(PT_HI, pt_regs, hi);
#ifdef CONFIG_CPU_HAS_SMARTMIPS
	OFFSET(PT_ACX, pt_regs, acx);
#endif
	OFFSET(PT_EPC, pt_regs, cp0_epc);
	OFFSET(PT_BVADDR, pt_regs, cp0_badvaddr);
	OFFSET(PT_STATUS, pt_regs, cp0_status);
	OFFSET(PT_CAUSE, pt_regs, cp0_cause);
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	OFFSET(PT_MPL, pt_regs, mpl);
	OFFSET(PT_MTP, pt_regs, mtp);
#endif /* CONFIG_CPU_CAVIUM_OCTEON */
	DEFINE(PT_SIZE, sizeof(struct pt_regs));
	BLANK();
}