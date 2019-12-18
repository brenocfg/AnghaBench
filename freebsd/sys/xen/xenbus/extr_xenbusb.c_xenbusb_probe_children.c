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
struct xenbusb_softc {int dummy; } ;
struct xenbus_device_ivars {int /*<<< orphan*/  xd_local_watch; int /*<<< orphan*/  xd_otherend_watch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ DS_NOTPRESENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  XenbusStateClosed ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 struct xenbus_device_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct xenbusb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_state (int /*<<< orphan*/ ) ; 
 int device_probe_and_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbusb_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbusb_device_sysctl_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbusb_release_confighook (struct xenbusb_softc*) ; 
 int /*<<< orphan*/  xenbusb_verify_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_register_watch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xenbusb_probe_children(device_t dev)
{
	device_t *kids;
	struct xenbus_device_ivars *ivars;
	int i, count, error;

	if (device_get_children(dev, &kids, &count) == 0) {
		for (i = 0; i < count; i++) {
			if (device_get_state(kids[i]) != DS_NOTPRESENT) {
				/*
				 * We already know about this one.
				 * Make sure it's still here.
				 */
				xenbusb_verify_device(dev, kids[i]);
				continue;
			}

			error = device_probe_and_attach(kids[i]);
			if (error == ENXIO) {
				struct xenbusb_softc *xbs;

				/*
				 * We don't have a PV driver for this device.
				 * However, an emulated device we do support
				 * may share this backend.  Hide the node from
				 * XenBus until the next rescan, but leave it's
				 * state unchanged so we don't inadvertently
				 * prevent attachment of any emulated device.
				 */
				xenbusb_delete_child(dev, kids[i]);

				/*
				 * Since the XenStore state of this device
				 * still indicates a pending attach, manually
				 * release it's hold on the boot process.
				 */
				xbs = device_get_softc(dev);
				xenbusb_release_confighook(xbs);

				continue;
			} else if (error) {
				/*
				 * Transition device to the closed state
				 * so the world knows that attachment will
				 * not occur.
				 */
				xenbus_set_state(kids[i], XenbusStateClosed);

				/*
				 * Remove our record of this device.
				 * So long as it remains in the closed
				 * state in the XenStore, we will not find
				 * it again.  The state will only change
				 * if the control domain actively reconfigures
				 * this device.
				 */
				xenbusb_delete_child(dev, kids[i]);

				continue;
			}
			/*
			 * Augment default newbus provided dynamic sysctl
			 * variables with the standard ivar contents of
			 * XenBus devices.
			 */
			xenbusb_device_sysctl_init(kids[i]);

			/*
			 * Now that we have a driver managing this device
			 * that can receive otherend state change events,
			 * hook up a watch for them.
			 */
			ivars = device_get_ivars(kids[i]);
			xs_register_watch(&ivars->xd_otherend_watch);
			xs_register_watch(&ivars->xd_local_watch);
		}
		free(kids, M_TEMP);
	}

	return (0);
}