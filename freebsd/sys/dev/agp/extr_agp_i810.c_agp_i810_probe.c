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
struct agp_i810_match {TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {int (* check_active ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_desc ) (int /*<<< orphan*/ *,struct agp_i810_match const*) ;} ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 int /*<<< orphan*/ * agp_i810_find_bridge (int /*<<< orphan*/ *) ; 
 struct agp_i810_match* agp_i810_match (int /*<<< orphan*/ *) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct agp_i810_match const*) ; 

__attribute__((used)) static int
agp_i810_probe(device_t dev)
{
	device_t bdev;
	const struct agp_i810_match *match;
	int err;

	if (resource_disabled("agp", device_get_unit(dev)))
		return (ENXIO);
	match = agp_i810_match(dev);
	if (match == NULL)
		return (ENXIO);

	bdev = agp_i810_find_bridge(dev);
	if (bdev == NULL) {
		if (bootverbose)
			printf("I810: can't find bridge device\n");
		return (ENXIO);
	}

	/*
	 * checking whether internal graphics device has been activated.
	 */
	err = match->driver->check_active(bdev);
	if (err != 0) {
		if (bootverbose)
			printf("i810: disabled, not probing\n");
		return (err);
	}

	match->driver->set_desc(dev, match);
	return (BUS_PROBE_DEFAULT);
}