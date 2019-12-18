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
struct gpio_keys_button_data {TYPE_1__* b; scalar_t__ can_sleep; } ;
struct TYPE_2__ {int active_low; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_get_value_cansleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_button_get_value(struct gpio_keys_button_data *bdata)
{
	int val;

	if (bdata->can_sleep)
		val = !!gpio_get_value_cansleep(bdata->b->gpio);
	else
		val = !!gpio_get_value(bdata->b->gpio);

	return val ^ bdata->b->active_low;
}