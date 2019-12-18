#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int extended_cpuid_level; int x86_phys_bits; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  X86_FEATURE_TME ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int cpuid_eax (int) ; 

__attribute__((used)) static u8 kvm_get_shadow_phys_bits(void)
{
	/*
	 * boot_cpu_data.x86_phys_bits is reduced when MKTME is detected
	 * in CPU detection code, but MKTME treats those reduced bits as
	 * 'keyID' thus they are not reserved bits. Therefore for MKTME
	 * we should still return physical address bits reported by CPUID.
	 */
	if (!boot_cpu_has(X86_FEATURE_TME) ||
	    WARN_ON_ONCE(boot_cpu_data.extended_cpuid_level < 0x80000008))
		return boot_cpu_data.x86_phys_bits;

	return cpuid_eax(0x80000008) & 0xff;
}