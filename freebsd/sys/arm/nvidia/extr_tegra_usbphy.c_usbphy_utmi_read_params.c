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
struct usbphy_softc {int xcvr_setup_use_fuses; int /*<<< orphan*/  xcvr_setup; int /*<<< orphan*/  hsdiscon_level; int /*<<< orphan*/  hssquelch_level; int /*<<< orphan*/  xcvr_hsslew; int /*<<< orphan*/  xcvr_lsrslew; int /*<<< orphan*/  xcvr_lsfslew; int /*<<< orphan*/  term_range_adj; int /*<<< orphan*/  idle_wait_delay; int /*<<< orphan*/  elastic_limit; int /*<<< orphan*/  hssync_start_delay; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int ENXIO ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
usbphy_utmi_read_params(struct usbphy_softc *sc, phandle_t node)
{
	int rv;

	rv = OF_getencprop(node, "nvidia,hssync-start-delay",
	    &sc->hssync_start_delay, sizeof (sc->hssync_start_delay));
	if (rv <= 0)
		return (ENXIO);

	rv = OF_getencprop(node, "nvidia,elastic-limit",
	    &sc->elastic_limit, sizeof (sc->elastic_limit));
	if (rv <= 0)
		return (ENXIO);

	rv = OF_getencprop(node, "nvidia,idle-wait-delay",
	    &sc->idle_wait_delay, sizeof (sc->idle_wait_delay));
	if (rv <= 0)
		return (ENXIO);

	rv = OF_getencprop(node, "nvidia,term-range-adj",
	    &sc->term_range_adj, sizeof (sc->term_range_adj));
	if (rv <= 0)
		return (ENXIO);

	rv = OF_getencprop(node, "nvidia,xcvr-lsfslew",
	    &sc->xcvr_lsfslew, sizeof (sc->xcvr_lsfslew));
	if (rv <= 0)
		return (ENXIO);

	rv = OF_getencprop(node, "nvidia,xcvr-lsrslew",
	    &sc->xcvr_lsrslew, sizeof (sc->xcvr_lsrslew));
	if (rv <= 0)
		return (ENXIO);

	rv = OF_getencprop(node, "nvidia,xcvr-hsslew",
	    &sc->xcvr_hsslew, sizeof (sc->xcvr_hsslew));
	if (rv <= 0)
		return (ENXIO);

	rv = OF_getencprop(node, "nvidia,hssquelch-level",
	    &sc->hssquelch_level, sizeof (sc->hssquelch_level));
	if (rv <= 0)
		return (ENXIO);

	rv = OF_getencprop(node, "nvidia,hsdiscon-level",
	    &sc->hsdiscon_level, sizeof (sc->hsdiscon_level));
	if (rv <= 0)
		return (ENXIO);

	rv = OF_getproplen(node, "nvidia,xcvr-setup-use-fuses");
	if (rv >= 1) {
		sc->xcvr_setup_use_fuses = 1;
	} else {
		rv = OF_getencprop(node, "nvidia,xcvr-setup",
		    &sc->xcvr_setup, sizeof (sc->xcvr_setup));
		if (rv <= 0)
			return (ENXIO);
	}

	return (0);
}