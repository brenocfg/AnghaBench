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
struct gpio_pin {int /*<<< orphan*/  gp_flags; int /*<<< orphan*/  gp_caps; int /*<<< orphan*/  gp_name; int /*<<< orphan*/  gp_pin; } ;
typedef  int /*<<< orphan*/  gpio_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  g_flags; int /*<<< orphan*/  g_caps; int /*<<< orphan*/  g_name; int /*<<< orphan*/  g_pin; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOGETCONFIG ; 
 int /*<<< orphan*/  GPIOMAXNAME ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gpio_pin*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
gpio_pin_config(gpio_handle_t handle, gpio_config_t *cfg)
{
	struct gpio_pin gppin;

	if (cfg == NULL)
		return (-1);
	gppin.gp_pin = cfg->g_pin;
	if (ioctl(handle, GPIOGETCONFIG, &gppin) < 0)
		return (-1);
	strlcpy(cfg->g_name, gppin.gp_name, GPIOMAXNAME);
	cfg->g_caps = gppin.gp_caps;
	cfg->g_flags = gppin.gp_flags;

	return (0);
}