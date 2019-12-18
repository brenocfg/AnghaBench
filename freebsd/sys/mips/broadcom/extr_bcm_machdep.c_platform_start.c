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
typedef  scalar_t__ vm_offset_t ;
typedef  int uint64_t ;
typedef  scalar_t__ __register_t ;

/* Variables and functions */
 scalar_t__ CFE_EPTSEAL ; 
 int bcm_get_cpufreq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_get_platform () ; 
 int bcm_init_platform_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcm_platform_data ; 
 int /*<<< orphan*/  cfe_init (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cninit () ; 
 int /*<<< orphan*/  edata ; 
 int /*<<< orphan*/  end ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mips_init () ; 
 int /*<<< orphan*/  mips_pcpu0_init () ; 
 int /*<<< orphan*/  mips_postboot_fixup () ; 
 int /*<<< orphan*/  mips_timer_early_init (int) ; 
 int /*<<< orphan*/  mips_timer_init_params (int,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

void
platform_start(__register_t a0, __register_t a1, __register_t a2,
	       __register_t a3)
{
	vm_offset_t 		 kernend;
	uint64_t		 platform_counter_freq;
	int			 error;

	/* clear the BSS and SBSS segments */
	kernend = (vm_offset_t)&end;
	memset(&edata, 0, kernend - (vm_offset_t)(&edata));

	mips_postboot_fixup();

	/* Initialize pcpu stuff */
	mips_pcpu0_init();

#ifdef CFE
	/*
	 * Initialize CFE firmware trampolines. This must be done
	 * before any CFE APIs are called, including writing
	 * to the CFE console.
	 *
	 * CFE passes the following values in registers:
	 * a0: firmware handle
	 * a2: firmware entry point
	 * a3: entry point seal
	 */
	if (a3 == CFE_EPTSEAL)
		cfe_init(a0, a2);
#endif

	/* Init BCM platform data */
	if ((error = bcm_init_platform_data(&bcm_platform_data)))
		panic("bcm_init_platform_data() failed: %d", error);

	platform_counter_freq = bcm_get_cpufreq(bcm_get_platform());

	/* CP0 ticks every two cycles */
	mips_timer_early_init(platform_counter_freq / 2);

	cninit();

	mips_init();

	mips_timer_init_params(platform_counter_freq, 1);
}