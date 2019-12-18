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
struct dwapb_gpio {unsigned int nr_ports; TYPE_1__* ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  gc; scalar_t__ is_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwapb_gpio_unregister(struct dwapb_gpio *gpio)
{
	unsigned int m;

	for (m = 0; m < gpio->nr_ports; ++m)
		if (gpio->ports[m].is_registered)
			gpiochip_remove(&gpio->ports[m].gc);
}