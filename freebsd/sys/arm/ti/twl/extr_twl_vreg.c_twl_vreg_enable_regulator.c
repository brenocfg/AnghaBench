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
 int twl_vreg_write_1 (struct twl_vreg_softc*,struct twl_regulator_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
twl_vreg_enable_regulator(struct twl_vreg_softc *sc,
    struct twl_regulator_entry *regulator)
{
	int err;
	uint8_t grp;
	int xlocked;

	TWL_VREG_ASSERT_LOCKED(sc);

	xlocked = sx_xlocked(&sc->sc_sx);
	if (!xlocked)
		TWL_VREG_LOCK_UPGRADE(sc);


	err = twl_vreg_read_1(sc, regulator, TWL_VREG_GRP, &grp);
	if (err)
		goto done;

	/* Enable the regulator by ensuring it's in the application power group
	 * and is in the "on" state.
	 */
	if (twl_is_4030(sc->sc_pdev)) {

		/* On the TWL4030 we just need to ensure the regulator is in the right
		 * power domain, don't need to turn on explicitly like TWL6030.
		 */
		grp |= TWL4030_P1_GRP;
		err = twl_vreg_write_1(sc, regulator, TWL_VREG_GRP, grp);

	} else if (twl_is_6030(sc->sc_pdev) || twl_is_6025(sc->sc_pdev)) {

		if (twl_is_6030(sc->sc_pdev) && !(grp & TWL6030_P1_GRP)) {
			grp |= TWL6030_P1_GRP;
			err = twl_vreg_write_1(sc, regulator, TWL_VREG_GRP, grp);
			if (err)
				goto done;
		}

		/* Write the resource state to "ON" */
		err = twl_vreg_write_1(sc, regulator, TWL_VREG_STATE, (grp << 5) | 0x01);
	}

done:
	if (!xlocked)
		TWL_VREG_LOCK_DOWNGRADE(sc);
	
	return (err);
}