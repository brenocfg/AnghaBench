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
typedef  int /*<<< orphan*/  uint8_t ;
struct regnode {int dummy; } ;
struct axp2xx_reg_sc {TYPE_1__* def; int /*<<< orphan*/  base_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  voltage_reg; int /*<<< orphan*/  voltage_step; } ;

/* Variables and functions */
 int ENXIO ; 
 int ERANGE ; 
 scalar_t__ axp2xx_regnode_voltage_to_reg (struct axp2xx_reg_sc*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  axp2xx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct axp2xx_reg_sc* regnode_get_softc (struct regnode*) ; 

__attribute__((used)) static int
axp2xx_regnode_set_voltage(struct regnode *regnode, int min_uvolt,
    int max_uvolt, int *udelay)
{
	struct axp2xx_reg_sc *sc;
	uint8_t val;

	sc = regnode_get_softc(regnode);

	if (!sc->def->voltage_step)
		return (ENXIO);

	if (axp2xx_regnode_voltage_to_reg(sc, min_uvolt, max_uvolt, &val) != 0)
		return (ERANGE);

	axp2xx_write(sc->base_dev, sc->def->voltage_reg, val);

	*udelay = 0;

	return (0);
}