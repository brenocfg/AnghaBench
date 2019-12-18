#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint16_t ;
typedef  TYPE_2__* device_t ;
typedef  int /*<<< orphan*/  attachentropy ;
struct TYPE_18__ {int unit; int flags; scalar_t__ busy; int /*<<< orphan*/  state; int /*<<< orphan*/  devclass; TYPE_1__* driver; int /*<<< orphan*/  parent; } ;
struct TYPE_17__ {char* name; } ;

/* Variables and functions */
 int DEVICE_ATTACH (TYPE_2__*) ; 
 int DF_ATTACHED_ONCE ; 
 int DF_DONENOMATCH ; 
 int DF_FIXEDCLASS ; 
 int /*<<< orphan*/  DS_ATTACHED ; 
 int /*<<< orphan*/  DS_ATTACHING ; 
 int /*<<< orphan*/  DS_BUSY ; 
 int /*<<< orphan*/  DS_NOTPRESENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (int (*) (TYPE_2__*),TYPE_2__*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RANDOM_ATTACH ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  devadded (TYPE_2__*) ; 
 int /*<<< orphan*/  devclass_delete_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  device_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  device_is_quiet (TYPE_2__*) ; 
 int /*<<< orphan*/  device_print_child (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  device_printf (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  device_set_driver (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_sysctl_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  device_sysctl_init (TYPE_2__*) ; 
 int /*<<< orphan*/  device_sysctl_update (TYPE_2__*) ; 
 scalar_t__ get_cyclecount () ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 int /*<<< orphan*/  random_harvest_direct (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_disabled (char*,int) ; 

int
device_attach(device_t dev)
{
	uint64_t attachtime;
	uint16_t attachentropy;
	int error;

	if (resource_disabled(dev->driver->name, dev->unit)) {
		device_disable(dev);
		if (bootverbose)
			 device_printf(dev, "disabled via hints entry\n");
		return (ENXIO);
	}

	device_sysctl_init(dev);
	if (!device_is_quiet(dev))
		device_print_child(dev->parent, dev);
	attachtime = get_cyclecount();
	dev->state = DS_ATTACHING;
	if ((error = DEVICE_ATTACH(dev)) != 0) {
		printf("device_attach: %s%d attach returned %d\n",
		    dev->driver->name, dev->unit, error);
		if (!(dev->flags & DF_FIXEDCLASS))
			devclass_delete_device(dev->devclass, dev);
		(void)device_set_driver(dev, NULL);
		device_sysctl_fini(dev);
		KASSERT(dev->busy == 0, ("attach failed but busy"));
		dev->state = DS_NOTPRESENT;
		return (error);
	}
	dev->flags |= DF_ATTACHED_ONCE;
	/* We only need the low bits of this time, but ranges from tens to thousands
	 * have been seen, so keep 2 bytes' worth.
	 */
	attachentropy = (uint16_t)(get_cyclecount() - attachtime);
	random_harvest_direct(&attachentropy, sizeof(attachentropy), RANDOM_ATTACH);
	device_sysctl_update(dev);
	if (dev->busy)
		dev->state = DS_BUSY;
	else
		dev->state = DS_ATTACHED;
	dev->flags &= ~DF_DONENOMATCH;
	EVENTHANDLER_DIRECT_INVOKE(device_attach, dev);
	devadded(dev);
	return (0);
}