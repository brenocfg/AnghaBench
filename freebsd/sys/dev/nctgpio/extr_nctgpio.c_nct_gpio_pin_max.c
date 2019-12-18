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
 int NCT_MAX_PIN ; 

__attribute__((used)) static int
nct_gpio_pin_max(device_t dev, int *npins)
{
	*npins = NCT_MAX_PIN;

	return (0);
}