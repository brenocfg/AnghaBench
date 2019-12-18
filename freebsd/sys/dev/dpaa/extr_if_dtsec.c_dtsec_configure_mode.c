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
typedef  int /*<<< orphan*/  tunable ;
struct dtsec_softc {int /*<<< orphan*/  sc_mode; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_start_locked; int /*<<< orphan*/  sc_port_tx_init; int /*<<< orphan*/  sc_port_rx_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_MODE_REGULAR ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dtsec_im_fm_port_rx_init ; 
 int /*<<< orphan*/  dtsec_im_fm_port_tx_init ; 
 int /*<<< orphan*/  dtsec_im_if_start_locked ; 
 int /*<<< orphan*/  dtsec_rm_fm_port_rx_init ; 
 int /*<<< orphan*/  dtsec_rm_fm_port_tx_init ; 
 int /*<<< orphan*/  dtsec_rm_if_start_locked ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void
dtsec_configure_mode(struct dtsec_softc *sc)
{
	char tunable[64];

	snprintf(tunable, sizeof(tunable), "%s.independent_mode",
	    device_get_nameunit(sc->sc_dev));

	sc->sc_mode = DTSEC_MODE_REGULAR;
	TUNABLE_INT_FETCH(tunable, &sc->sc_mode);

	if (sc->sc_mode == DTSEC_MODE_REGULAR) {
		sc->sc_port_rx_init = dtsec_rm_fm_port_rx_init;
		sc->sc_port_tx_init = dtsec_rm_fm_port_tx_init;
		sc->sc_start_locked = dtsec_rm_if_start_locked;
	} else {
		sc->sc_port_rx_init = dtsec_im_fm_port_rx_init;
		sc->sc_port_tx_init = dtsec_im_fm_port_tx_init;
		sc->sc_start_locked = dtsec_im_if_start_locked;
	}

	device_printf(sc->sc_dev, "Configured for %s mode.\n",
	    (sc->sc_mode == DTSEC_MODE_REGULAR) ? "regular" : "independent");
}