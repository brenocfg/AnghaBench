#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sc_kbd; } ;
typedef  TYPE_1__ hv_kbd_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ KBD_IS_CONFIGURED (int /*<<< orphan*/ *) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hvkbd_disable (int /*<<< orphan*/ *) ; 
 int kbd_detach (int /*<<< orphan*/ *) ; 
 int kbd_unregister (int /*<<< orphan*/ *) ; 

int
hv_kbd_drv_detach(device_t dev)
{
	int error = 0;
	hv_kbd_sc *sc = device_get_softc(dev);
	hvkbd_disable(&sc->sc_kbd);
	if (KBD_IS_CONFIGURED(&sc->sc_kbd)) {
		error = kbd_unregister(&sc->sc_kbd);
		if (error) {
			device_printf(dev, "WARNING: kbd_unregister() "
			    "returned non-zero! (ignored)\n");
		}
	}
#ifdef KBD_INSTALL_CDEV
	error = kbd_detach(&sc->sc_kbd);
#endif
	return (error);
}