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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int BHNDB_ROUTE_INTERRUPTS (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int bhnd_generic_setup_intr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void**) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bhnd_bhndb_setup_intr(device_t dev, device_t child, struct resource *irq,
    int flags, driver_filter_t *filter, driver_intr_t *intr, void *arg,
    void **cookiep)
{
	device_t	core, bus;
	int		error;

	/* Find the actual bus-attached child core */
	core = child;
	while ((bus = device_get_parent(core)) != NULL) {
		if (bus == dev)
			break;

		core = bus;
	}

	KASSERT(core != NULL, ("%s is not a child of %s",
	    device_get_nameunit(child), device_get_nameunit(dev)));

	/* Ask our bridge to enable interrupt routing for the child core */
	error = BHNDB_ROUTE_INTERRUPTS(device_get_parent(dev), core);
	if (error)
		return (error);

	/* Delegate actual interrupt setup to the default bhnd bus
	 * implementation */
	return (bhnd_generic_setup_intr(dev, child, irq, flags, filter, intr,
	    arg, cookiep));
}