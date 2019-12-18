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
struct syr827_reg_sc {TYPE_1__* param; int /*<<< orphan*/  volt_reg; int /*<<< orphan*/  base_dev; } ;
struct regnode {int dummy; } ;
struct TYPE_2__ {int ramp_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSEL_BUCK_EN ; 
 struct syr827_reg_sc* regnode_get_softc (struct regnode*) ; 
 int /*<<< orphan*/  syr827_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  syr827_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
syr827_regnode_enable(struct regnode *regnode, bool enable, int *udelay)
{
	struct syr827_reg_sc *sc;
	uint8_t val;

	sc = regnode_get_softc(regnode);

	syr827_read(sc->base_dev, sc->volt_reg, &val, 1);
	if (enable)
		val &= ~VSEL_BUCK_EN;
	else
		val |= VSEL_BUCK_EN;
	syr827_write(sc->base_dev, sc->volt_reg, val);

	*udelay = sc->param->ramp_delay;

	return (0);
}