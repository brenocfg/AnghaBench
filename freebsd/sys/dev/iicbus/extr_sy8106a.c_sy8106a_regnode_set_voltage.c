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
typedef  int uint8_t ;
struct sy8106a_reg_sc {TYPE_1__* param; int /*<<< orphan*/  base_dev; } ;
struct regnode {int dummy; } ;
struct TYPE_2__ {int ramp_delay; } ;

/* Variables and functions */
 int SEL_GO ; 
 int SEL_VOLTAGE_BASE ; 
 int SEL_VOLTAGE_MASK ; 
 int SEL_VOLTAGE_STEP ; 
 int /*<<< orphan*/  VOUT1_SEL ; 
 int abs (int) ; 
 struct sy8106a_reg_sc* regnode_get_softc (struct regnode*) ; 
 int /*<<< orphan*/  sy8106a_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sy8106a_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sy8106a_regnode_set_voltage(struct regnode *regnode, int min_uvolt,
    int max_uvolt, int *udelay)
{
	struct sy8106a_reg_sc *sc;
	int cur_uvolt;
	uint8_t val, oval;

	sc = regnode_get_softc(regnode);

	/* Get current voltage */
	sy8106a_read(sc->base_dev, VOUT1_SEL, &oval, 1);
	cur_uvolt = (oval & SEL_VOLTAGE_MASK) * SEL_VOLTAGE_STEP +
	    SEL_VOLTAGE_BASE;

	/* Set new voltage */
	val = SEL_GO | ((min_uvolt - SEL_VOLTAGE_BASE) / SEL_VOLTAGE_STEP);
	sy8106a_write(sc->base_dev, VOUT1_SEL, val);

	/* Time to delay is based on the number of voltage steps */
	*udelay = sc->param->ramp_delay *
	    (abs(cur_uvolt - min_uvolt) / SEL_VOLTAGE_STEP);

	return (0);
}