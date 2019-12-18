#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gpio_pin_t ;
typedef  int /*<<< orphan*/  gpio_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  g_flags; int /*<<< orphan*/  g_pin; } ;
typedef  TYPE_1__ gpio_config_t ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 scalar_t__ gpio_pin_config (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int gpio_pin_set_flags (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
gpio_pin_set_flag(gpio_handle_t handle, gpio_pin_t pin, uint32_t flag)
{
	gpio_config_t cfg;

	bzero(&cfg, sizeof(cfg));
	cfg.g_pin = pin;
	if (gpio_pin_config(handle, &cfg) < 0)
		return (-1);
	cfg.g_flags = flag;

	return (gpio_pin_set_flags(handle, &cfg));
}