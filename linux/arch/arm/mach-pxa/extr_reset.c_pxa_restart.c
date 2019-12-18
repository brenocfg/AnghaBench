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
#define  REBOOT_GPIO 130 
#define  REBOOT_HARD 129 
#define  REBOOT_SOFT 128 
 int /*<<< orphan*/  RESET_STATUS_ALL ; 
 int /*<<< orphan*/  clear_reset_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_gpio_reset () ; 
 int /*<<< orphan*/  do_hw_reset () ; 
 int /*<<< orphan*/  local_fiq_disable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  soft_restart (int /*<<< orphan*/ ) ; 

void pxa_restart(enum reboot_mode mode, const char *cmd)
{
	local_irq_disable();
	local_fiq_disable();

	clear_reset_status(RESET_STATUS_ALL);

	switch (mode) {
	case REBOOT_SOFT:
		/* Jump into ROM at address 0 */
		soft_restart(0);
		break;
	case REBOOT_GPIO:
		do_gpio_reset();
		break;
	case REBOOT_HARD:
	default:
		do_hw_reset();
		break;
	}
}