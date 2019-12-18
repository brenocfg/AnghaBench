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
struct cpuinfo_mips {int processor_id; int options; int /*<<< orphan*/  cputype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BMIPS32 ; 
 int /*<<< orphan*/  CPU_BMIPS3300 ; 
 int /*<<< orphan*/  CPU_BMIPS4350 ; 
 int /*<<< orphan*/  CPU_BMIPS4380 ; 
 int /*<<< orphan*/  CPU_BMIPS5000 ; 
 int MIPS_CPU_RIXI ; 
 int MIPS_CPU_ULRI ; 
#define  PRID_IMP_BMIPS32_REV4 135 
#define  PRID_IMP_BMIPS32_REV8 134 
#define  PRID_IMP_BMIPS3300 133 
#define  PRID_IMP_BMIPS3300_ALT 132 
#define  PRID_IMP_BMIPS3300_BUG 131 
#define  PRID_IMP_BMIPS43XX 130 
#define  PRID_IMP_BMIPS5000 129 
#define  PRID_IMP_BMIPS5200 128 
 int PRID_IMP_MASK ; 
 int PRID_REV_BMIPS4380_HI ; 
 int PRID_REV_BMIPS4380_LO ; 
 int PRID_REV_MASK ; 
 char** __cpu_name ; 
 int /*<<< orphan*/  decode_configs (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  set_elf_platform (unsigned int,char*) ; 

__attribute__((used)) static inline void cpu_probe_broadcom(struct cpuinfo_mips *c, unsigned int cpu)
{
	decode_configs(c);
	switch (c->processor_id & PRID_IMP_MASK) {
	case PRID_IMP_BMIPS32_REV4:
	case PRID_IMP_BMIPS32_REV8:
		c->cputype = CPU_BMIPS32;
		__cpu_name[cpu] = "Broadcom BMIPS32";
		set_elf_platform(cpu, "bmips32");
		break;
	case PRID_IMP_BMIPS3300:
	case PRID_IMP_BMIPS3300_ALT:
	case PRID_IMP_BMIPS3300_BUG:
		c->cputype = CPU_BMIPS3300;
		__cpu_name[cpu] = "Broadcom BMIPS3300";
		set_elf_platform(cpu, "bmips3300");
		break;
	case PRID_IMP_BMIPS43XX: {
		int rev = c->processor_id & PRID_REV_MASK;

		if (rev >= PRID_REV_BMIPS4380_LO &&
				rev <= PRID_REV_BMIPS4380_HI) {
			c->cputype = CPU_BMIPS4380;
			__cpu_name[cpu] = "Broadcom BMIPS4380";
			set_elf_platform(cpu, "bmips4380");
			c->options |= MIPS_CPU_RIXI;
		} else {
			c->cputype = CPU_BMIPS4350;
			__cpu_name[cpu] = "Broadcom BMIPS4350";
			set_elf_platform(cpu, "bmips4350");
		}
		break;
	}
	case PRID_IMP_BMIPS5000:
	case PRID_IMP_BMIPS5200:
		c->cputype = CPU_BMIPS5000;
		if ((c->processor_id & PRID_IMP_MASK) == PRID_IMP_BMIPS5200)
			__cpu_name[cpu] = "Broadcom BMIPS5200";
		else
			__cpu_name[cpu] = "Broadcom BMIPS5000";
		set_elf_platform(cpu, "bmips5000");
		c->options |= MIPS_CPU_ULRI | MIPS_CPU_RIXI;
		break;
	}
}