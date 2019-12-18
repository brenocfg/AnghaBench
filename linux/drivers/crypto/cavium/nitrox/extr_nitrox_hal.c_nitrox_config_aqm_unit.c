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
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_aqm_interrupts (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_aqm_rings (struct nitrox_device*) ; 

void nitrox_config_aqm_unit(struct nitrox_device *ndev)
{
	/* config aqm command queues */
	nitrox_config_aqm_rings(ndev);

	/* enable aqm interrupts */
	enable_aqm_interrupts(ndev);
}