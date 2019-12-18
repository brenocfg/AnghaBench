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
struct TYPE_2__ {void* ich_arg; int /*<<< orphan*/  ich_func; } ;
struct twl_vreg_softc {TYPE_1__ sc_init_hook; int /*<<< orphan*/  sc_vreg_list; int /*<<< orphan*/  sc_pdev; void* sc_dev; } ;
typedef  void* device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TWL_VREG_LOCK_INIT (struct twl_vreg_softc*) ; 
 scalar_t__ config_intrhook_establish (TYPE_1__*) ; 
 int /*<<< orphan*/  device_get_parent (void*) ; 
 struct twl_vreg_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  twl_vreg_init ; 

__attribute__((used)) static int
twl_vreg_attach(device_t dev)
{
	struct twl_vreg_softc *sc;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_pdev = device_get_parent(dev);

	TWL_VREG_LOCK_INIT(sc);

	LIST_INIT(&sc->sc_vreg_list);

	/* We have to wait until interrupts are enabled. I2C read and write
	 * only works if the interrupts are available.
	 */
	sc->sc_init_hook.ich_func = twl_vreg_init;
	sc->sc_init_hook.ich_arg = dev;

	if (config_intrhook_establish(&sc->sc_init_hook) != 0)
		return (ENOMEM);

	return (0);
}