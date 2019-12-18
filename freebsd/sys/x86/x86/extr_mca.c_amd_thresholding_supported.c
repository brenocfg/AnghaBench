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

/* Variables and functions */
 int AMDRAS_SCALABLE_MCA ; 
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_VENDOR_AMD ; 
 int amd_rascap ; 
 int /*<<< orphan*/  cpu_id ; 
 scalar_t__ cpu_vendor_id ; 

__attribute__((used)) static inline bool
amd_thresholding_supported(void)
{
	if (cpu_vendor_id != CPU_VENDOR_AMD)
		return (false);
	/*
	 * The RASCap register is wholly reserved in families 0x10-0x15 (through model 1F).
	 *
	 * It begins to be documented in family 0x15 model 30 and family 0x16,
	 * but neither of these families documents the ScalableMca bit, which
	 * supposedly defines the presence of this feature on family 0x17.
	 */
	if (CPUID_TO_FAMILY(cpu_id) >= 0x10 && CPUID_TO_FAMILY(cpu_id) <= 0x16)
		return (true);
	if (CPUID_TO_FAMILY(cpu_id) >= 0x17)
		return ((amd_rascap & AMDRAS_SCALABLE_MCA) != 0);
	return (false);
}