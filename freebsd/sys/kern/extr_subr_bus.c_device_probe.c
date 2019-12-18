#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_8__ {scalar_t__ state; int flags; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ BUS_PASS_DEFAULT ; 
 int /*<<< orphan*/  BUS_PROBE_NOMATCH (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int DF_DONENOMATCH ; 
 int DF_ENABLED ; 
 int DF_REBID ; 
 scalar_t__ DS_ALIVE ; 
 int /*<<< orphan*/  GIANT_REQUIRED ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_current_pass ; 
 int /*<<< orphan*/ * device_get_name (TYPE_1__*) ; 
 int /*<<< orphan*/  device_print_prettyname (TYPE_1__*) ; 
 int device_probe_child (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  devnomatch (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
device_probe(device_t dev)
{
	int error;

	GIANT_REQUIRED;

	if (dev->state >= DS_ALIVE && (dev->flags & DF_REBID) == 0)
		return (-1);

	if (!(dev->flags & DF_ENABLED)) {
		if (bootverbose && device_get_name(dev) != NULL) {
			device_print_prettyname(dev);
			printf("not probed (disabled)\n");
		}
		return (-1);
	}
	if ((error = device_probe_child(dev->parent, dev)) != 0) {
		if (bus_current_pass == BUS_PASS_DEFAULT &&
		    !(dev->flags & DF_DONENOMATCH)) {
			BUS_PROBE_NOMATCH(dev->parent, dev);
			devnomatch(dev);
			dev->flags |= DF_DONENOMATCH;
		}
		return (error);
	}
	return (0);
}