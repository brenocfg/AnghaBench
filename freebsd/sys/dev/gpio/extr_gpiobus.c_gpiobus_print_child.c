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
struct gpiobus_ivar {int npins; int /*<<< orphan*/  rl; } ;
typedef  int /*<<< orphan*/  pins ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct gpiobus_ivar* GPIOBUS_IVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 scalar_t__ bus_print_child_footer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_print_child_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiobus_print_pins (struct gpiobus_ivar*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ printf (char*,...) ; 
 int /*<<< orphan*/  resource_list_print_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
gpiobus_print_child(device_t dev, device_t child)
{
	char pins[128];
	int retval = 0;
	struct gpiobus_ivar *devi;

	devi = GPIOBUS_IVAR(child);
	memset(pins, 0, sizeof(pins));
	retval += bus_print_child_header(dev, child);
	if (devi->npins > 0) {
		if (devi->npins > 1)
			retval += printf(" at pins ");
		else
			retval += printf(" at pin ");
		gpiobus_print_pins(devi, pins, sizeof(pins));
		retval += printf("%s", pins);
	}
	resource_list_print_type(&devi->rl, "irq", SYS_RES_IRQ, "%jd");
	retval += bus_print_child_footer(dev, child);

	return (retval);
}