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
 int APIC_LVT_CMCI ; 
 int APIC_LVT_PMC ; 
 int APIC_VER_MAXLVT ; 
 int CPUID2_X2APIC ; 
 scalar_t__ LAPIC_DFR ; 
 scalar_t__ LAPIC_EXT_LVT0 ; 
 scalar_t__ LAPIC_ID ; 
 scalar_t__ LAPIC_LDR ; 
 scalar_t__ LAPIC_LVT_CMCI ; 
 scalar_t__ LAPIC_LVT_ERROR ; 
 scalar_t__ LAPIC_LVT_LINT0 ; 
 scalar_t__ LAPIC_LVT_LINT1 ; 
 scalar_t__ LAPIC_LVT_PCINT ; 
 scalar_t__ LAPIC_LVT_THERMAL ; 
 scalar_t__ LAPIC_LVT_TIMER ; 
 scalar_t__ LAPIC_SVR ; 
 scalar_t__ LAPIC_TPR ; 
 scalar_t__ LAPIC_VERSION ; 
 int MAXLVTSHIFT ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 int amd_read_elvt_count () ; 
 int amd_read_ext_features () ; 
 int cpu_feature2 ; 
 int /*<<< orphan*/  cpuid ; 
 int lapic_read32 (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int x2apic_mode ; 

__attribute__((used)) static void
native_lapic_dump(const char* str)
{
	uint32_t version;
	uint32_t maxlvt;
	uint32_t extf;
	int elvt_count;
	int i;

	version = lapic_read32(LAPIC_VERSION);
	maxlvt = (version & APIC_VER_MAXLVT) >> MAXLVTSHIFT;
	printf("cpu%d %s:\n", PCPU_GET(cpuid), str);
	printf("     ID: 0x%08x   VER: 0x%08x LDR: 0x%08x DFR: 0x%08x",
	    lapic_read32(LAPIC_ID), version,
	    lapic_read32(LAPIC_LDR), x2apic_mode ? 0 : lapic_read32(LAPIC_DFR));
	if ((cpu_feature2 & CPUID2_X2APIC) != 0)
		printf(" x2APIC: %d", x2apic_mode);
	printf("\n  lint0: 0x%08x lint1: 0x%08x TPR: 0x%08x SVR: 0x%08x\n",
	    lapic_read32(LAPIC_LVT_LINT0), lapic_read32(LAPIC_LVT_LINT1),
	    lapic_read32(LAPIC_TPR), lapic_read32(LAPIC_SVR));
	printf("  timer: 0x%08x therm: 0x%08x err: 0x%08x",
	    lapic_read32(LAPIC_LVT_TIMER), lapic_read32(LAPIC_LVT_THERMAL),
	    lapic_read32(LAPIC_LVT_ERROR));
	if (maxlvt >= APIC_LVT_PMC)
		printf(" pmc: 0x%08x", lapic_read32(LAPIC_LVT_PCINT));
	printf("\n");
	if (maxlvt >= APIC_LVT_CMCI)
		printf("   cmci: 0x%08x\n", lapic_read32(LAPIC_LVT_CMCI));
	extf = amd_read_ext_features();
	if (extf != 0) {
		printf("   AMD ext features: 0x%08x\n", extf);
		elvt_count = amd_read_elvt_count();
		for (i = 0; i < elvt_count; i++)
			printf("   AMD elvt%d: 0x%08x\n", i,
			    lapic_read32(LAPIC_EXT_LVT0 + i));
	}
}