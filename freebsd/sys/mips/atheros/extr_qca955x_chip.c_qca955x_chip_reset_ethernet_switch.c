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
 int /*<<< orphan*/  AR934X_RESET_ETH_SWITCH ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ar71xx_device_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar71xx_device_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qca955x_chip_reset_ethernet_switch(void)
{
#if 0
	ar71xx_device_stop(AR934X_RESET_ETH_SWITCH);
	DELAY(100);
	ar71xx_device_start(AR934X_RESET_ETH_SWITCH);
	DELAY(100);
#endif
}