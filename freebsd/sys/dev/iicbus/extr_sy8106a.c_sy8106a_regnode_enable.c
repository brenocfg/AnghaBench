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
struct sy8106a_reg_sc {TYPE_1__* param; int /*<<< orphan*/  base_dev; } ;
struct regnode {int dummy; } ;
struct TYPE_2__ {int ramp_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  COM_DISABLE ; 
 int /*<<< orphan*/  VOUT_COM ; 
 struct sy8106a_reg_sc* regnode_get_softc (struct regnode*) ; 
 int /*<<< orphan*/  sy8106a_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sy8106a_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sy8106a_regnode_enable(struct regnode *regnode, bool enable, int *udelay)
{
	struct sy8106a_reg_sc *sc;
	uint8_t val;

	sc = regnode_get_softc(regnode);

	sy8106a_read(sc->base_dev, VOUT_COM, &val, 1);
	if (enable)
		val &= ~COM_DISABLE;
	else
		val |= COM_DISABLE;
	sy8106a_write(sc->base_dev, VOUT_COM, val);

	*udelay = sc->param->ramp_delay;

	return (0);
}