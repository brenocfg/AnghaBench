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
struct TYPE_3__ {scalar_t__ vclock_mode; } ;
struct TYPE_4__ {TYPE_1__ clock; } ;

/* Variables and functions */
 scalar_t__ VCLOCK_HVCLOCK ; 
 int check_tsc_unstable () ; 
 TYPE_2__ pvclock_gtod_data ; 

__attribute__((used)) static inline bool kvm_check_tsc_unstable(void)
{
#ifdef CONFIG_X86_64
	/*
	 * TSC is marked unstable when we're running on Hyper-V,
	 * 'TSC page' clocksource is good.
	 */
	if (pvclock_gtod_data.clock.vclock_mode == VCLOCK_HVCLOCK)
		return false;
#endif
	return check_tsc_unstable();
}