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
struct cpuinfo_x86 {int /*<<< orphan*/ * x86_capability; } ;

/* Variables and functions */
 size_t CPUID_8086_0001_EDX ; 
 int cpuid_eax (int) ; 
 int /*<<< orphan*/  cpuid_edx (int) ; 

__attribute__((used)) static void early_init_transmeta(struct cpuinfo_x86 *c)
{
	u32 xlvl;

	/* Transmeta-defined flags: level 0x80860001 */
	xlvl = cpuid_eax(0x80860000);
	if ((xlvl & 0xffff0000) == 0x80860000) {
		if (xlvl >= 0x80860001)
			c->x86_capability[CPUID_8086_0001_EDX] = cpuid_edx(0x80860001);
	}
}