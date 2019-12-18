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
struct rk805_reg_sc {TYPE_1__* def; int /*<<< orphan*/  base_dev; } ;
struct regnode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  voltage_reg; int /*<<< orphan*/  voltage_step; } ;

/* Variables and functions */
 int ENXIO ; 
 int ERANGE ; 
 int /*<<< orphan*/  dprintf (struct rk805_reg_sc*,char*,int /*<<< orphan*/ ,int,...) ; 
 struct rk805_reg_sc* regnode_get_softc (struct regnode*) ; 
 int /*<<< orphan*/  rk805_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rk805_regnode_reg_to_voltage (struct rk805_reg_sc*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rk805_regnode_voltage_to_reg (struct rk805_reg_sc*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rk805_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rk805_regnode_set_voltage(struct regnode *regnode, int min_uvolt,
    int max_uvolt, int *udelay)
{
	struct rk805_reg_sc *sc;
	uint8_t val;
	int uvolt;

	sc = regnode_get_softc(regnode);

	if (!sc->def->voltage_step)
		return (ENXIO);

	dprintf(sc, "Setting %s to %d<->%d uvolts\n",
	    sc->def->name,
	    min_uvolt,
	    max_uvolt);
	rk805_read(sc->base_dev, sc->def->voltage_reg, &val, 1);
	if (rk805_regnode_voltage_to_reg(sc, min_uvolt, max_uvolt, &val) != 0)
		return (ERANGE);

	rk805_write(sc->base_dev, sc->def->voltage_reg, val);

	rk805_read(sc->base_dev, sc->def->voltage_reg, &val, 1);

	*udelay = 0;

	rk805_regnode_reg_to_voltage(sc, val, &uvolt);
	dprintf(sc, "Regulator %s set to %d uvolt\n",
	  sc->def->name,
	  uvolt);

	return (0);
}