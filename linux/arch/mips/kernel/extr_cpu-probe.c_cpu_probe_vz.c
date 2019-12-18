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
struct cpuinfo_mips {int dummy; } ;

/* Variables and functions */
 scalar_t__ cpu_has_guestctl1 ; 
 int /*<<< orphan*/  cpu_probe_gtoffset (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  cpu_probe_guestctl0 (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  cpu_probe_guestctl1 (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  decode_guest_configs (struct cpuinfo_mips*) ; 

__attribute__((used)) static inline void cpu_probe_vz(struct cpuinfo_mips *c)
{
	cpu_probe_guestctl0(c);
	if (cpu_has_guestctl1)
		cpu_probe_guestctl1(c);

	cpu_probe_gtoffset(c);

	decode_guest_configs(c);
}