#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  TYPE_2__* driverlink_t ;
struct TYPE_17__ {int /*<<< orphan*/  refs; int /*<<< orphan*/  name; TYPE_1__** baseclasses; } ;
typedef  TYPE_3__ driver_t ;
typedef  TYPE_4__* devclass_t ;
struct TYPE_18__ {int /*<<< orphan*/  drivers; } ;
struct TYPE_16__ {int pass; int /*<<< orphan*/  flags; TYPE_3__* driver; } ;
struct TYPE_15__ {char* name; } ;

/* Variables and functions */
 int BUS_PASS_ROOT ; 
 int /*<<< orphan*/  DL_DEFERRED_PROBE ; 
 int /*<<< orphan*/  DRIVERNAME (TYPE_3__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_BUS ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_data_generation_update () ; 
 int /*<<< orphan*/  devclass_driver_added (TYPE_4__*,TYPE_3__*) ; 
 TYPE_4__* devclass_find_internal (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ device_frozen ; 
 int /*<<< orphan*/  driver_register_pass (TYPE_2__*) ; 
 int /*<<< orphan*/  kobj_class_compile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int) ; 

int
devclass_add_driver(devclass_t dc, driver_t *driver, int pass, devclass_t *dcp)
{
	driverlink_t dl;
	const char *parentname;

	PDEBUG(("%s", DRIVERNAME(driver)));

	/* Don't allow invalid pass values. */
	if (pass <= BUS_PASS_ROOT)
		return (EINVAL);

	dl = malloc(sizeof *dl, M_BUS, M_NOWAIT|M_ZERO);
	if (!dl)
		return (ENOMEM);

	/*
	 * Compile the driver's methods. Also increase the reference count
	 * so that the class doesn't get freed when the last instance
	 * goes. This means we can safely use static methods and avoids a
	 * double-free in devclass_delete_driver.
	 */
	kobj_class_compile((kobj_class_t) driver);

	/*
	 * If the driver has any base classes, make the
	 * devclass inherit from the devclass of the driver's
	 * first base class. This will allow the system to
	 * search for drivers in both devclasses for children
	 * of a device using this driver.
	 */
	if (driver->baseclasses)
		parentname = driver->baseclasses[0]->name;
	else
		parentname = NULL;
	*dcp = devclass_find_internal(driver->name, parentname, TRUE);

	dl->driver = driver;
	TAILQ_INSERT_TAIL(&dc->drivers, dl, link);
	driver->refs++;		/* XXX: kobj_mtx */
	dl->pass = pass;
	driver_register_pass(dl);

	if (device_frozen) {
		dl->flags |= DL_DEFERRED_PROBE;
	} else {
		devclass_driver_added(dc, driver);
	}
	bus_data_generation_update();
	return (0);
}