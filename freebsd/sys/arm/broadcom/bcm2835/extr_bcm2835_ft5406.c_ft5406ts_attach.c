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
struct TYPE_2__ {struct ft5406ts_softc* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct ft5406ts_softc {TYPE_1__ sc_init_hook; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FT5406_LOCK_DESTROY (struct ft5406ts_softc*) ; 
 int /*<<< orphan*/  FT5406_LOCK_INIT (struct ft5406ts_softc*) ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 struct ft5406ts_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ft5406ts_init ; 

__attribute__((used)) static int
ft5406ts_attach(device_t dev)
{
	struct ft5406ts_softc *sc;

	/* set self dev */
	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	/* register callback for using mbox when interrupts are enabled */
	sc->sc_init_hook.ich_func = ft5406ts_init;
	sc->sc_init_hook.ich_arg = sc;

	FT5406_LOCK_INIT(sc);

	if (config_intrhook_establish(&sc->sc_init_hook) != 0) {
		device_printf(dev, "config_intrhook_establish failed\n");
		FT5406_LOCK_DESTROY(sc);
		return (ENOMEM);
	}

	return (0);
}