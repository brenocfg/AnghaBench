#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
typedef  TYPE_1__* device_t ;
struct TYPE_3__ {int /*<<< orphan*/ * dev_irq_arg; int /*<<< orphan*/ * dev_irq_fn; int /*<<< orphan*/ * dev_irq_filter; } ;

/* Variables and functions */

int
bus_teardown_intr(device_t dev, struct resource *r, void *cookie)
{

	dev->dev_irq_filter = NULL;
	dev->dev_irq_fn = NULL;
	dev->dev_irq_arg = NULL;

	return (0);
}