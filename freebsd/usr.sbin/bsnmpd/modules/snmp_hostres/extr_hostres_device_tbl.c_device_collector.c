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
typedef  void* u_int ;
struct devinfo_dev {char* dd_name; char* dd_location; int /*<<< orphan*/  dd_drivername; int /*<<< orphan*/  dd_desc; scalar_t__ dd_parent; scalar_t__ dd_handle; } ;
struct device_entry {void* status; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRDBG (char*,...) ; 
 int /*<<< orphan*/  HR_DEVICE_FOUND ; 
 struct device_entry* device_entry_create_devinfo (struct devinfo_dev*) ; 
 struct device_entry* device_find_by_dev (struct devinfo_dev*) ; 
 scalar_t__ device_get_status (struct devinfo_dev*) ; 
 int /*<<< orphan*/  device_get_type (struct devinfo_dev*,int /*<<< orphan*/ *) ; 
 int devinfo_foreach_device_child (struct devinfo_dev*,int (*) (struct devinfo_dev*,void*),void*) ; 

__attribute__((used)) static int
device_collector(struct devinfo_dev *dev, void *arg)
{
	struct device_entry *entry;

	HRDBG("%llu/%llu name='%s' desc='%s' drivername='%s' location='%s'",
	    (unsigned long long)dev->dd_handle,
	    (unsigned long long)dev->dd_parent, dev->dd_name, dev->dd_desc,
	    dev->dd_drivername, dev->dd_location);

	if (dev->dd_name[0] != '\0' || dev->dd_location[0] != '\0') {
		HRDBG("ANALYZING dev %s at %s",
		    dev->dd_name, dev->dd_location);

		if ((entry = device_find_by_dev(dev)) != NULL) {
			entry->flags |= HR_DEVICE_FOUND;
			entry->status = (u_int)device_get_status(dev);
		} else if ((entry = device_entry_create_devinfo(dev)) != NULL) {
			device_get_type(dev, &entry->type);

			entry->flags |= HR_DEVICE_FOUND;
			entry->status = (u_int)device_get_status(dev);
		}
	} else {
		HRDBG("SKIPPED unknown device at location '%s'",
		    dev->dd_location );
	}

	return (devinfo_foreach_device_child(dev, device_collector, arg));
}