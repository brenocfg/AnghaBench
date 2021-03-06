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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ti_pinmux_padconf {scalar_t__ gpio_pin; int gpio_mode; int /*<<< orphan*/  reg_off; int /*<<< orphan*/ * ballname; } ;
struct TYPE_2__ {unsigned int padconf_sate_mask; int padconf_muxmode_mask; struct ti_pinmux_padconf* padconf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 TYPE_1__* ti_pinmux_dev ; 
 int /*<<< orphan*/  ti_pinmux_sc ; 
 int /*<<< orphan*/  ti_pinmux_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ti_pinmux_padconf_set_gpiomode(uint32_t gpio, unsigned int state)
{
	const struct ti_pinmux_padconf *padconf;
	uint16_t reg_val;

	if (!ti_pinmux_sc)
		return (ENXIO);

	/* find the gpio pin in the padconf array */
	padconf = ti_pinmux_dev->padconf;
	while (padconf->ballname != NULL) {
		if (padconf->gpio_pin == gpio)
			break;
		padconf++;
	}
	if (padconf->ballname == NULL)
		return (EINVAL);

	/* populate the new value for the PADCONF register */
	reg_val = (uint16_t)(state & ti_pinmux_dev->padconf_sate_mask);

	/* set the mux mode */
	reg_val |= (uint16_t)(padconf->gpio_mode & ti_pinmux_dev->padconf_muxmode_mask);

	/* write the register value (16-bit writes) */
	ti_pinmux_write_2(ti_pinmux_sc, padconf->reg_off, reg_val);

	return (0);
}