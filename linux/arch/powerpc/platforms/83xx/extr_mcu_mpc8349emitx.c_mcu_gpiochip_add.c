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
struct gpio_chip {int can_sleep; int base; struct device_node* of_node; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  set; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  label; int /*<<< orphan*/  owner; } ;
struct mcu {struct gpio_chip gc; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCU_NUM_GPIO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int gpiochip_add_data (struct gpio_chip*,struct mcu*) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 int /*<<< orphan*/  mcu_gpio_dir_out ; 
 int /*<<< orphan*/  mcu_gpio_set ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mcu_gpiochip_add(struct mcu *mcu)
{
	struct device_node *np;
	struct gpio_chip *gc = &mcu->gc;

	np = of_find_compatible_node(NULL, NULL, "fsl,mcu-mpc8349emitx");
	if (!np)
		return -ENODEV;

	gc->owner = THIS_MODULE;
	gc->label = kasprintf(GFP_KERNEL, "%pOF", np);
	gc->can_sleep = 1;
	gc->ngpio = MCU_NUM_GPIO;
	gc->base = -1;
	gc->set = mcu_gpio_set;
	gc->direction_output = mcu_gpio_dir_out;
	gc->of_node = np;

	return gpiochip_add_data(gc, mcu);
}