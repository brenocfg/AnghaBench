#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  h_Fm; struct dtsec_softc* h_App; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  f_Event; int /*<<< orphan*/  mdioIrq; int /*<<< orphan*/  macId; int /*<<< orphan*/  enetMode; int /*<<< orphan*/  baseAddr; int /*<<< orphan*/  addr; } ;
typedef  TYPE_1__ t_FmMacParams ;
typedef  scalar_t__ t_Error ;
struct dtsec_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_mach; int /*<<< orphan*/  sc_fmh; int /*<<< orphan*/  sc_mac_mdio_irq; int /*<<< orphan*/  sc_eth_id; int /*<<< orphan*/  sc_mac_enet_mode; int /*<<< orphan*/  sc_mem; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * FM_MAC_Config (TYPE_1__*) ; 
 scalar_t__ FM_MAC_ConfigException (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FM_MAC_ConfigResetOnInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FM_MAC_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dtsec_fm_mac_exception_callback ; 
 int /*<<< orphan*/  dtsec_fm_mac_free (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_fm_mac_mdio_event_callback ; 
 int /*<<< orphan*/  e_FM_MAC_EX_1G_RX_CTL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtsec_fm_mac_init(struct dtsec_softc *sc, uint8_t *mac)
{
	t_FmMacParams params;
	t_Error error;

	memset(&params, 0, sizeof(params));
	memcpy(&params.addr, mac, sizeof(params.addr));

	params.baseAddr = rman_get_bushandle(sc->sc_mem);
	params.enetMode = sc->sc_mac_enet_mode;
	params.macId = sc->sc_eth_id;
	params.mdioIrq = sc->sc_mac_mdio_irq;
	params.f_Event = dtsec_fm_mac_mdio_event_callback;
	params.f_Exception = dtsec_fm_mac_exception_callback;
	params.h_App = sc;
	params.h_Fm = sc->sc_fmh;

	sc->sc_mach = FM_MAC_Config(&params);
	if (sc->sc_mach == NULL) {
		device_printf(sc->sc_dev, "couldn't configure FM_MAC module.\n"
		    );
		return (ENXIO);
	}

	error = FM_MAC_ConfigResetOnInit(sc->sc_mach, TRUE);
	if (error != E_OK) {
		device_printf(sc->sc_dev, "couldn't enable reset on init "
		    "feature.\n");
		dtsec_fm_mac_free(sc);
		return (ENXIO);
	}

	/* Do not inform about pause frames */
	error = FM_MAC_ConfigException(sc->sc_mach, e_FM_MAC_EX_1G_RX_CTL,
	    FALSE);
	if (error != E_OK) {
		device_printf(sc->sc_dev, "couldn't disable pause frames "
			"exception.\n");
		dtsec_fm_mac_free(sc);
		return (ENXIO);
	}

	error = FM_MAC_Init(sc->sc_mach);
	if (error != E_OK) {
		device_printf(sc->sc_dev, "couldn't initialize FM_MAC module."
		    "\n");
		dtsec_fm_mac_free(sc);
		return (ENXIO);
	}

	return (0);
}