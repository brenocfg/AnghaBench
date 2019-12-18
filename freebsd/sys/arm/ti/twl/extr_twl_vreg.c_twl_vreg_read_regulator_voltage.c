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
struct twl_regulator_entry {int* supp_voltages; int num_supp_voltages; int fixed_voltage; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TWL_VREG_ASSERT_LOCKED (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_LOCK_DOWNGRADE (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_LOCK_UPGRADE (struct twl_vreg_softc*) ; 
 int /*<<< orphan*/  TWL_VREG_VSEL ; 
 int UNDF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int sx_xlocked (int /*<<< orphan*/ *) ; 
 int twl_vreg_debug ; 
 int twl_vreg_is_regulator_enabled (struct twl_vreg_softc*,struct twl_regulator_entry*,int*) ; 
 int twl_vreg_read_1 (struct twl_vreg_softc*,struct twl_regulator_entry*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
twl_vreg_read_regulator_voltage(struct twl_vreg_softc *sc,
    struct twl_regulator_entry *regulator, int *millivolts)
{
	int err;
	int en = 0;
	int xlocked;
	uint8_t vsel;
	
	TWL_VREG_ASSERT_LOCKED(sc);
	
	/* Need to upgrade the lock because checking enabled state and voltage
	 * should be atomic.
	 */
	xlocked = sx_xlocked(&sc->sc_sx);
	if (!xlocked)
		TWL_VREG_LOCK_UPGRADE(sc);


	/* Check if the regulator is currently enabled */
	err = twl_vreg_is_regulator_enabled(sc, regulator, &en);
	if (err)
		goto done;

	*millivolts = 0;	
	if (!en)
		goto done;


	/* Not all voltages are adjustable */
	if (regulator->supp_voltages == NULL || !regulator->num_supp_voltages) {
		*millivolts = regulator->fixed_voltage;
		goto done;
	}

	/* For variable voltages read the voltage register */
	err = twl_vreg_read_1(sc, regulator, TWL_VREG_VSEL, &vsel);
	if (err)
		goto done;

	vsel &= (regulator->num_supp_voltages - 1);
	if (regulator->supp_voltages[vsel] == UNDF) {
		err = EINVAL;
		goto done;
	}

	*millivolts = regulator->supp_voltages[vsel];

done:
	if (!xlocked)
		TWL_VREG_LOCK_DOWNGRADE(sc);
	
	if ((twl_vreg_debug > 1) && !err)
		device_printf(sc->sc_dev, "%s : reading voltage is %dmV (vsel: 0x%x)\n",
		    regulator->name, *millivolts, vsel);

	return (err);
}