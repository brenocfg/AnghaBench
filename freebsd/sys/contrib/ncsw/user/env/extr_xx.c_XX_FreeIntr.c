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
typedef  int /*<<< orphan*/  t_Error ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  cookie; int /*<<< orphan*/ * arg; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int XX_INTR_FLAG_PREALLOCATED ; 
 TYPE_1__* XX_IntrInfo ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_device (struct resource*) ; 
 uintptr_t rman_get_start (struct resource*) ; 

t_Error
XX_FreeIntr(uintptr_t irq)
{
	device_t dev;
	struct resource *r;

	r = (struct resource *)irq;
	dev = rman_get_device(r);
	irq = rman_get_start(r);

	/* Handle preallocated interrupts */
	if (XX_IntrInfo[irq].flags & XX_INTR_FLAG_PREALLOCATED) {
		if (XX_IntrInfo[irq].handler == NULL)
			return (E_INVALID_STATE);

		XX_IntrInfo[irq].handler = NULL;
		XX_IntrInfo[irq].arg = NULL;

		return (E_OK);
	}

	return (bus_teardown_intr(dev, r, XX_IntrInfo[irq].cookie));
}