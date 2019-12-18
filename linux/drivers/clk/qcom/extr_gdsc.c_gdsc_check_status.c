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
typedef  int u32 ;
struct gdsc {int flags; unsigned int gdscr; int gds_hw_ctrl; int /*<<< orphan*/  regmap; } ;
typedef  enum gdsc_status { ____Placeholder_gdsc_status } gdsc_status ;

/* Variables and functions */
 unsigned int CFG_GDSCR_OFFSET ; 
 int EINVAL ; 
#define  GDSC_OFF 129 
#define  GDSC_ON 128 
 int GDSC_POWER_DOWN_COMPLETE ; 
 int GDSC_POWER_UP_COMPLETE ; 
 int POLL_CFG_GDSCR ; 
 int PWR_ON_MASK ; 
 int regmap_read (int /*<<< orphan*/ ,unsigned int,int*) ; 

__attribute__((used)) static int gdsc_check_status(struct gdsc *sc, enum gdsc_status status)
{
	unsigned int reg;
	u32 val;
	int ret;

	if (sc->flags & POLL_CFG_GDSCR)
		reg = sc->gdscr + CFG_GDSCR_OFFSET;
	else if (sc->gds_hw_ctrl)
		reg = sc->gds_hw_ctrl;
	else
		reg = sc->gdscr;

	ret = regmap_read(sc->regmap, reg, &val);
	if (ret)
		return ret;

	if (sc->flags & POLL_CFG_GDSCR) {
		switch (status) {
		case GDSC_ON:
			return !!(val & GDSC_POWER_UP_COMPLETE);
		case GDSC_OFF:
			return !!(val & GDSC_POWER_DOWN_COMPLETE);
		}
	}

	switch (status) {
	case GDSC_ON:
		return !!(val & PWR_ON_MASK);
	case GDSC_OFF:
		return !(val & PWR_ON_MASK);
	}

	return -EINVAL;
}