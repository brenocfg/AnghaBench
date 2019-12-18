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
struct xctrl_softc {int /*<<< orphan*/  xctrl_watch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct xctrl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xs_unregister_watch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xctrl_detach(device_t dev)
{
	struct xctrl_softc *xctrl;

	xctrl = device_get_softc(dev);

	/* Release watch */
	xs_unregister_watch(&xctrl->xctrl_watch);

	return (0);
}