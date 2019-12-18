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
typedef  scalar_t__ uint8_t ;
struct axp8xx_reg_sc {TYPE_1__* def; } ;
struct TYPE_2__ {int voltage_min; int voltage_nstep1; int voltage_step1; int voltage_nstep2; int voltage_step2; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
axp8xx_regnode_voltage_to_reg(struct axp8xx_reg_sc *sc, int min_uvolt,
    int max_uvolt, uint8_t *val)
{
	uint8_t nval;
	int nstep, uvolt;

	nval = 0;
	uvolt = sc->def->voltage_min * 1000;

	for (nstep = 0; nstep < sc->def->voltage_nstep1 && uvolt < min_uvolt;
	     nstep++) {
		++nval;
		uvolt += (sc->def->voltage_step1 * 1000);
	}
	for (nstep = 0; nstep < sc->def->voltage_nstep2 && uvolt < min_uvolt;
	     nstep++) {
		++nval;
		uvolt += (sc->def->voltage_step2 * 1000);
	}
	if (uvolt > max_uvolt)
		return (EINVAL);

	*val = nval;
	return (0);
}