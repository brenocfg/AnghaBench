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
struct rk805_reg_sc {TYPE_1__* def; } ;
struct TYPE_2__ {int voltage_nstep; int voltage_min; int voltage_step; } ;

/* Variables and functions */

__attribute__((used)) static void
rk805_regnode_reg_to_voltage(struct rk805_reg_sc *sc, uint8_t val, int *uv)
{
	if (val < sc->def->voltage_nstep)
		*uv = sc->def->voltage_min + val * sc->def->voltage_step;
	else
		*uv = sc->def->voltage_min +
		       (sc->def->voltage_nstep * sc->def->voltage_step);
}