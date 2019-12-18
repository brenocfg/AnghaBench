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
struct gpio_keys_button_data {TYPE_1__* b; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  button_hotplug_event (struct gpio_keys_button_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_button_get_value (struct gpio_keys_button_data*) ; 

__attribute__((used)) static irqreturn_t button_handle_irq(int irq, void *_bdata)
{
	struct gpio_keys_button_data *bdata = (struct gpio_keys_button_data *) _bdata;

	button_hotplug_event(bdata, bdata->b->type ?: EV_KEY, gpio_button_get_value(bdata));

	return IRQ_HANDLED;
}