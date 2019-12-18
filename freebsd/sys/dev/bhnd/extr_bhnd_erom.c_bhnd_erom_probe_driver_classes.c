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
struct bhnd_erom_io {int dummy; } ;
struct bhnd_chipid {int dummy; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  devclass_t ;
typedef  int /*<<< orphan*/  bhnd_erom_class_t ;

/* Variables and functions */
 int BUS_PROBE_SPECIFIC ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/ * bhnd_driver_get_erom_class (int /*<<< orphan*/ *) ; 
 int bhnd_erom_probe (int /*<<< orphan*/ *,struct bhnd_erom_io*,struct bhnd_chipid const*,struct bhnd_chipid*) ; 
 int devclass_get_drivers (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*) ; 
 char* devclass_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_class_compile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

bhnd_erom_class_t *
bhnd_erom_probe_driver_classes(devclass_t bus_devclass,
    struct bhnd_erom_io *eio, const struct bhnd_chipid *hint,
    struct bhnd_chipid *cid)
{
	driver_t		**drivers;
	int			 drv_count;
	bhnd_erom_class_t	*erom_cls;
	int			 error, prio, result;

	erom_cls = NULL;
	prio = 0;

	/* Fetch all available drivers */
	error = devclass_get_drivers(bus_devclass, &drivers, &drv_count);
	if (error) {
		printf("error fetching bhnd(4) drivers for %s: %d\n",
		    devclass_get_name(bus_devclass), error);
		return (NULL);
	}

	/* Enumerate the drivers looking for the best available EROM class */
	for (int i = 0; i < drv_count; i++) {
		struct bhnd_chipid	 pcid;
		bhnd_erom_class_t	*cls;

		/* The default implementation of BHND_BUS_GET_EROM_CLASS()
		 * returns NULL if unimplemented; this should always be safe
		 * to call on arbitrary drivers */
		cls = bhnd_driver_get_erom_class(drivers[i]);
		if (cls == NULL)
			continue;

		kobj_class_compile(cls);

		/* Probe the bus */
		result = bhnd_erom_probe(cls, eio, hint, &pcid);

		/* The parser did not match if an error was returned */
		if (result > 0)
			continue;
		
		/* Check for a new highest priority match */
		if (erom_cls == NULL || result > prio) {
			prio = result;

			*cid = pcid;
			erom_cls = cls;
		}

		/* Terminate immediately on BUS_PROBE_SPECIFIC */
		if (result == BUS_PROBE_SPECIFIC)
			break;
	}

	free(drivers, M_TEMP);
	return (erom_cls);
}