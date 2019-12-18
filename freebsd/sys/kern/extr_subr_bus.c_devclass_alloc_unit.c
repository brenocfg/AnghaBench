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
typedef  int /*<<< orphan*/ * device_t ;
typedef  TYPE_1__* devclass_t ;
struct TYPE_4__ {char* name; int maxunit; int /*<<< orphan*/ ** devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HINT_DEVICE_UNIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  DEVCLANAME (TYPE_1__*) ; 
 int EEXIST ; 
 int ENOMEM ; 
 int MINALLOCSIZE ; 
 int /*<<< orphan*/  M_BUS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int) ; 
 scalar_t__ resource_string_value (char*,int,char*,char const**) ; 
 int roundup (int,int) ; 

__attribute__((used)) static int
devclass_alloc_unit(devclass_t dc, device_t dev, int *unitp)
{
	const char *s;
	int unit = *unitp;

	PDEBUG(("unit %d in devclass %s", unit, DEVCLANAME(dc)));

	/* Ask the parent bus if it wants to wire this device. */
	if (unit == -1)
		BUS_HINT_DEVICE_UNIT(device_get_parent(dev), dev, dc->name,
		    &unit);

	/* If we were given a wired unit number, check for existing device */
	/* XXX imp XXX */
	if (unit != -1) {
		if (unit >= 0 && unit < dc->maxunit &&
		    dc->devices[unit] != NULL) {
			if (bootverbose)
				printf("%s: %s%d already exists; skipping it\n",
				    dc->name, dc->name, *unitp);
			return (EEXIST);
		}
	} else {
		/* Unwired device, find the next available slot for it */
		unit = 0;
		for (unit = 0;; unit++) {
			/* If there is an "at" hint for a unit then skip it. */
			if (resource_string_value(dc->name, unit, "at", &s) ==
			    0)
				continue;

			/* If this device slot is already in use, skip it. */
			if (unit < dc->maxunit && dc->devices[unit] != NULL)
				continue;

			break;
		}
	}

	/*
	 * We've selected a unit beyond the length of the table, so let's
	 * extend the table to make room for all units up to and including
	 * this one.
	 */
	if (unit >= dc->maxunit) {
		device_t *newlist, *oldlist;
		int newsize;

		oldlist = dc->devices;
		newsize = roundup((unit + 1), MINALLOCSIZE / sizeof(device_t));
		newlist = malloc(sizeof(device_t) * newsize, M_BUS, M_NOWAIT);
		if (!newlist)
			return (ENOMEM);
		if (oldlist != NULL)
			bcopy(oldlist, newlist, sizeof(device_t) * dc->maxunit);
		bzero(newlist + dc->maxunit,
		    sizeof(device_t) * (newsize - dc->maxunit));
		dc->devices = newlist;
		dc->maxunit = newsize;
		if (oldlist != NULL)
			free(oldlist, M_BUS);
	}
	PDEBUG(("now: unit %d in devclass %s", unit, DEVCLANAME(dc)));

	*unitp = unit;
	return (0);
}