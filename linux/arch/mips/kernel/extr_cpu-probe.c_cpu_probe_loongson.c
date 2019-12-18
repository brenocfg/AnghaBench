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
struct cpuinfo_mips {int processor_id; int options; int ases; int /*<<< orphan*/  writecombine; void* cputype; } ;

/* Variables and functions */
 void* CPU_LOONGSON3 ; 
 int MIPS_ASE_LOONGSON_CAM ; 
 int MIPS_ASE_LOONGSON_EXT ; 
 int MIPS_ASE_LOONGSON_EXT2 ; 
 int MIPS_ASE_LOONGSON_MMI ; 
 int MIPS_CPU_FTLB ; 
 int /*<<< orphan*/  MIPS_CPU_ISA_M64R2 ; 
 int MIPS_CPU_LDPTE ; 
 int MIPS_CPU_TLBINV ; 
#define  PRID_IMP_LOONGSON_64 132 
 int PRID_IMP_MASK ; 
#define  PRID_REV_LOONGSON3A_R2_0 131 
#define  PRID_REV_LOONGSON3A_R2_1 130 
#define  PRID_REV_LOONGSON3A_R3_0 129 
#define  PRID_REV_LOONGSON3A_R3_1 128 
 int PRID_REV_MASK ; 
 int /*<<< orphan*/  _CACHE_UNCACHED_ACCELERATED ; 
 char** __cpu_name ; 
 int /*<<< orphan*/  decode_configs (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  set_elf_platform (unsigned int,char*) ; 
 int /*<<< orphan*/  set_isa (struct cpuinfo_mips*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cpu_probe_loongson(struct cpuinfo_mips *c, unsigned int cpu)
{
	switch (c->processor_id & PRID_IMP_MASK) {
	case PRID_IMP_LOONGSON_64:  /* Loongson-2/3 */
		switch (c->processor_id & PRID_REV_MASK) {
		case PRID_REV_LOONGSON3A_R2_0:
		case PRID_REV_LOONGSON3A_R2_1:
			c->cputype = CPU_LOONGSON3;
			__cpu_name[cpu] = "ICT Loongson-3";
			set_elf_platform(cpu, "loongson3a");
			set_isa(c, MIPS_CPU_ISA_M64R2);
			break;
		case PRID_REV_LOONGSON3A_R3_0:
		case PRID_REV_LOONGSON3A_R3_1:
			c->cputype = CPU_LOONGSON3;
			__cpu_name[cpu] = "ICT Loongson-3";
			set_elf_platform(cpu, "loongson3a");
			set_isa(c, MIPS_CPU_ISA_M64R2);
			break;
		}

		decode_configs(c);
		c->options |= MIPS_CPU_FTLB | MIPS_CPU_TLBINV | MIPS_CPU_LDPTE;
		c->writecombine = _CACHE_UNCACHED_ACCELERATED;
		c->ases |= (MIPS_ASE_LOONGSON_MMI | MIPS_ASE_LOONGSON_CAM |
			MIPS_ASE_LOONGSON_EXT | MIPS_ASE_LOONGSON_EXT2);
		break;
	default:
		panic("Unknown Loongson Processor ID!");
		break;
	}
}