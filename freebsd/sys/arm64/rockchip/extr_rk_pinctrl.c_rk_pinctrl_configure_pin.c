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
typedef  int uint32_t ;
struct syscon {int dummy; } ;
struct rk_pinctrl_softc {TYPE_2__* conf; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
struct TYPE_4__ {int iomux_nbanks; int (* get_pd_offset ) (struct rk_pinctrl_softc*,int) ;TYPE_1__* iomux_conf; struct syscon* (* get_syscon ) (struct rk_pinctrl_softc*,int) ;} ;
struct TYPE_3__ {int bank; int subbank; int offset; int nbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_node_from_xref (int) ; 
 int /*<<< orphan*/  SYSCON_MODIFY_4 (struct syscon*,int,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  rk_pinctrl_get_fixup (struct rk_pinctrl_softc*,int,int,int*,int*,int*) ; 
 int rk_pinctrl_handle_io (struct rk_pinctrl_softc*,int /*<<< orphan*/ ,int,int) ; 
 int rk_pinctrl_parse_bias (int /*<<< orphan*/ ) ; 
 int rk_pinctrl_parse_drive (struct rk_pinctrl_softc*,int /*<<< orphan*/ ,int,int,int*,int*) ; 
 struct syscon* stub1 (struct rk_pinctrl_softc*,int) ; 
 int stub2 (struct rk_pinctrl_softc*,int) ; 

__attribute__((used)) static void
rk_pinctrl_configure_pin(struct rk_pinctrl_softc *sc, uint32_t *pindata)
{
	phandle_t pin_conf;
	struct syscon *syscon;
	uint32_t bank, subbank, pin, function, bias;
	uint32_t bit, mask, reg, drive;
	int i, rv;

	bank = pindata[0];
	pin = pindata[1];
	function = pindata[2];
	pin_conf = OF_node_from_xref(pindata[3]);
	subbank = pin / 8;

	for (i = 0; i < sc->conf->iomux_nbanks; i++)
		if (sc->conf->iomux_conf[i].bank == bank &&
		    sc->conf->iomux_conf[i].subbank == subbank)
			break;

	if (i == sc->conf->iomux_nbanks) {
		device_printf(sc->dev, "Unknown pin %d in bank %d\n", pin,
		    bank);
		return;
	}

	/* Find syscon */
	syscon = sc->conf->get_syscon(sc, bank);

	/* Parse pin function */
	reg = sc->conf->iomux_conf[i].offset;
	switch (sc->conf->iomux_conf[i].nbits) {
	case 4:
		if ((pin % 8) >= 4)
			reg += 0x4;
		bit = (pin % 4) * 4;
		mask = (0xF << bit);
		break;
	case 3:
		if ((pin % 8) >= 5)
			reg += 4;
		bit = (pin % 8 % 5) * 3;
		mask = (0x7 << bit);
		break;
	case 2:
		bit = (pin % 8) * 2;
		mask = (0x3 << bit);
		break;
	default:
		device_printf(sc->dev,
		    "Unknown pin stride width %d in bank %d\n",
		    sc->conf->iomux_conf[i].nbits, bank);
		return;
	}
	rk_pinctrl_get_fixup(sc, bank, pin, &reg, &mask, &bit);

	/*
	 * NOTE: not all syscon registers uses hi-word write mask, thus
	 * register modify method should be used.
	 * XXXX We should not pass write mask to syscon register 
	 * without hi-word write mask.
	 */
	SYSCON_MODIFY_4(syscon, reg, mask, function << bit | (mask << 16));

	/* Pull-Up/Down */
	bias = rk_pinctrl_parse_bias(pin_conf);
	if (bias >= 0) {
		reg = sc->conf->get_pd_offset(sc, bank);

		reg += bank * 0x10 + ((pin / 8) * 0x4);
		bit = (pin % 8) * 2;
		mask = (0x3 << bit) << 16;
		SYSCON_MODIFY_4(syscon, reg, mask, bias << bit | (mask << 16));
	}

	/* Drive Strength */
	rv = rk_pinctrl_parse_drive(sc, pin_conf, bank, subbank, &drive, &reg);
	if (rv == 0) {
		bit = (pin % 8) * 2;
		mask = (0x3 << bit) << 16;
		SYSCON_MODIFY_4(syscon, reg, mask, drive << bit | (mask << 16));
	}

	/* Input/Outpot + default level */
	rv = rk_pinctrl_handle_io(sc, pin_conf, bank, pin);
}