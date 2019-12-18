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
struct TYPE_4__ {int g_pin; char* g_name; int /*<<< orphan*/  g_caps; int /*<<< orphan*/  g_flags; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int gpio_pin_get (int /*<<< orphan*/ ,int) ; 
 int gpio_pin_list (int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_pins(gpio_handle_t handle, int verbose)
{
	int i, maxpin, pinv;
	gpio_config_t *cfgs;
	gpio_config_t *pin;

	maxpin = gpio_pin_list(handle, &cfgs);
	if (maxpin < 0) {
		perror("gpio_pin_list");
		exit(1);
	}

	for (i = 0; i <= maxpin; i++) {
		pin = cfgs + i;
		pinv = gpio_pin_get(handle, pin->g_pin);
		printf("pin %02d:\t%d\t%s", pin->g_pin, pinv,
		    pin->g_name);

		print_caps(pin->g_flags);

		if (verbose) {
			printf(", caps:");
			print_caps(pin->g_caps);
		}
		printf("\n");
	}
	free(cfgs);
}