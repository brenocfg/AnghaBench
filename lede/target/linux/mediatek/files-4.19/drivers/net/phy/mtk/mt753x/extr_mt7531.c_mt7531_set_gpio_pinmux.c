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
typedef  int u32 ;
struct gsw_mt753x {TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/ * gpio_int_funcs ; 
 int /*<<< orphan*/ * gpio_int_pins ; 
 int /*<<< orphan*/ * gpio_mdc_funcs ; 
 int /*<<< orphan*/ * gpio_mdc_pins ; 
 int /*<<< orphan*/ * gpio_mdio_funcs ; 
 int /*<<< orphan*/ * gpio_mdio_pins ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  pinmux_set_mux_7531 (struct gsw_mt753x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7531_set_gpio_pinmux(struct gsw_mt753x *gsw)
{
	u32 group = 0;
	struct device_node *np = gsw->dev->of_node;

	/* Set GPIO 0 interrupt mode */
	pinmux_set_mux_7531(gsw, gpio_int_pins[0], gpio_int_funcs[0]);

	of_property_read_u32(np, "mediatek,mdio_master_pinmux", &group);

	/* group = 0: do nothing, 1: 1st group (AE), 2: 2nd group (BE) */
	if (group > 0 && group <= 2) {
		group--;
		pinmux_set_mux_7531(gsw, gpio_mdc_pins[group],
				    gpio_mdc_funcs[group]);
		pinmux_set_mux_7531(gsw, gpio_mdio_pins[group],
				    gpio_mdio_funcs[group]);
	}

	return 0;
}