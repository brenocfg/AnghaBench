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
struct cpuinfo_mips {int processor_id; int cputype; int /*<<< orphan*/  options; void* writecombine; } ;

/* Variables and functions */
 int CPU_1004K ; 
 int CPU_1074K ; 
 int CPU_20KC ; 
 void* CPU_24K ; 
 int CPU_25KF ; 
 int CPU_34K ; 
 int CPU_4KC ; 
 int CPU_4KEC ; 
 int CPU_4KSC ; 
 int CPU_5KC ; 
 int CPU_5KE ; 
 int CPU_74K ; 
#define  CPU_I6400 157 
#define  CPU_I6500 156 
 void* CPU_INTERAPTIV ; 
 int CPU_M14KC ; 
 int CPU_M14KEC ; 
 int CPU_M5150 ; 
 int CPU_M6250 ; 
 int CPU_P5600 ; 
 int CPU_P6600 ; 
 void* CPU_PROAPTIV ; 
 int CPU_QEMU_GENERIC ; 
 int /*<<< orphan*/  MIPS_CPU_SHARED_FTLB_ENTRIES ; 
 int /*<<< orphan*/  MIPS_CPU_SHARED_FTLB_RAM ; 
#define  PRID_IMP_1004K 155 
#define  PRID_IMP_1074K 154 
#define  PRID_IMP_20KC 153 
#define  PRID_IMP_24K 152 
#define  PRID_IMP_24KE 151 
#define  PRID_IMP_25KF 150 
#define  PRID_IMP_34K 149 
#define  PRID_IMP_4KC 148 
#define  PRID_IMP_4KEC 147 
#define  PRID_IMP_4KECR2 146 
#define  PRID_IMP_4KSC 145 
#define  PRID_IMP_4KSD 144 
#define  PRID_IMP_5KC 143 
#define  PRID_IMP_5KE 142 
#define  PRID_IMP_74K 141 
#define  PRID_IMP_I6400 140 
#define  PRID_IMP_I6500 139 
#define  PRID_IMP_INTERAPTIV_MP 138 
#define  PRID_IMP_INTERAPTIV_UP 137 
#define  PRID_IMP_M14KC 136 
#define  PRID_IMP_M14KEC 135 
#define  PRID_IMP_M5150 134 
#define  PRID_IMP_M6250 133 
 int PRID_IMP_MASK ; 
#define  PRID_IMP_P5600 132 
#define  PRID_IMP_P6600 131 
#define  PRID_IMP_PROAPTIV_MP 130 
#define  PRID_IMP_PROAPTIV_UP 129 
#define  PRID_IMP_QEMU_GENERIC 128 
 void* _CACHE_UNCACHED ; 
 void* _CACHE_UNCACHED_ACCELERATED ; 
 char** __cpu_name ; 
 int __get_cpu_type (int) ; 
 int /*<<< orphan*/  cpu_set_mt_per_tc_perf (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  decode_configs (struct cpuinfo_mips*) ; 
 int /*<<< orphan*/  spram_config () ; 

__attribute__((used)) static inline void cpu_probe_mips(struct cpuinfo_mips *c, unsigned int cpu)
{
	c->writecombine = _CACHE_UNCACHED_ACCELERATED;
	switch (c->processor_id & PRID_IMP_MASK) {
	case PRID_IMP_QEMU_GENERIC:
		c->writecombine = _CACHE_UNCACHED;
		c->cputype = CPU_QEMU_GENERIC;
		__cpu_name[cpu] = "MIPS GENERIC QEMU";
		break;
	case PRID_IMP_4KC:
		c->cputype = CPU_4KC;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 4Kc";
		break;
	case PRID_IMP_4KEC:
	case PRID_IMP_4KECR2:
		c->cputype = CPU_4KEC;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 4KEc";
		break;
	case PRID_IMP_4KSC:
	case PRID_IMP_4KSD:
		c->cputype = CPU_4KSC;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 4KSc";
		break;
	case PRID_IMP_5KC:
		c->cputype = CPU_5KC;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 5Kc";
		break;
	case PRID_IMP_5KE:
		c->cputype = CPU_5KE;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 5KE";
		break;
	case PRID_IMP_20KC:
		c->cputype = CPU_20KC;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 20Kc";
		break;
	case PRID_IMP_24K:
		c->cputype = CPU_24K;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 24Kc";
		break;
	case PRID_IMP_24KE:
		c->cputype = CPU_24K;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 24KEc";
		break;
	case PRID_IMP_25KF:
		c->cputype = CPU_25KF;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 25Kc";
		break;
	case PRID_IMP_34K:
		c->cputype = CPU_34K;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 34Kc";
		cpu_set_mt_per_tc_perf(c);
		break;
	case PRID_IMP_74K:
		c->cputype = CPU_74K;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 74Kc";
		break;
	case PRID_IMP_M14KC:
		c->cputype = CPU_M14KC;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS M14Kc";
		break;
	case PRID_IMP_M14KEC:
		c->cputype = CPU_M14KEC;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS M14KEc";
		break;
	case PRID_IMP_1004K:
		c->cputype = CPU_1004K;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 1004Kc";
		cpu_set_mt_per_tc_perf(c);
		break;
	case PRID_IMP_1074K:
		c->cputype = CPU_1074K;
		c->writecombine = _CACHE_UNCACHED;
		__cpu_name[cpu] = "MIPS 1074Kc";
		break;
	case PRID_IMP_INTERAPTIV_UP:
		c->cputype = CPU_INTERAPTIV;
		__cpu_name[cpu] = "MIPS interAptiv";
		cpu_set_mt_per_tc_perf(c);
		break;
	case PRID_IMP_INTERAPTIV_MP:
		c->cputype = CPU_INTERAPTIV;
		__cpu_name[cpu] = "MIPS interAptiv (multi)";
		cpu_set_mt_per_tc_perf(c);
		break;
	case PRID_IMP_PROAPTIV_UP:
		c->cputype = CPU_PROAPTIV;
		__cpu_name[cpu] = "MIPS proAptiv";
		break;
	case PRID_IMP_PROAPTIV_MP:
		c->cputype = CPU_PROAPTIV;
		__cpu_name[cpu] = "MIPS proAptiv (multi)";
		break;
	case PRID_IMP_P5600:
		c->cputype = CPU_P5600;
		__cpu_name[cpu] = "MIPS P5600";
		break;
	case PRID_IMP_P6600:
		c->cputype = CPU_P6600;
		__cpu_name[cpu] = "MIPS P6600";
		break;
	case PRID_IMP_I6400:
		c->cputype = CPU_I6400;
		__cpu_name[cpu] = "MIPS I6400";
		break;
	case PRID_IMP_I6500:
		c->cputype = CPU_I6500;
		__cpu_name[cpu] = "MIPS I6500";
		break;
	case PRID_IMP_M5150:
		c->cputype = CPU_M5150;
		__cpu_name[cpu] = "MIPS M5150";
		break;
	case PRID_IMP_M6250:
		c->cputype = CPU_M6250;
		__cpu_name[cpu] = "MIPS M6250";
		break;
	}

	decode_configs(c);

	spram_config();

	switch (__get_cpu_type(c->cputype)) {
	case CPU_I6500:
		c->options |= MIPS_CPU_SHARED_FTLB_ENTRIES;
		/* fall-through */
	case CPU_I6400:
		c->options |= MIPS_CPU_SHARED_FTLB_RAM;
		/* fall-through */
	default:
		break;
	}
}