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
typedef  int u64 ;
struct vas_window {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMR ; 
 int LPCR_ISL ; 
 int LPCR_TC ; 
 int /*<<< orphan*/  SEIDR ; 
 int SET_FIELD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SPRN_AMR ; 
 int /*<<< orphan*/  SPRN_LPCR ; 
 int /*<<< orphan*/  VAS_AMR ; 
 int /*<<< orphan*/  VAS_SEIDR ; 
 int /*<<< orphan*/  VAS_XLATE_LPCR_ISL ; 
 int /*<<< orphan*/  VAS_XLATE_LPCR_PAGE_SIZE ; 
 int /*<<< orphan*/  VAS_XLATE_LPCR_SC ; 
 int /*<<< orphan*/  VAS_XLATE_LPCR_TC ; 
 int /*<<< orphan*/  VAS_XLATE_MODE ; 
 int /*<<< orphan*/  VAS_XLATE_MSR_DR ; 
 int /*<<< orphan*/  VAS_XLATE_MSR_HV ; 
 int /*<<< orphan*/  VAS_XLATE_MSR_PR ; 
 int /*<<< orphan*/  VAS_XLATE_MSR_SF ; 
 int /*<<< orphan*/  VREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLATE_CTL ; 
 int /*<<< orphan*/  XLATE_LPCR ; 
 int /*<<< orphan*/  XLATE_MSR ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 scalar_t__ radix_enabled () ; 
 int /*<<< orphan*/  write_hvwc_reg (struct vas_window*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_xlate_regs(struct vas_window *window, bool user_win)
{
	u64 lpcr, val;

	/*
	 * MSR_TA, MSR_US are false for both kernel and user.
	 * MSR_DR and MSR_PR are false for kernel.
	 */
	val = 0ULL;
	val = SET_FIELD(VAS_XLATE_MSR_HV, val, 1);
	val = SET_FIELD(VAS_XLATE_MSR_SF, val, 1);
	if (user_win) {
		val = SET_FIELD(VAS_XLATE_MSR_DR, val, 1);
		val = SET_FIELD(VAS_XLATE_MSR_PR, val, 1);
	}
	write_hvwc_reg(window, VREG(XLATE_MSR), val);

	lpcr = mfspr(SPRN_LPCR);
	val = 0ULL;
	/*
	 * NOTE: From Section 5.7.8.1 Segment Lookaside Buffer of the
	 *	 Power ISA, v3.0B, Page size encoding is 0 = 4KB, 5 = 64KB.
	 *
	 * NOTE: From Section 1.3.1, Address Translation Context of the
	 *	 Nest MMU Workbook, LPCR_SC should be 0 for Power9.
	 */
	val = SET_FIELD(VAS_XLATE_LPCR_PAGE_SIZE, val, 5);
	val = SET_FIELD(VAS_XLATE_LPCR_ISL, val, lpcr & LPCR_ISL);
	val = SET_FIELD(VAS_XLATE_LPCR_TC, val, lpcr & LPCR_TC);
	val = SET_FIELD(VAS_XLATE_LPCR_SC, val, 0);
	write_hvwc_reg(window, VREG(XLATE_LPCR), val);

	/*
	 * Section 1.3.1 (Address translation Context) of NMMU workbook.
	 *	0b00	Hashed Page Table mode
	 *	0b01	Reserved
	 *	0b10	Radix on HPT
	 *	0b11	Radix on Radix
	 */
	val = 0ULL;
	val = SET_FIELD(VAS_XLATE_MODE, val, radix_enabled() ? 3 : 2);
	write_hvwc_reg(window, VREG(XLATE_CTL), val);

	/*
	 * TODO: Can we mfspr(AMR) even for user windows?
	 */
	val = 0ULL;
	val = SET_FIELD(VAS_AMR, val, mfspr(SPRN_AMR));
	write_hvwc_reg(window, VREG(AMR), val);

	val = 0ULL;
	val = SET_FIELD(VAS_SEIDR, val, 0);
	write_hvwc_reg(window, VREG(SEIDR), val);
}