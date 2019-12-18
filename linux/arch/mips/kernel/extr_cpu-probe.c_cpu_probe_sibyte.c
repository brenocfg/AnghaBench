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
struct cpuinfo_mips {int processor_id; int options; int /*<<< orphan*/  cputype; int /*<<< orphan*/  writecombine; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SB1 ; 
 int /*<<< orphan*/  CPU_SB1A ; 
 int MIPS_CPU_32FPR ; 
 int MIPS_CPU_FPU ; 
 int PRID_IMP_MASK ; 
#define  PRID_IMP_SB1 129 
#define  PRID_IMP_SB1A 128 
 int PRID_REV_MASK ; 
 int /*<<< orphan*/  _CACHE_UNCACHED_ACCELERATED ; 
 char** __cpu_name ; 
 int /*<<< orphan*/  decode_configs (struct cpuinfo_mips*) ; 

__attribute__((used)) static inline void cpu_probe_sibyte(struct cpuinfo_mips *c, unsigned int cpu)
{
	decode_configs(c);

	c->writecombine = _CACHE_UNCACHED_ACCELERATED;
	switch (c->processor_id & PRID_IMP_MASK) {
	case PRID_IMP_SB1:
		c->cputype = CPU_SB1;
		__cpu_name[cpu] = "SiByte SB1";
		/* FPU in pass1 is known to have issues. */
		if ((c->processor_id & PRID_REV_MASK) < 0x02)
			c->options &= ~(MIPS_CPU_FPU | MIPS_CPU_32FPR);
		break;
	case PRID_IMP_SB1A:
		c->cputype = CPU_SB1A;
		__cpu_name[cpu] = "SiByte SB1A";
		break;
	}
}