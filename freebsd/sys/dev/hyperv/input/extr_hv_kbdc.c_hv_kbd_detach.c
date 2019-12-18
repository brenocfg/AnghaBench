#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * hs_xact_ctx; } ;
typedef  TYPE_1__ hv_kbd_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hv_kbd_detach1 (int /*<<< orphan*/ ) ; 
 int hv_kbd_drv_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_kbd_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  vmbus_xact_ctx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hv_kbd_detach(device_t dev)
{
	int ret;
	hv_kbd_sc *sc = device_get_softc(dev);
	hv_kbd_fini(sc);
	if (sc->hs_xact_ctx != NULL)
		vmbus_xact_ctx_destroy(sc->hs_xact_ctx);
	ret = hv_kbd_detach1(dev);
	if (!ret)
		device_printf(dev, "Fail to detach\n");
	return hv_kbd_drv_detach(dev);
}