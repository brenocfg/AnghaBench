#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  devclass_t ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 scalar_t__ LOGICALID_PCM ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_devclass (int /*<<< orphan*/ *) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ *) ; 
 scalar_t__ isa_get_serial (int /*<<< orphan*/ *) ; 
 scalar_t__ isa_get_vendorid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
find_masterdev(sc_p scp)
{
	int i, units;
	devclass_t devclass;
	device_t dev;

	devclass = device_get_devclass(scp->dev);
	units = devclass_get_maxunit(devclass);
	dev = NULL;
	for (i = 0 ; i < units ; i++) {
		dev = devclass_get_device(devclass, i);
		if (isa_get_vendorid(dev) == isa_get_vendorid(scp->dev)
		    && isa_get_logicalid(dev) == LOGICALID_PCM
		    && isa_get_serial(dev) == isa_get_serial(scp->dev))
			break;
	}
	if (i == units)
		return (NULL);

	return (dev);
}