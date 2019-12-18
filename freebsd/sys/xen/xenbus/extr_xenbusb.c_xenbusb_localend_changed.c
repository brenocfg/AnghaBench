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
struct xenbus_device_ivars {int /*<<< orphan*/  xd_lock; int /*<<< orphan*/  xd_node; int /*<<< orphan*/  xd_state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  XENBUS_LOCALEND_CHANGED (int /*<<< orphan*/ ,char const*) ; 
 struct xenbus_device_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_read_driver_state (int /*<<< orphan*/ ) ; 

void
xenbusb_localend_changed(device_t bus, device_t child, const char *path)
{

	if (strcmp(path, "/state") != 0) {
		struct xenbus_device_ivars *ivars;

		ivars = device_get_ivars(child);
		sx_xlock(&ivars->xd_lock);
		ivars->xd_state = xenbus_read_driver_state(ivars->xd_node);
		sx_xunlock(&ivars->xd_lock);
	}
	XENBUS_LOCALEND_CHANGED(child, path);
}