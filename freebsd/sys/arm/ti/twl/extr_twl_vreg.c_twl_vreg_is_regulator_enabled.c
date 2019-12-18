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
struct twl_vreg_softc {int /*<<< orphan*/  sc_pdev; int /*<<< orphan*/  sc_sx; } ;
struct twl_regulator_entry {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int TWL4030_P1_GRP ; 
 int TWL6030_P1_GRP ; 
 int /*<<< orphan*/  TWL_VREG_ASSERT_LOCKED (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_GRP ; 
 int /*<<< orphan*/  TWL_VREG_LOCK_DOWNGRADE (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_LOCK_UPGRADE (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_STATE ; 
 int sx_xlocked (int /*<<< orphan*/ *) ; 
 scalar_t__ twl_is_4030 (int /*<<< orphan*/ ) ; 
 scalar_t__ twl_is_6025 (int /*<<< orphan*/ ) ; 
 scalar_t__ twl_is_6030 (int /*<<< orphan*/ ) ; 
 int twl_vreg_read_1 (struct twl_vreg_softc*,struct twl_regulator_entry*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
twl_vreg_is_regulator_enabled(struct twl_vreg_softc *sc,
	struct twl_regulator_entry *regulator, int *enabled)
{
	int err;
	uint8_t grp;
	uint8_t state;
	int xlocked;
	
	if (enabled == NULL)
		return (EINVAL);

	TWL_VREG_ASSERT_LOCKED(sc);

	xlocked = sx_xlocked(&sc->sc_sx);
	if (!xlocked)
		TWL_VREG_LOCK_UPGRADE(sc);

	/* The status reading is different for the different devices */
	if (twl_is_4030(sc->sc_pdev)) {

		err = twl_vreg_read_1(sc, regulator, TWL_VREG_GRP, &state);
		if (err)
			goto done;

		*enabled = (state & TWL4030_P1_GRP);

	} else if (twl_is_6030(sc->sc_pdev) || twl_is_6025(sc->sc_pdev)) {

		/* Check the regulator is in the application group */
		if (twl_is_6030(sc->sc_pdev)) {
			err = twl_vreg_read_1(sc, regulator, TWL_VREG_GRP, &grp);
			if (err)
				goto done;

			if (!(grp & TWL6030_P1_GRP)) {
				*enabled = 0; /* disabled */
				goto done;
			}
		}

		/* Read the application mode state and verify it's ON */
		err = twl_vreg_read_1(sc, regulator, TWL_VREG_STATE, &state);
		if (err)
			goto done;

		*enabled = ((state & 0x0C) == 0x04);

	} else {
		err = EINVAL;
	}

done:
	if (!xlocked)
		TWL_VREG_LOCK_DOWNGRADE(sc);

	return (err);
}