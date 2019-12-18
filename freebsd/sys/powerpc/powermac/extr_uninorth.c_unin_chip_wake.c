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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  UNIN_HWINIT_STATE ; 
 int /*<<< orphan*/  UNIN_PWR_MASK ; 
 int /*<<< orphan*/  UNIN_PWR_MGMT ; 
 int /*<<< orphan*/  UNIN_PWR_NORMAL ; 
 int /*<<< orphan*/  UNIN_RUNNING ; 
 int /*<<< orphan*/ * unin_chip ; 
 int /*<<< orphan*/  unin_update_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
unin_chip_wake(device_t dev)
{

	if (dev == NULL)
		dev = unin_chip;
	unin_update_reg(dev, UNIN_PWR_MGMT, UNIN_PWR_NORMAL, UNIN_PWR_MASK);
	DELAY(10);
	unin_update_reg(dev, UNIN_HWINIT_STATE, UNIN_RUNNING, 0);
	DELAY(100);

	return (0);
}