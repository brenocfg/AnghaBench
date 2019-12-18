#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_4__ {char* class_name; } ;
struct TYPE_3__ {size_t cpuid; size_t cpu_class; char* cpu_name; char** cpu_steppings; } ;

/* Variables and functions */
#define  CPU_CLASS_ARM10E 134 
#define  CPU_CLASS_ARM10EJ 133 
#define  CPU_CLASS_ARM9EJS 132 
#define  CPU_CLASS_ARM9ES 131 
#define  CPU_CLASS_ARM9TDMI 130 
#define  CPU_CLASS_MARVELL 129 
#define  CPU_CLASS_XSCALE 128 
 size_t CPU_CONTROL_BEND_ENABLE ; 
 size_t CPU_CONTROL_BPRD_ENABLE ; 
 size_t CPU_CONTROL_DC_ENABLE ; 
 size_t CPU_CONTROL_IC_ENABLE ; 
 size_t CPU_CONTROL_LABT_ENABLE ; 
 size_t CPU_CONTROL_WBUF_ENABLE ; 
 size_t CPU_ID_CPU_MASK ; 
 size_t CPU_ID_REVISION_MASK ; 
 int MV_BTB_DISABLE ; 
 int MV_DC_STREAM_ENABLE ; 
 int MV_L2_ENABLE ; 
 int MV_L2_PREFETCH_DISABLE ; 
 int MV_WA_ENABLE ; 
 size_t arm_pcache_type ; 
 scalar_t__ arm_pcache_unified ; 
 scalar_t__ arm_pdcache_line_size ; 
 int arm_pdcache_size ; 
 int arm_pdcache_ways ; 
 scalar_t__ arm_picache_line_size ; 
 int arm_picache_size ; 
 int arm_picache_ways ; 
 size_t cp15_midr_get () ; 
 size_t cp15_sctlr_get () ; 
 size_t cpu_class ; 
 TYPE_2__* cpu_classes ; 
 TYPE_1__* cpuids ; 
 int /*<<< orphan*/  print_enadis (size_t,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sheeva_control_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** wtnames ; 

void
identify_arm_cpu(void)
{
	u_int cpuid, ctrl;
	int i;

	ctrl = cp15_sctlr_get();
	cpuid = cp15_midr_get();

	if (cpuid == 0) {
		printf("Processor failed probe - no CPU ID\n");
		return;
	}

	for (i = 0; cpuids[i].cpuid != 0; i++)
		if (cpuids[i].cpuid == (cpuid & CPU_ID_CPU_MASK)) {
			cpu_class = cpuids[i].cpu_class;
			printf("CPU: %s %s (%s core)\n",
			    cpuids[i].cpu_name,
			    cpuids[i].cpu_steppings[cpuid &
			    CPU_ID_REVISION_MASK],
			    cpu_classes[cpu_class].class_name);
			break;
		}
	if (cpuids[i].cpuid == 0)
		printf("unknown CPU (ID = 0x%x)\n", cpuid);

	printf(" ");

	if (ctrl & CPU_CONTROL_BEND_ENABLE)
		printf(" Big-endian");
	else
		printf(" Little-endian");

	switch (cpu_class) {
	case CPU_CLASS_ARM9TDMI:
	case CPU_CLASS_ARM9ES:
	case CPU_CLASS_ARM9EJS:
	case CPU_CLASS_ARM10E:
	case CPU_CLASS_ARM10EJ:
	case CPU_CLASS_XSCALE:
	case CPU_CLASS_MARVELL:
		print_enadis(ctrl & CPU_CONTROL_DC_ENABLE, "DC");
		print_enadis(ctrl & CPU_CONTROL_IC_ENABLE, "IC");
#if defined(SOC_MV_KIRKWOOD) || defined(SOC_MV_DISCOVERY)
		i = sheeva_control_ext(0, 0);
		print_enadis(i & MV_WA_ENABLE, "WA");
		print_enadis(i & MV_DC_STREAM_ENABLE, "DC streaming");
		printf("\n ");
		print_enadis((i & MV_BTB_DISABLE) == 0, "BTB");
		print_enadis(i & MV_L2_ENABLE, "L2");
		print_enadis((i & MV_L2_PREFETCH_DISABLE) == 0,
		    "L2 prefetch");
		printf("\n ");
#endif
		break;
	default:
		break;
	}

	print_enadis(ctrl & CPU_CONTROL_WBUF_ENABLE, "WB");
	if (ctrl & CPU_CONTROL_LABT_ENABLE)
		printf(" LABT");
	else
		printf(" EABT");

	print_enadis(ctrl & CPU_CONTROL_BPRD_ENABLE, "branch prediction");
	printf("\n");

	/* Print cache info. */
	if (arm_picache_line_size == 0 && arm_pdcache_line_size == 0)
		return;

	if (arm_pcache_unified) {
		printf("  %dKB/%dB %d-way %s unified cache\n",
		    arm_pdcache_size / 1024,
		    arm_pdcache_line_size, arm_pdcache_ways,
		    wtnames[arm_pcache_type]);
	} else {
		printf("  %dKB/%dB %d-way instruction cache\n",
		    arm_picache_size / 1024,
		    arm_picache_line_size, arm_picache_ways);
		printf("  %dKB/%dB %d-way %s data cache\n",
		    arm_pdcache_size / 1024,
		    arm_pdcache_line_size, arm_pdcache_ways,
		    wtnames[arm_pcache_type]);
	}
}