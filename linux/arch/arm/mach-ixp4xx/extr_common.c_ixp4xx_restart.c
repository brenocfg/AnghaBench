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
 int* IXP4XX_OSWE ; 
 int /*<<< orphan*/ * IXP4XX_OSWK ; 
 scalar_t__* IXP4XX_OSWT ; 
 int IXP4XX_WDT_COUNT_ENABLE ; 
 int /*<<< orphan*/  IXP4XX_WDT_KEY ; 
 int IXP4XX_WDT_RESET_ENABLE ; 
 int REBOOT_SOFT ; 
 int /*<<< orphan*/  soft_restart (int /*<<< orphan*/ ) ; 

void ixp4xx_restart(enum reboot_mode mode, const char *cmd)
{
	if (mode == REBOOT_SOFT) {
		/* Jump into ROM at address 0 */
		soft_restart(0);
	} else {
		/* Use on-chip reset capability */

		/* set the "key" register to enable access to
		 * "timer" and "enable" registers
		 */
		*IXP4XX_OSWK = IXP4XX_WDT_KEY;

		/* write 0 to the timer register for an immediate reset */
		*IXP4XX_OSWT = 0;

		*IXP4XX_OSWE = IXP4XX_WDT_RESET_ENABLE | IXP4XX_WDT_COUNT_ENABLE;
	}
}