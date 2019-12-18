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
struct cf_level {TYPE_1__* rel_set; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int GPIO_DDR_OUTPUT ; 
 int /*<<< orphan*/  macgpio_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vcoregpio_pre_change(device_t dev, const struct cf_level *level)
{
	if (level->rel_set[0].freq == 10000 /* max */) {
		/*
		 * Make sure the CPU voltage is raised before we raise
		 * the clock.
		 */
		macgpio_write(dev, GPIO_DDR_OUTPUT | 1);
		DELAY(1000);
	}
}