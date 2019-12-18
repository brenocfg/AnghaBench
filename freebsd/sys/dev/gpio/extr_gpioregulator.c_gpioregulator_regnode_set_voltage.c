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
struct regnode {int dummy; } ;
struct gpioregulator_state {int val; int mask; } ;
struct gpioregulator_reg_sc {TYPE_1__* def; } ;
struct TYPE_2__ {int nstates; int npins; int startup_delay_us; int /*<<< orphan*/ * pins; struct gpioregulator_state* states; } ;

/* Variables and functions */
 int EINVAL ; 
 int gpio_pin_set_active (int /*<<< orphan*/ ,int) ; 
 struct gpioregulator_reg_sc* regnode_get_softc (struct regnode*) ; 

__attribute__((used)) static int
gpioregulator_regnode_set_voltage(struct regnode *regnode, int min_uvolt,
    int max_uvolt, int *udelay)
{
	struct gpioregulator_reg_sc *sc;
	const struct gpioregulator_state *state;
	int error, n;

	sc = regnode_get_softc(regnode);
	state = NULL;

	for (n = 0; n < sc->def->nstates; n++) {
		if (sc->def->states[n].val >= min_uvolt &&
		    sc->def->states[n].val <= max_uvolt) {
			state = &sc->def->states[n];
			break;
		}
	}
	if (state == NULL)
		return (EINVAL);

	for (n = 0; n < sc->def->npins; n++) {
		error = gpio_pin_set_active(sc->def->pins[n],
		    (state->mask >> n) & 1);
		if (error != 0)
			return (error);
	}

	*udelay = sc->def->startup_delay_us;

	return (0);
}