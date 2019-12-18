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
typedef  int uint8_t ;
struct syr827_reg_sc {int /*<<< orphan*/  volt_reg; int /*<<< orphan*/  base_dev; } ;
struct regnode {int dummy; } ;

/* Variables and functions */
 int VSEL_NSEL_MASK ; 
 int VSEL_VOLTAGE_BASE ; 
 int VSEL_VOLTAGE_STEP ; 
 struct syr827_reg_sc* regnode_get_softc (struct regnode*) ; 
 int /*<<< orphan*/  syr827_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
syr827_regnode_get_voltage(struct regnode *regnode, int *uvolt)
{
	struct syr827_reg_sc *sc;
	uint8_t val;

	sc = regnode_get_softc(regnode);

	syr827_read(sc->base_dev, sc->volt_reg, &val, 1);
	*uvolt = (val & VSEL_NSEL_MASK) * VSEL_VOLTAGE_STEP +
	    VSEL_VOLTAGE_BASE;

	return (0);
}