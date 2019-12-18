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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 scalar_t__ CHIP_PROCESSOR_ID_XLP_416 ; 
 int MAXCPU ; 
 int /*<<< orphan*/  SYS_CPU_RESET ; 
 int XLP_MAX_CORES ; 
 int /*<<< orphan*/  nlm_get_sys_regbase (int /*<<< orphan*/ ) ; 
 scalar_t__ nlm_processor_id () ; 
 int nlm_read_sys_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,...) ; 
 int* xlp_cpuid_to_hwtid ; 
 int xlp_hw_thread_mask ; 
 int* xlp_hwtid_to_cpuid ; 
 int xlp_mmuval ; 
 int xlp_ncores ; 
 int xlp_threads_per_core ; 

__attribute__((used)) static void
xlp_parse_mmu_options(void)
{
	uint64_t sysbase;
	uint32_t cpu_map = xlp_hw_thread_mask;
	uint32_t core0_thr_mask, core_thr_mask, cpu_rst_mask;
	int i, j, k;

#ifdef SMP
	if (cpu_map == 0)
		cpu_map = 0xffffffff;
#else /* Uniprocessor! */
	if (cpu_map == 0)
		cpu_map = 0x1;
	else if (cpu_map != 0x1) {
		printf("WARNING: Starting uniprocessor kernel on cpumask [0x%lx]!\n"
		    "WARNING: Other CPUs will be unused.\n", (u_long)cpu_map);
		cpu_map = 0x1;
	}
#endif

	xlp_ncores = 1;
	core0_thr_mask = cpu_map & 0xf;
	switch (core0_thr_mask) {
	case 1:
		xlp_threads_per_core = 1;
		xlp_mmuval = 0;
		break;
	case 3:
		xlp_threads_per_core = 2;
		xlp_mmuval = 2;
		break;
	case 0xf:
		xlp_threads_per_core = 4;
		xlp_mmuval = 3;
		break;
	default:
		goto unsupp;
	}

	/* Try to find the enabled cores from SYS block */
	sysbase = nlm_get_sys_regbase(0);
	cpu_rst_mask = nlm_read_sys_reg(sysbase, SYS_CPU_RESET) & 0xff;

	/* XLP 416 does not report this correctly, fix */
	if (nlm_processor_id() == CHIP_PROCESSOR_ID_XLP_416)
		cpu_rst_mask = 0xe;

	/* Take out cores which do not exist on chip */
	for (i = 1; i < XLP_MAX_CORES; i++) {
		if ((cpu_rst_mask & (1 << i)) == 0)
			cpu_map &= ~(0xfu << (4 * i));
	}

	/* Verify other cores' CPU masks */
	for (i = 1; i < XLP_MAX_CORES; i++) {
		core_thr_mask = (cpu_map >> (4 * i)) & 0xf;
		if (core_thr_mask == 0)
			continue;
		if (core_thr_mask != core0_thr_mask)
			goto unsupp;
		xlp_ncores++;
	}

	xlp_hw_thread_mask = cpu_map;
	/* setup hardware processor id to cpu id mapping */
	for (i = 0; i< MAXCPU; i++)
		xlp_cpuid_to_hwtid[i] =
		    xlp_hwtid_to_cpuid[i] = -1;
	for (i = 0, k = 0; i < XLP_MAX_CORES; i++) {
		if (((cpu_map >> (i * 4)) & 0xf) == 0)
			continue;
		for (j = 0; j < xlp_threads_per_core; j++) {
			xlp_cpuid_to_hwtid[k] = i * 4 + j;
			xlp_hwtid_to_cpuid[i * 4 + j] = k;
			k++;
		}
	}

	return;

unsupp:
	printf("ERROR : Unsupported CPU mask [use 1,2 or 4 threads per core].\n"
	    "\tcore0 thread mask [%lx], boot cpu mask [%lx].\n",
	    (u_long)core0_thr_mask, (u_long)cpu_map);
	panic("Invalid CPU mask - halting.\n");
	return;
}