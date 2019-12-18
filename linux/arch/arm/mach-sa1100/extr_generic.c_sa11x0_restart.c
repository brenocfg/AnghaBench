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
 int REBOOT_SOFT ; 
 int /*<<< orphan*/  RESET_STATUS_ALL ; 
 int /*<<< orphan*/  RSRR ; 
 int /*<<< orphan*/  RSRR_SWR ; 
 int /*<<< orphan*/  clear_reset_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_restart (int /*<<< orphan*/ ) ; 

void sa11x0_restart(enum reboot_mode mode, const char *cmd)
{
	clear_reset_status(RESET_STATUS_ALL);

	if (mode == REBOOT_SOFT) {
		/* Jump into ROM at address 0 */
		soft_restart(0);
	} else {
		/* Use on-chip reset capability */
		RSRR = RSRR_SWR;
	}
}