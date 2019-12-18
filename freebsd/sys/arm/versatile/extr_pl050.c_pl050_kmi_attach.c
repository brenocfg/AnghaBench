#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {void* kb_data; } ;
struct kmi_softc {int /*<<< orphan*/ * sc_fkeymap; int /*<<< orphan*/  sc_accmap; int /*<<< orphan*/  sc_keymap; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/  sc_intr_hl; int /*<<< orphan*/ * sc_mem_res; TYPE_1__ sc_kbd; int /*<<< orphan*/  sc_dev; } ;
typedef  TYPE_1__ keyboard_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 int /*<<< orphan*/  KBD_CONFIG_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  KBD_FOUND_DEVICE (TYPE_1__*) ; 
 int /*<<< orphan*/  KBD_INIT_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  KBD_PROBE_DONE (TYPE_1__*) ; 
 int /*<<< orphan*/  KB_OTHER ; 
 int /*<<< orphan*/  KMICR ; 
 int KMICR_EN ; 
 int KMICR_RXINTREN ; 
 int /*<<< orphan*/  KMIDATA ; 
 int /*<<< orphan*/  KMI_DRIVER_NAME ; 
 int KMI_NFKEY ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int SET_SCANCODE_SET ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  accent_map ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kmi_softc*,int /*<<< orphan*/ *) ; 
 struct kmi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fkey_tab ; 
 int /*<<< orphan*/  genkbd_diag (TYPE_1__*,scalar_t__) ; 
 scalar_t__ kbd_attach (TYPE_1__*) ; 
 int /*<<< orphan*/  kbd_init_struct (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kbd_register (TYPE_1__*) ; 
 int /*<<< orphan*/  kbd_set_maps (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  key_map ; 
 int kmi_attached ; 
 int /*<<< orphan*/  kmi_clear_state (TYPE_1__*) ; 
 int /*<<< orphan*/  pl050_kmi_intr ; 
 int /*<<< orphan*/  pl050_kmi_read_4 (struct kmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl050_kmi_write_4 (struct kmi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pl050_kmi_attach(device_t dev)
{
	struct kmi_softc *sc = device_get_softc(dev);
	keyboard_t *kbd;
	int rid;
	int i;
	uint32_t ack;

	sc->sc_dev = dev;
	kbd = &sc->sc_kbd;
	rid = 0;

	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "could not allocate memory resource\n");
		return (ENXIO);
	}

	/* Request the IRQ resources */
	sc->sc_irq_res =  bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (sc->sc_irq_res == NULL) {
		device_printf(dev, "Error: could not allocate irq resources\n");
		return (ENXIO);
	}

	/* Setup and enable the timer */
	if (bus_setup_intr(dev, sc->sc_irq_res, INTR_TYPE_CLK,
			NULL, pl050_kmi_intr, sc,
			&sc->sc_intr_hl) != 0) {
		bus_release_resource(dev, SYS_RES_IRQ, rid,
			sc->sc_irq_res);
		device_printf(dev, "Unable to setup the clock irq handler.\n");
		return (ENXIO);
	}

	/* TODO: clock & divisor */

	pl050_kmi_write_4(sc, KMICR, KMICR_EN);

	pl050_kmi_write_4(sc, KMIDATA, SET_SCANCODE_SET);
	/* read out ACK */
	ack = pl050_kmi_read_4(sc, KMIDATA);
	/* Set Scan Code set 1 (XT) */
	pl050_kmi_write_4(sc, KMIDATA, 1);
	/* read out ACK */
	ack = pl050_kmi_read_4(sc, KMIDATA);

	pl050_kmi_write_4(sc, KMICR, KMICR_EN | KMICR_RXINTREN);

	kbd_init_struct(kbd, KMI_DRIVER_NAME, KB_OTHER, 
			device_get_unit(dev), 0, 0, 0);
	kbd->kb_data = (void *)sc;

	sc->sc_keymap = key_map;
	sc->sc_accmap = accent_map;
	for (i = 0; i < KMI_NFKEY; i++) {
		sc->sc_fkeymap[i] = fkey_tab[i];
	}

	kbd_set_maps(kbd, &sc->sc_keymap, &sc->sc_accmap,
	    sc->sc_fkeymap, KMI_NFKEY);

	KBD_FOUND_DEVICE(kbd);
	kmi_clear_state(kbd);
	KBD_PROBE_DONE(kbd);

	KBD_INIT_DONE(kbd);

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
	kmi_attached = 1;
	return (0);

detach:
	return (ENXIO);

}