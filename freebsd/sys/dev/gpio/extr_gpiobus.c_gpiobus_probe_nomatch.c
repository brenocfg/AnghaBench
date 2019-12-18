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
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gpiobus_print_pins (struct gpiobus_ivar*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  resource_list_print_type (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
gpiobus_probe_nomatch(device_t dev, device_t child)
{
	char pins[128];
	struct gpiobus_ivar *devi;

	devi = GPIOBUS_IVAR(child);
	memset(pins, 0, sizeof(pins));
	gpiobus_print_pins(devi, pins, sizeof(pins));
	if (devi->npins > 1)
		device_printf(dev, "<unknown device> at pins %s", pins);
	else
		device_printf(dev, "<unknown device> at pin %s", pins);
	resource_list_print_type(&devi->rl, "irq", SYS_RES_IRQ, "%jd");
	printf("\n");
}