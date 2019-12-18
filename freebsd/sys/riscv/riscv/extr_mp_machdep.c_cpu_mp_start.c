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

/* Variables and functions */
#define  CPUS_FDT 129 
#define  CPUS_UNKNOWN 128 
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  all_harts ; 
 int /*<<< orphan*/  ap_boot_mtx ; 
 int /*<<< orphan*/  boot_hart ; 
 int cpu_enum_method ; 
 int /*<<< orphan*/  cpu_init_fdt ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_cpu_early_foreach (int /*<<< orphan*/ ,int) ; 

void
cpu_mp_start(void)
{

	mtx_init(&ap_boot_mtx, "ap boot", NULL, MTX_SPIN);

	CPU_SET(0, &all_cpus);
	CPU_SET(boot_hart, &all_harts);

	switch(cpu_enum_method) {
#ifdef FDT
	case CPUS_FDT:
		ofw_cpu_early_foreach(cpu_init_fdt, true);
		break;
#endif
	case CPUS_UNKNOWN:
		break;
	}
}