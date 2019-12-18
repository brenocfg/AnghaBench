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
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 int CPUID_TO_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_id ; 

__attribute__((used)) static bool
nehalem_cpu(void)
{
	u_int family, model;

	/*
	 * The family:model numbers belonging to the Nehalem microarchitecture
	 * are documented in Section 35.5, Intel SDM dated Feb 2014.
	 */
	family = CPUID_TO_FAMILY(cpu_id);
	model = CPUID_TO_MODEL(cpu_id);
	if (family == 0x6) {
		switch (model) {
		case 0x1A:
		case 0x1E:
		case 0x1F:
		case 0x2E:
			return (true);
		default:
			break;
		}
	}
	return (false);
}