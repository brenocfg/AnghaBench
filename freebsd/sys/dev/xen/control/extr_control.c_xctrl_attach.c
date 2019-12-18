#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* node; uintptr_t callback_data; int /*<<< orphan*/  callback; } ;
struct xctrl_softc {TYPE_1__ xctrl_watch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 struct xctrl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  xctrl_on_watch_event ; 
 scalar_t__ xen_pv_domain () ; 
 int /*<<< orphan*/  xen_pv_shutdown_final ; 
 int /*<<< orphan*/  xs_register_watch (TYPE_1__*) ; 

__attribute__((used)) static int
xctrl_attach(device_t dev)
{
	struct xctrl_softc *xctrl;

	xctrl = device_get_softc(dev);

	/* Activate watch */
	xctrl->xctrl_watch.node = "control/shutdown";
	xctrl->xctrl_watch.callback = xctrl_on_watch_event;
	xctrl->xctrl_watch.callback_data = (uintptr_t)xctrl;
	xs_register_watch(&xctrl->xctrl_watch);

	if (xen_pv_domain())
		EVENTHANDLER_REGISTER(shutdown_final, xen_pv_shutdown_final, NULL,
		                      SHUTDOWN_PRI_LAST);

	return (0);
}