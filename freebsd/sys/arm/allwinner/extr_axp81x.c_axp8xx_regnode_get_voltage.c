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
struct regnode {int dummy; } ;
struct axp8xx_reg_sc {TYPE_1__* def; int /*<<< orphan*/  base_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  voltage_reg; int /*<<< orphan*/  voltage_step2; int /*<<< orphan*/  voltage_step1; } ;

/* Variables and functions */
 int AXP_VOLTCTL_MASK ; 
 int ENXIO ; 
 int /*<<< orphan*/  axp8xx_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  axp8xx_regnode_reg_to_voltage (struct axp8xx_reg_sc*,int,int*) ; 
 struct axp8xx_reg_sc* regnode_get_softc (struct regnode*) ; 

__attribute__((used)) static int
axp8xx_regnode_get_voltage(struct regnode *regnode, int *uvolt)
{
	struct axp8xx_reg_sc *sc;
	uint8_t val;

	sc = regnode_get_softc(regnode);

	if (!sc->def->voltage_step1 || !sc->def->voltage_step2)
		return (ENXIO);

	axp8xx_read(sc->base_dev, sc->def->voltage_reg, &val, 1);
	axp8xx_regnode_reg_to_voltage(sc, val & AXP_VOLTCTL_MASK, uvolt);

	return (0);
}