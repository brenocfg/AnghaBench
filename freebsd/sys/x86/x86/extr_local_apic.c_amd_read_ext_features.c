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
typedef  int uint32_t ;

/* Variables and functions */
 int APIC_VER_AMD_EXT_SPACE ; 
 scalar_t__ CPU_VENDOR_AMD ; 
 int /*<<< orphan*/  LAPIC_EXT_FEATURES ; 
 int /*<<< orphan*/  LAPIC_VERSION ; 
 scalar_t__ cpu_vendor_id ; 
 int lapic_read32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
amd_read_ext_features(void)
{
	uint32_t version;

	if (cpu_vendor_id != CPU_VENDOR_AMD)
		return (0);
	version = lapic_read32(LAPIC_VERSION);
	if ((version & APIC_VER_AMD_EXT_SPACE) != 0)
		return (lapic_read32(LAPIC_EXT_FEATURES));
	else
		return (0);
}