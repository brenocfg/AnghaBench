#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  force_ibs_eilvt_setup () ; 

__attribute__((used)) static void ibs_eilvt_setup(void)
{
	/*
	 * Force LVT offset assignment for family 10h: The offsets are
	 * not assigned by the BIOS for this family, so the OS is
	 * responsible for doing it. If the OS assignment fails, fall
	 * back to BIOS settings and try to setup this.
	 */
	if (boot_cpu_data.x86 == 0x10)
		force_ibs_eilvt_setup();
}