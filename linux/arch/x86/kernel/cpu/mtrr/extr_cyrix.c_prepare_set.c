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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CX86_CCR3 ; 
 int X86_CR0_CD ; 
 int X86_CR4_PGE ; 
 int /*<<< orphan*/  X86_FEATURE_PGE ; 
 int __read_cr4 () ; 
 int /*<<< orphan*/  __write_cr4 (int) ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int ccr3 ; 
 int cr4 ; 
 int getCx86 (int /*<<< orphan*/ ) ; 
 int read_cr0 () ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  write_cr0 (int) ; 

__attribute__((used)) static void prepare_set(void)
{
	u32 cr0;

	/*  Save value of CR4 and clear Page Global Enable (bit 7)  */
	if (boot_cpu_has(X86_FEATURE_PGE)) {
		cr4 = __read_cr4();
		__write_cr4(cr4 & ~X86_CR4_PGE);
	}

	/*
	 * Disable and flush caches.
	 * Note that wbinvd flushes the TLBs as a side-effect
	 */
	cr0 = read_cr0() | X86_CR0_CD;
	wbinvd();
	write_cr0(cr0);
	wbinvd();

	/* Cyrix ARRs - everything else was excluded at the top */
	ccr3 = getCx86(CX86_CCR3);

	/* Cyrix ARRs - everything else was excluded at the top */
	setCx86(CX86_CCR3, (ccr3 & 0x0f) | 0x10);
}