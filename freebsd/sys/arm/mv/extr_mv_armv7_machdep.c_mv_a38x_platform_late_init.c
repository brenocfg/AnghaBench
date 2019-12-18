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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 scalar_t__ MV_SOC_UNSUPPORTED ; 
 int /*<<< orphan*/  VM_MEMATTR_DEVICE ; 
 int /*<<< orphan*/  VM_MEMATTR_SO ; 
 int /*<<< orphan*/  arm_tmr_change_frequency (int) ; 
 scalar_t__ armada38x_mbus_optimization () ; 
 scalar_t__ armada38x_open_bootrom_win () ; 
 scalar_t__ armada38x_scu_enable () ; 
 scalar_t__ armada38x_win_set_iosync_barrier () ; 
 int get_cpu_freq () ; 
 scalar_t__ mv_check_soc_family () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_remap_vm_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ soc_decode_win () ; 

__attribute__((used)) static void
mv_a38x_platform_late_init(platform_t plate)
{

	/*
	 * Re-initialise decode windows
	 */
	if (mv_check_soc_family() == MV_SOC_UNSUPPORTED)
		panic("Unsupported SoC family\n");

	if (soc_decode_win() != 0)
		printf("WARNING: could not re-initialise decode windows! "
		    "Running with existing settings...\n");

	/* Configure timers' base frequency */
	arm_tmr_change_frequency(get_cpu_freq() / 2);

	/*
	 * Workaround for Marvell Armada38X family HW issue
	 * between Cortex-A9 CPUs and on-chip devices that may
	 * cause hang on heavy load.
	 * To avoid that, map all registers including PCIe IO
	 * as strongly ordered instead of device memory.
	 */
	pmap_remap_vm_attr(VM_MEMATTR_DEVICE, VM_MEMATTR_SO);

	/* Set IO Sync Barrier bit for all Mbus devices */
	if (armada38x_win_set_iosync_barrier() != 0)
		printf("WARNING: could not map CPU Subsystem registers\n");
	if (armada38x_mbus_optimization() != 0)
		printf("WARNING: could not enable mbus optimization\n");
	if (armada38x_scu_enable() != 0)
		printf("WARNING: could not enable SCU\n");
#ifdef SMP
	/* Open window to bootROM memory - needed for SMP */
	if (armada38x_open_bootrom_win() != 0)
		printf("WARNING: could not open window to bootROM\n");
#endif
}