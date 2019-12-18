#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gpio_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  g_name; int /*<<< orphan*/  g_pin; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_pin_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpio_pin_list (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_pinnum_by_name(gpio_handle_t handle, const char *name) {
	int i, maxpin, pinn;
	gpio_config_t *cfgs;
	gpio_config_t *pin;

	pinn = -1;
	maxpin = gpio_pin_list(handle, &cfgs);
	if (maxpin < 0) {
		perror("gpio_pin_list");
		exit(1);
	}

	for (i = 0; i <= maxpin; i++) {
		pin = cfgs + i;
		gpio_pin_get(handle, pin->g_pin);
		if (!strcmp(name, pin->g_name)) {
			pinn = i;
			break;
		}
	}
	free(cfgs);

	return pinn;
}