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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* power_on ) (TYPE_1__*) ;scalar_t__ power_off; int /*<<< orphan*/  flags; } ;
struct gdsc {scalar_t__ pwrsts; int flags; TYPE_1__ pd; int /*<<< orphan*/  gdscr; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int ALWAYS_ON ; 
 int CLK_DIS_WAIT_MASK ; 
 int CLK_DIS_WAIT_VAL ; 
 int EN_FEW_WAIT_MASK ; 
 int EN_FEW_WAIT_VAL ; 
 int EN_REST_WAIT_MASK ; 
 int EN_REST_WAIT_VAL ; 
 int /*<<< orphan*/  GDSC_ON ; 
 int /*<<< orphan*/  GENPD_FLAG_ALWAYS_ON ; 
 int HW_CONTROL_MASK ; 
 scalar_t__ PWRSTS_ON ; 
 int PWRSTS_RET ; 
 int SW_OVERRIDE_MASK ; 
 int VOTABLE ; 
 int gdsc_check_status (struct gdsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdsc_clear_mem_on (struct gdsc*) ; 
 scalar_t__ gdsc_disable ; 
 int /*<<< orphan*/  gdsc_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  gdsc_force_mem_on (struct gdsc*) ; 
 int gdsc_toggle_logic (struct gdsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_genpd_init (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int gdsc_init(struct gdsc *sc)
{
	u32 mask, val;
	int on, ret;

	/*
	 * Disable HW trigger: collapse/restore occur based on registers writes.
	 * Disable SW override: Use hardware state-machine for sequencing.
	 * Configure wait time between states.
	 */
	mask = HW_CONTROL_MASK | SW_OVERRIDE_MASK |
	       EN_REST_WAIT_MASK | EN_FEW_WAIT_MASK | CLK_DIS_WAIT_MASK;
	val = EN_REST_WAIT_VAL | EN_FEW_WAIT_VAL | CLK_DIS_WAIT_VAL;
	ret = regmap_update_bits(sc->regmap, sc->gdscr, mask, val);
	if (ret)
		return ret;

	/* Force gdsc ON if only ON state is supported */
	if (sc->pwrsts == PWRSTS_ON) {
		ret = gdsc_toggle_logic(sc, GDSC_ON);
		if (ret)
			return ret;
	}

	on = gdsc_check_status(sc, GDSC_ON);
	if (on < 0)
		return on;

	/*
	 * Votable GDSCs can be ON due to Vote from other masters.
	 * If a Votable GDSC is ON, make sure we have a Vote.
	 */
	if ((sc->flags & VOTABLE) && on)
		gdsc_enable(&sc->pd);

	/* If ALWAYS_ON GDSCs are not ON, turn them ON */
	if (sc->flags & ALWAYS_ON) {
		if (!on)
			gdsc_enable(&sc->pd);
		on = true;
		sc->pd.flags |= GENPD_FLAG_ALWAYS_ON;
	}

	if (on || (sc->pwrsts & PWRSTS_RET))
		gdsc_force_mem_on(sc);
	else
		gdsc_clear_mem_on(sc);

	if (!sc->pd.power_off)
		sc->pd.power_off = gdsc_disable;
	if (!sc->pd.power_on)
		sc->pd.power_on = gdsc_enable;
	pm_genpd_init(&sc->pd, NULL, !on);

	return 0;
}