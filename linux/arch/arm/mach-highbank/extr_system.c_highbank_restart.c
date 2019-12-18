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
typedef  enum reboot_mode { ____Placeholder_reboot_mode } reboot_mode ;

/* Variables and functions */
 int REBOOT_HARD ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  highbank_set_pwr_hard_reset () ; 
 int /*<<< orphan*/  highbank_set_pwr_soft_reset () ; 

void highbank_restart(enum reboot_mode mode, const char *cmd)
{
	if (mode == REBOOT_HARD)
		highbank_set_pwr_hard_reset();
	else
		highbank_set_pwr_soft_reset();

	while (1)
		cpu_do_idle();
}