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
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ XenbusStateClosed ; 
 int /*<<< orphan*/  XenbusStateInitWait ; 
 int XenbusStateInitialising ; 
 scalar_t__ xenbus_dev_is_online (int /*<<< orphan*/ ) ; 
 scalar_t__ xenbus_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_set_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbusb_otherend_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
xenbusb_back_otherend_changed(device_t bus, device_t child,
			      enum xenbus_state peer_state)
{
	/* Perform default processing of state. */
	xenbusb_otherend_changed(bus, child, peer_state);

	/*
	 * "Online" devices are never fully detached in the
	 * newbus sense.  Only the front<->back connection is
	 * torn down.  If the front returns to the initialising
	 * state after closing a previous connection, signal
	 * our willingness to reconnect and that all necessary
	 * XenStore data for feature negotiation is present.
	 */
	if (peer_state == XenbusStateInitialising
	 && xenbus_dev_is_online(child) != 0
	 && xenbus_get_state(child) == XenbusStateClosed)
		xenbus_set_state(child, XenbusStateInitWait);
}