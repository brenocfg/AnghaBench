#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {void* kb_data; } ;
struct ckb_softc {int cols; int /*<<< orphan*/  sc_repeat_callout; int /*<<< orphan*/ * sc_fkeymap; int /*<<< orphan*/  sc_accmap; int /*<<< orphan*/  sc_keymap; scalar_t__* scan; scalar_t__* scan_local; TYPE_1__ sc_kbd; int /*<<< orphan*/  gpio; int /*<<< orphan*/  rows; int /*<<< orphan*/  dev; int /*<<< orphan*/ * gpio_dev; int /*<<< orphan*/ * keymap; } ;
typedef  TYPE_1__ keyboard_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CKB_NFKEY ; 
 int ENXIO ; 
 int /*<<< orphan*/  KBD_CONFIG_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  KBD_DRIVER_NAME ; 
 int /*<<< orphan*/  KBD_FOUND_DEVICE (TYPE_1__*) ; 
 int /*<<< orphan*/  KBD_INIT_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  KBD_PROBE_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  KB_OTHER ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  accent_map ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ckb_clear_state (TYPE_1__*) ; 
 int /*<<< orphan*/  ckb_ec_intr ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ckb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * fkey_tab ; 
 int /*<<< orphan*/  kbd_init_struct (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kbd_register (TYPE_1__*) ; 
 int /*<<< orphan*/  kbd_set_maps (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  key_map ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ckb_softc*) ; 
 int parse_dts (struct ckb_softc*) ; 

__attribute__((used)) static int
chrome_kb_attach(device_t dev)
{
	struct ckb_softc *sc;
	keyboard_t *kbd;
	int error;
	int rid;
	int i;

	sc = device_get_softc(dev);

	sc->dev = dev;
	sc->keymap = NULL;

	if ((error = parse_dts(sc)) != 0)
		return error;

	sc->gpio_dev = devclass_get_device(devclass_find("gpio"), 0);
	if (sc->gpio_dev == NULL) {
		device_printf(sc->dev, "Can't find gpio device.\n");
		return (ENXIO);
	}

#if 0
	device_printf(sc->dev, "Keyboard matrix [%dx%d]\n",
	    sc->cols, sc->rows);
#endif

	pad_setup_intr(sc->gpio, ckb_ec_intr, sc);

	kbd = &sc->sc_kbd;
	rid = 0;

	sc->scan_local = malloc(sc->cols, M_DEVBUF, M_NOWAIT);
	sc->scan = malloc(sc->cols, M_DEVBUF, M_NOWAIT);

	for (i = 0; i < sc->cols; i++) {
		sc->scan_local[i] = 0;
		sc->scan[i] = 0;
	}

	kbd_init_struct(kbd, KBD_DRIVER_NAME, KB_OTHER,
	    device_get_unit(dev), 0, 0, 0);
	kbd->kb_data = (void *)sc;

	sc->sc_keymap = key_map;
        sc->sc_accmap = accent_map;
	for (i = 0; i < CKB_NFKEY; i++) {
		sc->sc_fkeymap[i] = fkey_tab[i];
        }

	kbd_set_maps(kbd, &sc->sc_keymap, &sc->sc_accmap,
	    sc->sc_fkeymap, CKB_NFKEY);

	KBD_FOUND_DEVICE(kbd);
	ckb_clear_state(kbd);
	KBD_PROBE_DONE(kbd);

	callout_init(&sc->sc_repeat_callout, 0);

	KBD_INIT_DONE(kbd);

	if (kbd_register(kbd) < 0) {
		return (ENXIO);
	}
	KBD_CONFIG_DONE(kbd);

	return (0);
}