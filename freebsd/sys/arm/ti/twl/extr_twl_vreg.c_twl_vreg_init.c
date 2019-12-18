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
struct twl_vreg_softc {int /*<<< orphan*/  sc_init_hook; int /*<<< orphan*/  sc_pdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TWL_VREG_XLOCK (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_XUNLOCK (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct twl_vreg_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_regulators ; 
 int /*<<< orphan*/  twl6030_regulators ; 
 scalar_t__ twl_is_4030 (int /*<<< orphan*/ ) ; 
 scalar_t__ twl_is_6025 (int /*<<< orphan*/ ) ; 
 scalar_t__ twl_is_6030 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl_vreg_add_regulators (struct twl_vreg_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
twl_vreg_init(void *dev)
{
	struct twl_vreg_softc *sc;

	sc = device_get_softc((device_t)dev);

	TWL_VREG_XLOCK(sc);

	if (twl_is_4030(sc->sc_pdev))
		twl_vreg_add_regulators(sc, twl4030_regulators);
	else if (twl_is_6030(sc->sc_pdev) || twl_is_6025(sc->sc_pdev))
		twl_vreg_add_regulators(sc, twl6030_regulators);

	TWL_VREG_XUNLOCK(sc);

	config_intrhook_disestablish(&sc->sc_init_hook);
}