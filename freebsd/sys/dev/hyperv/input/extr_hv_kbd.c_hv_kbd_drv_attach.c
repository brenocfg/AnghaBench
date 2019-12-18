#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {void* kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* enable ) (TYPE_1__*) ;} ;
typedef  TYPE_2__ keyboard_switch_t ;
struct TYPE_19__ {int /*<<< orphan*/  sc_mode; TYPE_1__ sc_kbd; } ;
typedef  TYPE_3__ hv_kbd_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  HVKBD_DRIVER_NAME ; 
 int /*<<< orphan*/  KBD_CONFIG_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  KBD_FOUND_DEVICE (TYPE_1__*) ; 
 int /*<<< orphan*/  KBD_INIT_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  KBD_PROBE_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  KB_OTHER ; 
 int /*<<< orphan*/  K_RAW ; 
 int /*<<< orphan*/  accent_map ; 
 scalar_t__ bootverbose ; 
 TYPE_3__* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fkey_tab ; 
 int /*<<< orphan*/  genkbd_diag (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  hv_kbd_drv_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hvkbd_clear_state (TYPE_1__*) ; 
 scalar_t__ kbd_attach (TYPE_1__*) ; 
 TYPE_2__* kbd_get_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_init_struct (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kbd_register (TYPE_1__*) ; 
 int /*<<< orphan*/  kbd_set_maps (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_map ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

int
hv_kbd_drv_attach(device_t dev)
{
	hv_kbd_sc *sc = device_get_softc(dev);
	int unit = device_get_unit(dev);
	keyboard_t *kbd = &sc->sc_kbd;
	keyboard_switch_t *sw;
	sw = kbd_get_switch(HVKBD_DRIVER_NAME);
	if (sw == NULL) {
		return (ENXIO);
	}

	kbd_init_struct(kbd, HVKBD_DRIVER_NAME, KB_OTHER, unit, 0, 0, 0);
	kbd->kb_data = (void *)sc;
	kbd_set_maps(kbd, &key_map, &accent_map, fkey_tab, nitems(fkey_tab));
	KBD_FOUND_DEVICE(kbd);
	hvkbd_clear_state(kbd);
	KBD_PROBE_DONE(kbd);
	KBD_INIT_DONE(kbd);
	sc->sc_mode = K_RAW;
	(*sw->enable)(kbd);

	if (kbd_register(kbd) < 0) {
		goto detach;
	}
	KBD_CONFIG_DONE(kbd);
#ifdef KBD_INSTALL_CDEV
        if (kbd_attach(kbd)) {
		goto detach;
	}
#endif
	if (bootverbose) {
		genkbd_diag(kbd, bootverbose);
	}
	return (0);
detach:
	hv_kbd_drv_detach(dev);
	return (ENXIO);
}