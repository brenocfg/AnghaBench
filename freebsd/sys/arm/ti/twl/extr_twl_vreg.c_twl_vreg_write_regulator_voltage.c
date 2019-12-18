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
struct twl_vreg_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_sx; } ;
struct twl_regulator_entry {scalar_t__ num_supp_voltages; int fixed_voltage; int /*<<< orphan*/  name; int /*<<< orphan*/ * supp_voltages; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TWL_VREG_ASSERT_LOCKED (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_LOCK_DOWNGRADE (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_LOCK_UPGRADE (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_VSEL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int sx_xlocked (int /*<<< orphan*/ *) ; 
 int twl_vreg_debug ; 
 int twl_vreg_disable_regulator (struct twl_vreg_softc*,struct twl_regulator_entry*) ; 
 int twl_vreg_enable_regulator (struct twl_vreg_softc*,struct twl_regulator_entry*) ; 
 int twl_vreg_millivolt_to_vsel (struct twl_vreg_softc*,struct twl_regulator_entry*,int,int*) ; 
 int twl_vreg_write_1 (struct twl_vreg_softc*,struct twl_regulator_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
twl_vreg_write_regulator_voltage(struct twl_vreg_softc *sc,
    struct twl_regulator_entry *regulator, int millivolts)
{
	int err;
	uint8_t vsel;
	int xlocked;

	TWL_VREG_ASSERT_LOCKED(sc);

	/* If millivolts is zero then we simply disable the output */
	if (millivolts == 0)
		return (twl_vreg_disable_regulator(sc, regulator));

	/* If the regulator has a fixed voltage then check the setting matches
	 * and simply enable.
	 */
	if (regulator->supp_voltages == NULL || regulator->num_supp_voltages == 0) {
		if (millivolts != regulator->fixed_voltage)
			return (EINVAL);

		return (twl_vreg_enable_regulator(sc, regulator));
	}

	/* Get the VSEL value for the given voltage */
	err = twl_vreg_millivolt_to_vsel(sc, regulator, millivolts, &vsel);
	if (err)
		return (err);

	
	/* Need to upgrade because writing the voltage and enabling should be atomic */
	xlocked = sx_xlocked(&sc->sc_sx);
	if (!xlocked)
		TWL_VREG_LOCK_UPGRADE(sc);


	/* Set voltage and enable (atomically) */
	err = twl_vreg_write_1(sc, regulator, TWL_VREG_VSEL, (vsel & 0x1f));
	if (!err) {
		err = twl_vreg_enable_regulator(sc, regulator);
	}

	if (!xlocked)
		TWL_VREG_LOCK_DOWNGRADE(sc);

	if ((twl_vreg_debug > 1) && !err)
		device_printf(sc->sc_dev, "%s : setting voltage to %dmV (vsel: 0x%x)\n",
		    regulator->name, millivolts, vsel);

	return (err);
}