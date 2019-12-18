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
typedef  unsigned int uint8_t ;
struct twl_vreg_softc {int dummy; } ;
struct twl_regulator_entry {scalar_t__* supp_voltages; unsigned int num_supp_voltages; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TWL_VREG_ASSERT_LOCKED (struct twl_vreg_softc*) ; 
 scalar_t__ UNDF ; 
 int abs (int) ; 

__attribute__((used)) static int
twl_vreg_millivolt_to_vsel(struct twl_vreg_softc *sc,
	struct twl_regulator_entry *regulator, int millivolts, uint8_t *vsel)
{
	int delta, smallest_delta;
	unsigned i, closest_idx;

	TWL_VREG_ASSERT_LOCKED(sc);

	if (regulator->supp_voltages == NULL)
		return (EINVAL);

	/* Loop over the support voltages and try and find the closest match */
	closest_idx = 0;
	smallest_delta = 0x7fffffff;
	for (i = 0; i < regulator->num_supp_voltages; i++) {

		/* Ignore undefined values */
		if (regulator->supp_voltages[i] == UNDF)
			continue;

		/* Calculate the difference */
		delta = millivolts - (int)regulator->supp_voltages[i];
		if (abs(delta) < smallest_delta) {
			smallest_delta = abs(delta);
			closest_idx = i;
		}
	}

	/* Check we got a voltage that was within 100mv of the actual target, this
	 * is just a value I picked out of thin air.
	 */
	if ((smallest_delta > 100) && (closest_idx < 0x100))
		return (EINVAL);

	*vsel = closest_idx;
	return (0);
}