#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_18__ ;

/* Type definitions */
typedef  int u_long ;
struct thread {int dummy; } ;
struct devreq {int dr_flags; int /*<<< orphan*/  dr_data; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  driver ;
typedef  TYPE_2__* device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_31__ {int flags; int unit; TYPE_18__* devclass; int /*<<< orphan*/ * parent; TYPE_1__* driver; } ;
struct TYPE_30__ {int /*<<< orphan*/  name; } ;
struct TYPE_29__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BUS_RESCAN (TYPE_2__*) ; 
 int BUS_RESET_CHILD (TYPE_2__*,TYPE_2__*,int) ; 
 int BUS_RESUME_CHILD (TYPE_2__*,TYPE_2__*) ; 
 int BUS_SUSPEND_CHILD (TYPE_2__*,TYPE_2__*) ; 
 int DEVF_CLEAR_DRIVER_DETACH ; 
 int DEVF_FORCE_DELETE ; 
 int DEVF_FORCE_DETACH ; 
 int DEVF_RESET_DETACH ; 
 int DEVF_SET_DRIVER_DETACH ; 
#define  DEV_ATTACH 140 
#define  DEV_CLEAR_DRIVER 139 
#define  DEV_DELETE 138 
#define  DEV_DETACH 137 
#define  DEV_DISABLE 136 
#define  DEV_ENABLE 135 
#define  DEV_FREEZE 134 
#define  DEV_RESCAN 133 
#define  DEV_RESET 132 
#define  DEV_RESUME 131 
#define  DEV_SET_DRIVER 130 
#define  DEV_SUSPEND 129 
#define  DEV_THAW 128 
 int DF_FIXEDCLASS ; 
 int DF_REBID ; 
 int DF_WILDCARD ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOTTY ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  PRIV_DRIVER ; 
 int /*<<< orphan*/  bus_child_present (TYPE_2__*) ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int devclass_add_device (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * devclass_create (char*) ; 
 int /*<<< orphan*/  devclass_delete_device (TYPE_18__*,TYPE_2__*) ; 
 int device_attach (TYPE_2__*) ; 
 int device_delete_child (TYPE_2__*,TYPE_2__*) ; 
 int device_detach (TYPE_2__*) ; 
 int /*<<< orphan*/  device_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  device_do_deferred_actions () ; 
 int /*<<< orphan*/  device_enable (TYPE_2__*) ; 
 int device_frozen ; 
 TYPE_2__* device_get_parent (TYPE_2__*) ; 
 int /*<<< orphan*/  device_is_alive (TYPE_2__*) ; 
 int /*<<< orphan*/  device_is_attached (TYPE_2__*) ; 
 int /*<<< orphan*/  device_is_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  device_is_suspended (TYPE_2__*) ; 
 int device_probe_and_attach (TYPE_2__*) ; 
 int device_quiesce (TYPE_2__*) ; 
 int /*<<< orphan*/  driver_exists (int /*<<< orphan*/ *,char*) ; 
 int find_device (struct devreq*,TYPE_2__**) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_disabled (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_unset_value (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
devctl2_ioctl(struct cdev *cdev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	struct devreq *req;
	device_t dev;
	int error, old;

	/* Locate the device to control. */
	mtx_lock(&Giant);
	req = (struct devreq *)data;
	switch (cmd) {
	case DEV_ATTACH:
	case DEV_DETACH:
	case DEV_ENABLE:
	case DEV_DISABLE:
	case DEV_SUSPEND:
	case DEV_RESUME:
	case DEV_SET_DRIVER:
	case DEV_CLEAR_DRIVER:
	case DEV_RESCAN:
	case DEV_DELETE:
	case DEV_RESET:
		error = priv_check(td, PRIV_DRIVER);
		if (error == 0)
			error = find_device(req, &dev);
		break;
	case DEV_FREEZE:
	case DEV_THAW:
		error = priv_check(td, PRIV_DRIVER);
		break;
	default:
		error = ENOTTY;
		break;
	}
	if (error) {
		mtx_unlock(&Giant);
		return (error);
	}

	/* Perform the requested operation. */
	switch (cmd) {
	case DEV_ATTACH:
		if (device_is_attached(dev) && (dev->flags & DF_REBID) == 0)
			error = EBUSY;
		else if (!device_is_enabled(dev))
			error = ENXIO;
		else
			error = device_probe_and_attach(dev);
		break;
	case DEV_DETACH:
		if (!device_is_attached(dev)) {
			error = ENXIO;
			break;
		}
		if (!(req->dr_flags & DEVF_FORCE_DETACH)) {
			error = device_quiesce(dev);
			if (error)
				break;
		}
		error = device_detach(dev);
		break;
	case DEV_ENABLE:
		if (device_is_enabled(dev)) {
			error = EBUSY;
			break;
		}

		/*
		 * If the device has been probed but not attached (e.g.
		 * when it has been disabled by a loader hint), just
		 * attach the device rather than doing a full probe.
		 */
		device_enable(dev);
		if (device_is_alive(dev)) {
			/*
			 * If the device was disabled via a hint, clear
			 * the hint.
			 */
			if (resource_disabled(dev->driver->name, dev->unit))
				resource_unset_value(dev->driver->name,
				    dev->unit, "disabled");
			error = device_attach(dev);
		} else
			error = device_probe_and_attach(dev);
		break;
	case DEV_DISABLE:
		if (!device_is_enabled(dev)) {
			error = ENXIO;
			break;
		}

		if (!(req->dr_flags & DEVF_FORCE_DETACH)) {
			error = device_quiesce(dev);
			if (error)
				break;
		}

		/*
		 * Force DF_FIXEDCLASS on around detach to preserve
		 * the existing name.
		 */
		old = dev->flags;
		dev->flags |= DF_FIXEDCLASS;
		error = device_detach(dev);
		if (!(old & DF_FIXEDCLASS))
			dev->flags &= ~DF_FIXEDCLASS;
		if (error == 0)
			device_disable(dev);
		break;
	case DEV_SUSPEND:
		if (device_is_suspended(dev)) {
			error = EBUSY;
			break;
		}
		if (device_get_parent(dev) == NULL) {
			error = EINVAL;
			break;
		}
		error = BUS_SUSPEND_CHILD(device_get_parent(dev), dev);
		break;
	case DEV_RESUME:
		if (!device_is_suspended(dev)) {
			error = EINVAL;
			break;
		}
		if (device_get_parent(dev) == NULL) {
			error = EINVAL;
			break;
		}
		error = BUS_RESUME_CHILD(device_get_parent(dev), dev);
		break;
	case DEV_SET_DRIVER: {
		devclass_t dc;
		char driver[128];

		error = copyinstr(req->dr_data, driver, sizeof(driver), NULL);
		if (error)
			break;
		if (driver[0] == '\0') {
			error = EINVAL;
			break;
		}
		if (dev->devclass != NULL &&
		    strcmp(driver, dev->devclass->name) == 0)
			/* XXX: Could possibly force DF_FIXEDCLASS on? */
			break;

		/*
		 * Scan drivers for this device's bus looking for at
		 * least one matching driver.
		 */
		if (dev->parent == NULL) {
			error = EINVAL;
			break;
		}
		if (!driver_exists(dev->parent, driver)) {
			error = ENOENT;
			break;
		}
		dc = devclass_create(driver);
		if (dc == NULL) {
			error = ENOMEM;
			break;
		}

		/* Detach device if necessary. */
		if (device_is_attached(dev)) {
			if (req->dr_flags & DEVF_SET_DRIVER_DETACH)
				error = device_detach(dev);
			else
				error = EBUSY;
			if (error)
				break;
		}

		/* Clear any previously-fixed device class and unit. */
		if (dev->flags & DF_FIXEDCLASS)
			devclass_delete_device(dev->devclass, dev);
		dev->flags |= DF_WILDCARD;
		dev->unit = -1;

		/* Force the new device class. */
		error = devclass_add_device(dc, dev);
		if (error)
			break;
		dev->flags |= DF_FIXEDCLASS;
		error = device_probe_and_attach(dev);
		break;
	}
	case DEV_CLEAR_DRIVER:
		if (!(dev->flags & DF_FIXEDCLASS)) {
			error = 0;
			break;
		}
		if (device_is_attached(dev)) {
			if (req->dr_flags & DEVF_CLEAR_DRIVER_DETACH)
				error = device_detach(dev);
			else
				error = EBUSY;
			if (error)
				break;
		}

		dev->flags &= ~DF_FIXEDCLASS;
		dev->flags |= DF_WILDCARD;
		devclass_delete_device(dev->devclass, dev);
		error = device_probe_and_attach(dev);
		break;
	case DEV_RESCAN:
		if (!device_is_attached(dev)) {
			error = ENXIO;
			break;
		}
		error = BUS_RESCAN(dev);
		break;
	case DEV_DELETE: {
		device_t parent;

		parent = device_get_parent(dev);
		if (parent == NULL) {
			error = EINVAL;
			break;
		}
		if (!(req->dr_flags & DEVF_FORCE_DELETE)) {
			if (bus_child_present(dev) != 0) {
				error = EBUSY;
				break;
			}
		}
		
		error = device_delete_child(parent, dev);
		break;
	}
	case DEV_FREEZE:
		if (device_frozen)
			error = EBUSY;
		else
			device_frozen = true;
		break;
	case DEV_THAW:
		if (!device_frozen)
			error = EBUSY;
		else {
			device_do_deferred_actions();
			device_frozen = false;
		}
		break;
	case DEV_RESET:
		if ((req->dr_flags & ~(DEVF_RESET_DETACH)) != 0) {
			error = EINVAL;
			break;
		}
		error = BUS_RESET_CHILD(device_get_parent(dev), dev,
		    req->dr_flags);
		break;
	}
	mtx_unlock(&Giant);
	return (error);
}