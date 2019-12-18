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
 int CPUID_TYPE_CORE ; 
 int CPUID_TYPE_SMT ; 
 int core_id_shift ; 
 int /*<<< orphan*/  cpuid_count (int,int,int*) ; 
 int pkg_id_shift ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  topo_probe_intel_0x4 () ; 

__attribute__((used)) static void
topo_probe_intel_0xb(void)
{
	u_int p[4];
	int bits;
	int type;
	int i;

	/* Fall back if CPU leaf 11 doesn't really exist. */
	cpuid_count(0x0b, 0, p);
	if (p[1] == 0) {
		topo_probe_intel_0x4();
		return;
	}

	/* We only support three levels for now. */
	for (i = 0; ; i++) {
		cpuid_count(0x0b, i, p);

		bits = p[0] & 0x1f;
		type = (p[2] >> 8) & 0xff;

		if (type == 0)
			break;

		/* TODO: check for duplicate (re-)assignment */
		if (type == CPUID_TYPE_SMT)
			core_id_shift = bits;
		else if (type == CPUID_TYPE_CORE)
			pkg_id_shift = bits;
		else
			printf("unknown CPU level type %d\n", type);
	}

	if (pkg_id_shift < core_id_shift) {
		printf("WARNING: core covers more APIC IDs than a package\n");
		core_id_shift = pkg_id_shift;
	}
}