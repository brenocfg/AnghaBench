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
typedef  int u_int ;

/* Variables and functions */
 int VIA_CPUID_DO_RNG ; 
 int VIA_CPUID_HAS_ACE ; 
 int VIA_CPUID_HAS_ACE2 ; 
 int VIA_CPUID_HAS_PHE ; 
 int VIA_CPUID_HAS_PMM ; 
 int VIA_CPUID_HAS_RNG ; 
 int /*<<< orphan*/  VIA_HAS_AES ; 
 int /*<<< orphan*/  VIA_HAS_AESCTR ; 
 int /*<<< orphan*/  VIA_HAS_MM ; 
 int /*<<< orphan*/  VIA_HAS_RNG ; 
 int /*<<< orphan*/  VIA_HAS_SHA ; 
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 int rdmsr (int) ; 
 int /*<<< orphan*/  via_feature_rng ; 
 int /*<<< orphan*/  via_feature_xcrypt ; 
 int /*<<< orphan*/  wrmsr (int,int) ; 

__attribute__((used)) static void
init_via(void)
{
	u_int regs[4], val;

	/*
	 * Check extended CPUID for PadLock features.
	 *
	 * http://www.via.com.tw/en/downloads/whitepapers/initiatives/padlock/programming_guide.pdf
	 */
	do_cpuid(0xc0000000, regs);
	if (regs[0] >= 0xc0000001) {
		do_cpuid(0xc0000001, regs);
		val = regs[3];
	} else
		return;

	/* Enable RNG if present. */
	if ((val & VIA_CPUID_HAS_RNG) != 0) {
		via_feature_rng = VIA_HAS_RNG;
		wrmsr(0x110B, rdmsr(0x110B) | VIA_CPUID_DO_RNG);
	}

	/* Enable PadLock if present. */
	if ((val & VIA_CPUID_HAS_ACE) != 0)
		via_feature_xcrypt |= VIA_HAS_AES;
	if ((val & VIA_CPUID_HAS_ACE2) != 0)
		via_feature_xcrypt |= VIA_HAS_AESCTR;
	if ((val & VIA_CPUID_HAS_PHE) != 0)
		via_feature_xcrypt |= VIA_HAS_SHA;
	if ((val & VIA_CPUID_HAS_PMM) != 0)
		via_feature_xcrypt |= VIA_HAS_MM;
	if (via_feature_xcrypt != 0)
		wrmsr(0x1107, rdmsr(0x1107) | (1 << 28));
}