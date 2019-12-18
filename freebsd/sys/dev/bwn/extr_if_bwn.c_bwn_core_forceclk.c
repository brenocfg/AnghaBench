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
struct bwn_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_pmu; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;
typedef  int /*<<< orphan*/  bhnd_clock ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CLOCK_DYN ; 
 int /*<<< orphan*/  BHND_CLOCK_HT ; 
 int bhnd_request_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bwn_core_forceclk(struct bwn_mac *mac, bool force)
{
	struct bwn_softc	*sc;
	bhnd_clock		 clock;
	int			 error;

	sc = mac->mac_sc;

	/* On PMU equipped devices, we do not need to force the HT clock */
	if (sc->sc_pmu != NULL)
		return (0);

	/* Issue a PMU clock request */
	if (force)
		clock = BHND_CLOCK_HT;
	else
		clock = BHND_CLOCK_DYN;

	if ((error = bhnd_request_clock(sc->sc_dev, clock))) {
		device_printf(sc->sc_dev, "%d clock request failed: %d\n",
		    clock, error);
		return (error);
	}

	return (0);
}