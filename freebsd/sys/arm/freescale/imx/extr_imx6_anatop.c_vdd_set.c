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
typedef  int uint32_t ;
struct imx6_anatop_softc {int cpu_curmv; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int IMX6_ANALOG_PMU_REG0_TARG_MASK ; 
 int IMX6_ANALOG_PMU_REG0_TARG_SHIFT ; 
 int IMX6_ANALOG_PMU_REG1_TARG_MASK ; 
 int IMX6_ANALOG_PMU_REG1_TARG_SHIFT ; 
 int IMX6_ANALOG_PMU_REG2_TARG_MASK ; 
 int IMX6_ANALOG_PMU_REG2_TARG_SHIFT ; 
 int /*<<< orphan*/  IMX6_ANALOG_PMU_REG_CORE ; 
 int imx6_anatop_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx6_anatop_write_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vdd_set(struct imx6_anatop_softc *sc, int mv)
{
	int newtarg, newtargSoc, oldtarg;
	uint32_t delay, pmureg;
	static boolean_t init_done = false;

	/*
	 * The datasheet says VDD_PU and VDD_SOC must be equal, and VDD_ARM
	 * can't be more than 50mV above or 200mV below them.  We keep them the
	 * same except in the case of the lowest operating point, which is
	 * handled as a special case below.
	 */

	pmureg = imx6_anatop_read_4(IMX6_ANALOG_PMU_REG_CORE);
	oldtarg = pmureg & IMX6_ANALOG_PMU_REG0_TARG_MASK;

	/* Convert mV to target value.  Clamp target to valid range. */
	if (mv < 725)
		newtarg = 0x00;
	else if (mv > 1450)
		newtarg = 0x1F;
	else
		newtarg = (mv - 700) / 25;

	/*
	 * The SOC voltage can't go below 1150mV, and thus because of the 200mV
	 * rule, the ARM voltage can't go below 950mV.  The 950 is encoded in
	 * our oppt table, here we handle the SOC 1150 rule as a special case.
	 * (1150-700/25=18).
	 */
	newtargSoc = (newtarg < 18) ? 18 : newtarg;

	/*
	 * The first time through the 3 voltages might not be equal so use a
	 * long conservative delay.  After that we need to delay 3uS for every
	 * 25mV step upward; we actually delay 6uS because empirically, it works
	 * and the 3uS per step recommended by the docs doesn't (3uS fails when
	 * going from 400->1200, but works for smaller changes).
	 */
	if (init_done) {
		if (newtarg == oldtarg)
			return;
		else if (newtarg > oldtarg)
			delay = (newtarg - oldtarg) * 6;
		else
			delay = 0;
	} else {
		delay = (700 / 25) * 6;
		init_done = true;
	}

	/*
	 * Make the change and wait for it to take effect.
	 */
	pmureg &= ~(IMX6_ANALOG_PMU_REG0_TARG_MASK |
	    IMX6_ANALOG_PMU_REG1_TARG_MASK |
	    IMX6_ANALOG_PMU_REG2_TARG_MASK);

	pmureg |= newtarg << IMX6_ANALOG_PMU_REG0_TARG_SHIFT;
	pmureg |= newtarg << IMX6_ANALOG_PMU_REG1_TARG_SHIFT;
	pmureg |= newtargSoc << IMX6_ANALOG_PMU_REG2_TARG_SHIFT;

	imx6_anatop_write_4(IMX6_ANALOG_PMU_REG_CORE, pmureg);
	DELAY(delay);
	sc->cpu_curmv = newtarg * 25 + 700;
}