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
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  TYPE_1__* device_t ;
struct TYPE_3__ {void* dev_irq_arg; int /*<<< orphan*/ * dev_irq_fn; int /*<<< orphan*/ * dev_irq_filter; } ;

/* Variables and functions */

void
device_set_interrupt(device_t dev, driver_filter_t *filter,
    driver_intr_t *fn, void *arg)
{
	dev->dev_irq_filter = filter;
	dev->dev_irq_fn = fn;
	dev->dev_irq_arg = arg;
}