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
typedef  int /*<<< orphan*/  xen_intr_handle_t ;
struct xenisrc {scalar_t__ xi_close; } ;
typedef  int /*<<< orphan*/  evtchn_port_t ;
typedef  enum intr_type { ____Placeholder_intr_type } intr_type ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVTCHN_TYPE_PORT ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int xen_intr_bind_isrc (struct xenisrc**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 

int
xen_intr_bind_local_port(device_t dev, evtchn_port_t local_port,
    driver_filter_t filter, driver_intr_t handler, void *arg,
    enum intr_type flags, xen_intr_handle_t *port_handlep)
{
	struct xenisrc *isrc;
	int error;

	error = xen_intr_bind_isrc(&isrc, local_port, EVTCHN_TYPE_PORT,
	    device_get_nameunit(dev), filter, handler, arg, flags,
	    port_handlep);
	if (error != 0)
		return (error);

	/*
	 * The Event Channel API didn't open this port, so it is not
	 * responsible for closing it automatically on unbind.
	 */
	isrc->xi_close = 0;
	return (0);
}