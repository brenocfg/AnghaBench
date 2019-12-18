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
typedef  int uint32_t ;
struct TYPE_2__ {int pud_ctrl; struct aml8726_pinctrl_function* func; struct aml8726_pinctrl_pkg_pin* ppin; } ;
struct aml8726_pinctrl_softc {TYPE_1__ soc; } ;
struct aml8726_pinctrl_pkg_pin {int pull_bits; int aobus; int /*<<< orphan*/  pull_addr; int /*<<< orphan*/ * pkg_name; } ;
struct aml8726_pinctrl_pin {char* name; int mux_bits; int /*<<< orphan*/  mux_addr; int /*<<< orphan*/ * pkg_name; } ;
struct aml8726_pinctrl_function {char* name; struct aml8726_pinctrl_pin* pins; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  enum aml8726_pinctrl_pull_mode { ____Placeholder_aml8726_pinctrl_pull_mode } aml8726_pinctrl_pull_mode ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_PINCTRL_LOCK (struct aml8726_pinctrl_softc*) ; 
 int /*<<< orphan*/  AML_PINCTRL_UNLOCK (struct aml8726_pinctrl_softc*) ; 
 int AOMUX_READ_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AOMUX_WRITE_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ,int) ; 
 int AOPEN_READ_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AOPEN_WRITE_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ,int) ; 
 int AOPUD_READ_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AOPUD_WRITE_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ,int) ; 
 int ENXIO ; 
 int MUX_READ_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUX_WRITE_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_node_from_xref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int PEN_READ_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PEN_WRITE_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ,int) ; 
 int PUD_READ_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUD_WRITE_4 (struct aml8726_pinctrl_softc*,int /*<<< orphan*/ ,int) ; 
#define  aml8726_disable_pm 131 
#define  aml8726_enable_down_pm 130 
#define  aml8726_enable_pm 129 
#define  aml8726_enable_up_pm 128 
 int aml8726_unknown_pm ; 
 struct aml8726_pinctrl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 

__attribute__((used)) static int
aml8726_pinctrl_configure_pins(device_t dev, phandle_t cfgxref)
{
	struct aml8726_pinctrl_softc *sc = device_get_softc(dev);
	struct aml8726_pinctrl_function *cf;
	struct aml8726_pinctrl_function *f;
	struct aml8726_pinctrl_pkg_pin *pp;
	struct aml8726_pinctrl_pin *cp;
	struct aml8726_pinctrl_pin *p;
	enum aml8726_pinctrl_pull_mode pm;
	char *function_name;
	char *pins;
	char *pin_name;
	char *pull;
	phandle_t node;
	ssize_t len;
	uint32_t value;

	node = OF_node_from_xref(cfgxref);

	len = OF_getprop_alloc(node, "amlogic,function",
	    (void **)&function_name);

	if (len < 0) {
		device_printf(dev,
		    "missing amlogic,function attribute in FDT\n");
		return (ENXIO);
	}

	for (f = sc->soc.func; f->name != NULL; f++)
		if (strncmp(f->name, function_name, len) == 0)
			break;

	if (f->name == NULL) {
		device_printf(dev, "unknown function attribute %.*s in FDT\n",
		    len, function_name);
		OF_prop_free(function_name);
		return (ENXIO);
	}

	OF_prop_free(function_name);

	len = OF_getprop_alloc(node, "amlogic,pull",
	    (void **)&pull);

	pm = aml8726_unknown_pm;

	if (len > 0) {
		if (strncmp(pull, "enable", len) == 0)
			pm = aml8726_enable_pm;
		else if (strncmp(pull, "disable", len) == 0)
			pm = aml8726_disable_pm;
		else if (strncmp(pull, "down", len) == 0)
			pm = aml8726_enable_down_pm;
		else if (strncmp(pull, "up", len) == 0)
			pm = aml8726_enable_up_pm;
		else {
			device_printf(dev,
			    "unknown pull attribute %.*s in FDT\n",
			    len, pull);
			OF_prop_free(pull);
			return (ENXIO);
		}
	}

	OF_prop_free(pull);

	/*
	 * Setting the pull direction isn't supported on all SoC.
	 */
	switch (pm) {
	case aml8726_enable_down_pm:
	case aml8726_enable_up_pm:
		if (sc->soc.pud_ctrl == false) {
			device_printf(dev,
			    "SoC doesn't support setting pull direction.\n");
			return (ENXIO);
		}
		break;
	default:
		break;
	}

	len = OF_getprop_alloc(node, "amlogic,pins",
	    (void **)&pins);

	if (len < 0) {
		device_printf(dev, "missing amlogic,pins attribute in FDT\n");
		return (ENXIO);
	}

	pin_name = pins;

	while (len) {
		for (p = f->pins; p->name != NULL; p++)
			if (strncmp(p->name, pin_name, len) == 0)
				break;

		if (p->name == NULL) {
			/* display message prior to queuing up next string */
			device_printf(dev, "unknown pin attribute %.*s in FDT\n",
			    len, pin_name);
		}

		/* queue up next string */
		while (*pin_name && len) {
			pin_name++;
			len--;
		}
		if (len) {
			pin_name++;
			len--;
		}

		if (p->name == NULL)
			continue;

		for (pp = sc->soc.ppin; pp->pkg_name != NULL; pp++)
			if (strcmp(pp->pkg_name, p->pkg_name) == 0)
				break;

		if (pp->pkg_name == NULL) {
			device_printf(dev,
			    "missing entry for package pin %s\n",
			    p->pkg_name);
			continue;
		}

		if (pm != aml8726_unknown_pm && pp->pull_bits == 0x00000000) {
			device_printf(dev,
			    "missing pull info for package pin %s\n",
			    p->pkg_name);
			continue;
		}

		AML_PINCTRL_LOCK(sc);

		/*
		 * First clear all other mux bits associated with this
		 * package pin.  This may briefly configure the pin as
		 * GPIO ...  however this should be fine since after
		 * reset the default GPIO mode is input.
		 */

		for (cf = sc->soc.func; cf->name != NULL; cf++)
			for (cp = cf->pins; cp->name != NULL; cp++) {
				if (cp == p)
					continue;
				if (strcmp(cp->pkg_name, p->pkg_name) != 0)
					continue;
				if (cp->mux_bits == 0)
					continue;
				if (pp->aobus == false) {
					value = MUX_READ_4(sc, cp->mux_addr);
					value &= ~cp->mux_bits;
					MUX_WRITE_4(sc, cp->mux_addr, value);
				} else {
					value = AOMUX_READ_4(sc, cp->mux_addr);
					value &= ~cp->mux_bits;
					AOMUX_WRITE_4(sc, cp->mux_addr, value);
				}
			}

		/*
		 * Now set the desired mux bits.
		 *
		 * In the case of GPIO there's no bits to set.
		 */

		if (p->mux_bits != 0) {
			if (pp->aobus == false) {
				value = MUX_READ_4(sc, p->mux_addr);
				value |= p->mux_bits;
				MUX_WRITE_4(sc, p->mux_addr, value);
			} else {
				value = AOMUX_READ_4(sc, p->mux_addr);
				value |= p->mux_bits;
				AOMUX_WRITE_4(sc, p->mux_addr, value);
			}
		}

		/*
		 * Finally set the pull mode if it was specified.
		 */

		switch (pm) {
		case aml8726_enable_down_pm:
		case aml8726_enable_up_pm:
			if (pp->aobus == false) {
				value = PUD_READ_4(sc, pp->pull_addr);
				if (pm == aml8726_enable_down_pm)
					value &= ~pp->pull_bits;
				else
					value |= pp->pull_bits;
				PUD_WRITE_4(sc, pp->pull_addr, value);
			} else {
				value = AOPUD_READ_4(sc, pp->pull_addr);
				if (pm == aml8726_enable_down_pm)
					value &= ~(pp->pull_bits << 16);
				else
					value |= (pp->pull_bits << 16);
				AOPUD_WRITE_4(sc, pp->pull_addr, value);
			}
			/* FALLTHROUGH */
		case aml8726_disable_pm:
		case aml8726_enable_pm:
			if (pp->aobus == false) {
				value = PEN_READ_4(sc, pp->pull_addr);
				if (pm == aml8726_disable_pm)
					value &= ~pp->pull_bits;
				else
					value |= pp->pull_bits;
				PEN_WRITE_4(sc, pp->pull_addr, value);
			} else {
				value = AOPEN_READ_4(sc, pp->pull_addr);
				if (pm == aml8726_disable_pm)
					value &= ~pp->pull_bits;
				else
					value |= pp->pull_bits;
				AOPEN_WRITE_4(sc, pp->pull_addr, value);
			}
			break;
		default:
			break;
		}

		AML_PINCTRL_UNLOCK(sc);
	}

	OF_prop_free(pins);

	return (0);
}