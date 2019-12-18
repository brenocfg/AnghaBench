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
struct xenbus_device {int const state; int /*<<< orphan*/  dev; int /*<<< orphan*/  otherend; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  XenbusStateClosed 131 
#define  XenbusStateClosing 130 
#define  XenbusStateConnected 129 
#define  XenbusStateInitialised 128 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xenbus_frontend_closed (struct xenbus_device*) ; 
 int /*<<< orphan*/  xenbus_read_unsigned (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int const) ; 

__attribute__((used)) static void backend_changed(struct xenbus_device *dev,
		enum xenbus_state backend_state)
{
	switch (backend_state) {
	case XenbusStateInitialised:
	case XenbusStateConnected:
		if (dev->state == XenbusStateConnected)
			break;

		if (!xenbus_read_unsigned(dev->otherend, "feature-protocol-v2",
					  0)) {
			xenbus_dev_fatal(dev, -EINVAL,
					"vTPM protocol 2 required");
			return;
		}
		xenbus_switch_state(dev, XenbusStateConnected);
		break;

	case XenbusStateClosing:
	case XenbusStateClosed:
		device_unregister(&dev->dev);
		xenbus_frontend_closed(dev);
		break;
	default:
		break;
	}
}