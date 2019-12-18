#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kobj_t ;
typedef  TYPE_1__* device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;
struct TYPE_9__ {int unit; int flags; int /*<<< orphan*/  state; int /*<<< orphan*/ * softc; int /*<<< orphan*/ * ivars; scalar_t__ order; scalar_t__ devflags; scalar_t__ busy; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * nameunit; int /*<<< orphan*/ * devclass; int /*<<< orphan*/ * driver; int /*<<< orphan*/  children; struct TYPE_9__* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICENAME (TYPE_1__*) ; 
 int DF_ENABLED ; 
 int DF_FIXEDCLASS ; 
 int DF_QUIET ; 
 int DF_QUIET_CHILDREN ; 
 int DF_WILDCARD ; 
 int /*<<< orphan*/  DS_NOTPRESENT ; 
 int /*<<< orphan*/  M_BUS ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_data_devices ; 
 int /*<<< orphan*/  bus_data_generation_update () ; 
 scalar_t__ devclass_add_device (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * devclass_find_internal (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ device_has_quiet_children (TYPE_1__*) ; 
 int /*<<< orphan*/  devlink ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  null_class ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static device_t
make_device(device_t parent, const char *name, int unit)
{
	device_t dev;
	devclass_t dc;

	PDEBUG(("%s at %s as unit %d", name, DEVICENAME(parent), unit));

	if (name) {
		dc = devclass_find_internal(name, NULL, TRUE);
		if (!dc) {
			printf("make_device: can't find device class %s\n",
			    name);
			return (NULL);
		}
	} else {
		dc = NULL;
	}

	dev = malloc(sizeof(*dev), M_BUS, M_NOWAIT|M_ZERO);
	if (!dev)
		return (NULL);

	dev->parent = parent;
	TAILQ_INIT(&dev->children);
	kobj_init((kobj_t) dev, &null_class);
	dev->driver = NULL;
	dev->devclass = NULL;
	dev->unit = unit;
	dev->nameunit = NULL;
	dev->desc = NULL;
	dev->busy = 0;
	dev->devflags = 0;
	dev->flags = DF_ENABLED;
	dev->order = 0;
	if (unit == -1)
		dev->flags |= DF_WILDCARD;
	if (name) {
		dev->flags |= DF_FIXEDCLASS;
		if (devclass_add_device(dc, dev)) {
			kobj_delete((kobj_t) dev, M_BUS);
			return (NULL);
		}
	}
	if (parent != NULL && device_has_quiet_children(parent))
		dev->flags |= DF_QUIET | DF_QUIET_CHILDREN;
	dev->ivars = NULL;
	dev->softc = NULL;

	dev->state = DS_NOTPRESENT;

	TAILQ_INSERT_TAIL(&bus_data_devices, dev, devlink);
	bus_data_generation_update();

	return (dev);
}