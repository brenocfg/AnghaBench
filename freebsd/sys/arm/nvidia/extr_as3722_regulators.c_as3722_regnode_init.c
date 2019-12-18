#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regnode {int dummy; } ;
struct as3722_reg_sc {int enable_usec; TYPE_1__* def; TYPE_2__* base_sc; scalar_t__ ext_control; scalar_t__ enable_tracking; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ id; int /*<<< orphan*/  name; int /*<<< orphan*/  volt_reg; int /*<<< orphan*/  nranges; int /*<<< orphan*/  ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3722_LDO3_MODE_MASK ; 
 int /*<<< orphan*/  AS3722_LDO3_MODE_PMOS_TRACKING ; 
 scalar_t__ AS3722_REG_ID_LDO3 ; 
 scalar_t__ AS3722_REG_ID_SD0 ; 
 int RM1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int as3722_reg_enable (struct as3722_reg_sc*) ; 
 int as3722_reg_extreg_setup (struct as3722_reg_sc*,scalar_t__) ; 
 scalar_t__ as3722_sd0_is_low_voltage (struct as3722_reg_sc*) ; 
 int /*<<< orphan*/  as3722_sd0_lv_ranges ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 struct as3722_reg_sc* regnode_get_softc (struct regnode*) ; 

__attribute__((used)) static int
as3722_regnode_init(struct regnode *regnode)
{
	struct as3722_reg_sc *sc;
	int rv;

	sc = regnode_get_softc(regnode);

	sc->enable_usec = 500;
	if (sc->def->id == AS3722_REG_ID_SD0) {
		if (as3722_sd0_is_low_voltage(sc)) {
			sc->def->ranges = as3722_sd0_lv_ranges;
			sc->def->nranges = nitems(as3722_sd0_lv_ranges);
		}
		sc->enable_usec = 600;
	} else if (sc->def->id == AS3722_REG_ID_LDO3) {
		if (sc->enable_tracking) {
			rv = RM1(sc->base_sc, sc->def->volt_reg,
			    AS3722_LDO3_MODE_MASK,
			    AS3722_LDO3_MODE_PMOS_TRACKING);
			if (rv < 0) {
				device_printf(sc->base_sc->dev,
					"LDO3 tracking failed: %d\n", rv);
				return (rv);
			}
		}
	}

	if (sc->ext_control) {

		rv = as3722_reg_enable(sc);
		if (rv < 0) {
			device_printf(sc->base_sc->dev,
				"Failed to enable %s regulator: %d\n",
				sc->def->name, rv);
			return (rv);
		}
		rv = as3722_reg_extreg_setup(sc, sc->ext_control);
		if (rv < 0) {
			device_printf(sc->base_sc->dev,
				"%s ext control failed: %d", sc->def->name, rv);
			return (rv);
		}
	}
	return (0);
}