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
struct TYPE_2__ {scalar_t__ restart_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_wait () ; 
 int /*<<< orphan*/  loongson_reboot () ; 
 TYPE_1__ loongson_sysconf ; 
 int /*<<< orphan*/  mach_prepare_reboot () ; 

__attribute__((used)) static void loongson_restart(char *command)
{
#ifndef CONFIG_LEFI_FIRMWARE_INTERFACE
	/* do preparation for reboot */
	mach_prepare_reboot();

	/* reboot via jumping to boot base address */
	loongson_reboot();
#else
	void (*fw_restart)(void) = (void *)loongson_sysconf.restart_addr;

	fw_restart();
	while (1) {
		if (cpu_wait)
			cpu_wait();
	}
#endif
}