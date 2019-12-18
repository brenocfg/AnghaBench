#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpio_chip {int can_sleep; int base; unsigned int ngpio; int /*<<< orphan*/  owner; TYPE_2__* parent; int /*<<< orphan*/  of_node; int /*<<< orphan*/  label; int /*<<< orphan*/  dbg_show; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; } ;
struct adnp {TYPE_1__* client; scalar_t__ reg_shift; struct gpio_chip gpio; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {TYPE_2__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_FS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adnp_gpio_dbg_show ; 
 int /*<<< orphan*/  adnp_gpio_direction_input ; 
 int /*<<< orphan*/  adnp_gpio_direction_output ; 
 int /*<<< orphan*/  adnp_gpio_get ; 
 int /*<<< orphan*/  adnp_gpio_set ; 
 int devm_gpiochip_add_data (TYPE_2__*,struct gpio_chip*,struct adnp*) ; 
 scalar_t__ get_count_order (unsigned int) ; 

__attribute__((used)) static int adnp_gpio_setup(struct adnp *adnp, unsigned int num_gpios)
{
	struct gpio_chip *chip = &adnp->gpio;
	int err;

	adnp->reg_shift = get_count_order(num_gpios) - 3;

	chip->direction_input = adnp_gpio_direction_input;
	chip->direction_output = adnp_gpio_direction_output;
	chip->get = adnp_gpio_get;
	chip->set = adnp_gpio_set;
	chip->can_sleep = true;

	if (IS_ENABLED(CONFIG_DEBUG_FS))
		chip->dbg_show = adnp_gpio_dbg_show;

	chip->base = -1;
	chip->ngpio = num_gpios;
	chip->label = adnp->client->name;
	chip->parent = &adnp->client->dev;
	chip->of_node = chip->parent->of_node;
	chip->owner = THIS_MODULE;

	err = devm_gpiochip_add_data(&adnp->client->dev, chip, adnp);
	if (err)
		return err;

	return 0;
}