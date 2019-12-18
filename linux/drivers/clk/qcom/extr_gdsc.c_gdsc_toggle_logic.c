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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct gdsc {int flags; TYPE_1__ pd; scalar_t__ gds_hw_ctrl; int /*<<< orphan*/  gdscr; int /*<<< orphan*/  regmap; } ;
typedef  enum gdsc_status { ____Placeholder_gdsc_status } gdsc_status ;

/* Variables and functions */
 int GDSC_OFF ; 
 int GDSC_ON ; 
 int /*<<< orphan*/  SW_COLLAPSE_MASK ; 
 int TIMEOUT_US ; 
 int VOTABLE ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,char*) ; 
 int gdsc_poll_status (struct gdsc*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gdsc_toggle_logic(struct gdsc *sc, enum gdsc_status status)
{
	int ret;
	u32 val = (status == GDSC_ON) ? 0 : SW_COLLAPSE_MASK;

	ret = regmap_update_bits(sc->regmap, sc->gdscr, SW_COLLAPSE_MASK, val);
	if (ret)
		return ret;

	/* If disabling votable gdscs, don't poll on status */
	if ((sc->flags & VOTABLE) && status == GDSC_OFF) {
		/*
		 * Add a short delay here to ensure that an enable
		 * right after it was disabled does not put it in an
		 * unknown state
		 */
		udelay(TIMEOUT_US);
		return 0;
	}

	if (sc->gds_hw_ctrl) {
		/*
		 * The gds hw controller asserts/de-asserts the status bit soon
		 * after it receives a power on/off request from a master.
		 * The controller then takes around 8 xo cycles to start its
		 * internal state machine and update the status bit. During
		 * this time, the status bit does not reflect the true status
		 * of the core.
		 * Add a delay of 1 us between writing to the SW_COLLAPSE bit
		 * and polling the status bit.
		 */
		udelay(1);
	}

	ret = gdsc_poll_status(sc, status);
	WARN(ret, "%s status stuck at 'o%s'", sc->pd.name, status ? "ff" : "n");
	return ret;
}