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
struct resource {int dummy; } ;
struct mvs_controller {TYPE_1__* interrupt; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * argument; int /*<<< orphan*/ * function; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ ) ; 
 struct mvs_controller* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvs_teardown_intr(device_t dev, device_t child, struct resource *irq,
		      void *cookie)
{
	struct mvs_controller *ctlr = device_get_softc(dev);
	int unit = (intptr_t)device_get_ivars(child);

	ctlr->interrupt[unit].function = NULL;
	ctlr->interrupt[unit].argument = NULL;
	return (0);
}