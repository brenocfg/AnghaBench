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
struct axp2xx_reg_sc {TYPE_1__* def; int /*<<< orphan*/  base_dev; } ;
struct TYPE_2__ {int voltage_mask; int /*<<< orphan*/  voltage_reg; int /*<<< orphan*/  voltage_step; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  axp2xx_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  axp2xx_regnode_reg_to_voltage (struct axp2xx_reg_sc*,int,int*) ; 
 struct axp2xx_reg_sc* regnode_get_softc (struct regnode*) ; 

__attribute__((used)) static int
axp2xx_regnode_get_voltage(struct regnode *regnode, int *uvolt)
{
	struct axp2xx_reg_sc *sc;
	uint8_t val;

	sc = regnode_get_softc(regnode);

	if (!sc->def->voltage_step)
		return (ENXIO);

	axp2xx_read(sc->base_dev, sc->def->voltage_reg, &val, 1);
	axp2xx_regnode_reg_to_voltage(sc, val & sc->def->voltage_mask, uvolt);

	return (0);
}