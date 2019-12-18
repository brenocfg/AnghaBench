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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_CR_PAT ; 
 int /*<<< orphan*/  X86_FEATURE_PAT ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pat_ap_init(u64 pat)
{
	if (!boot_cpu_has(X86_FEATURE_PAT)) {
		/*
		 * If this happens we are on a secondary CPU, but switched to
		 * PAT on the boot CPU. We have no way to undo PAT.
		 */
		panic("x86/PAT: PAT enabled, but not supported by secondary CPU\n");
	}

	wrmsrl(MSR_IA32_CR_PAT, pat);
}