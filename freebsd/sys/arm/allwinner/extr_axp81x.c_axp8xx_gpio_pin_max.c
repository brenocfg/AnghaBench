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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  axp8xx_pins ; 
 int nitems (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
axp8xx_gpio_pin_max(device_t dev, int *maxpin)
{
	*maxpin = nitems(axp8xx_pins) - 1;

	return (0);
}