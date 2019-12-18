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
struct cpuinfo_x86 {int x86_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_F15H_IC_CFG ; 
 int /*<<< orphan*/  clear_rdrand_cpuid_bit (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  rdmsrl_safe (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wrmsrl_safe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_amd_bd(struct cpuinfo_x86 *c)
{
	u64 value;

	/*
	 * The way access filter has a performance penalty on some workloads.
	 * Disable it on the affected CPUs.
	 */
	if ((c->x86_model >= 0x02) && (c->x86_model < 0x20)) {
		if (!rdmsrl_safe(MSR_F15H_IC_CFG, &value) && !(value & 0x1E)) {
			value |= 0x1E;
			wrmsrl_safe(MSR_F15H_IC_CFG, value);
		}
	}

	/*
	 * Some BIOS implementations do not restore proper RDRAND support
	 * across suspend and resume. Check on whether to hide the RDRAND
	 * instruction support via CPUID.
	 */
	clear_rdrand_cpuid_bit(c);
}