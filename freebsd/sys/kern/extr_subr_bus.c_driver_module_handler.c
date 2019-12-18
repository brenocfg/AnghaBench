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
struct driver_module_data {int (* dmd_chainevh ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int dmd_pass; int /*<<< orphan*/  dmd_chainarg; int /*<<< orphan*/  dmd_driver; int /*<<< orphan*/  dmd_busname; int /*<<< orphan*/  dmd_devclass; } ;
typedef  int /*<<< orphan*/  module_t ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/  devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVERNAME (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 130 
#define  MOD_QUIESCE 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int devclass_add_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int devclass_delete_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devclass_quiesce_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
driver_module_handler(module_t mod, int what, void *arg)
{
	struct driver_module_data *dmd;
	devclass_t bus_devclass;
	kobj_class_t driver;
	int error, pass;

	dmd = (struct driver_module_data *)arg;
	bus_devclass = devclass_find_internal(dmd->dmd_busname, NULL, TRUE);
	error = 0;

	switch (what) {
	case MOD_LOAD:
		if (dmd->dmd_chainevh)
			error = dmd->dmd_chainevh(mod,what,dmd->dmd_chainarg);

		pass = dmd->dmd_pass;
		driver = dmd->dmd_driver;
		PDEBUG(("Loading module: driver %s on bus %s (pass %d)",
		    DRIVERNAME(driver), dmd->dmd_busname, pass));
		error = devclass_add_driver(bus_devclass, driver, pass,
		    dmd->dmd_devclass);
		break;

	case MOD_UNLOAD:
		PDEBUG(("Unloading module: driver %s from bus %s",
		    DRIVERNAME(dmd->dmd_driver),
		    dmd->dmd_busname));
		error = devclass_delete_driver(bus_devclass,
		    dmd->dmd_driver);

		if (!error && dmd->dmd_chainevh)
			error = dmd->dmd_chainevh(mod,what,dmd->dmd_chainarg);
		break;
	case MOD_QUIESCE:
		PDEBUG(("Quiesce module: driver %s from bus %s",
		    DRIVERNAME(dmd->dmd_driver),
		    dmd->dmd_busname));
		error = devclass_quiesce_driver(bus_devclass,
		    dmd->dmd_driver);

		if (!error && dmd->dmd_chainevh)
			error = dmd->dmd_chainevh(mod,what,dmd->dmd_chainarg);
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}

	return (error);
}