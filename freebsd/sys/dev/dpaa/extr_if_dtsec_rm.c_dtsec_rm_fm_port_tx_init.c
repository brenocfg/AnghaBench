#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ opLiodnOffset; int /*<<< orphan*/  qmChannel; int /*<<< orphan*/  dfltFqid; int /*<<< orphan*/  errFqid; } ;
struct TYPE_6__ {TYPE_3__ nonRxParams; } ;
struct TYPE_7__ {int independentModeEnable; TYPE_1__ specificParams; struct dtsec_softc* h_App; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  liodnBase; int /*<<< orphan*/  portId; int /*<<< orphan*/  portType; int /*<<< orphan*/  h_Fm; scalar_t__ baseAddr; } ;
typedef  TYPE_2__ t_FmPortParams ;
typedef  TYPE_3__ t_FmPortNonRxParams ;
typedef  scalar_t__ t_Error ;
struct dtsec_softc {scalar_t__ sc_port_tx_hw_id; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_txph; int /*<<< orphan*/  sc_port_tx_qman_chan; int /*<<< orphan*/  sc_tx_conf_fqid; int /*<<< orphan*/  sc_eth_id; int /*<<< orphan*/  sc_eth_dev_type; int /*<<< orphan*/  sc_fmh; scalar_t__ sc_fm_base; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/ * FM_PORT_Config (TYPE_2__*) ; 
 int /*<<< orphan*/  FM_PORT_Free (int /*<<< orphan*/ *) ; 
 scalar_t__ FM_PORT_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FM_PORT_LIODN_BASE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dtsec_fm_port_tx_exception_callback ; 
 int /*<<< orphan*/  dtsec_fm_port_tx_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int
dtsec_rm_fm_port_tx_init(struct dtsec_softc *sc, int unit)
{
	t_FmPortParams params;
	t_FmPortNonRxParams *tx_params;
	t_Error error;

	memset(&params, 0, sizeof(params));

	params.baseAddr = sc->sc_fm_base + sc->sc_port_tx_hw_id;
	params.h_Fm = sc->sc_fmh;
	params.portType = dtsec_fm_port_tx_type(sc->sc_eth_dev_type);
	params.portId = sc->sc_eth_id;
	params.independentModeEnable = false;
	params.liodnBase = FM_PORT_LIODN_BASE;
	params.f_Exception = dtsec_fm_port_tx_exception_callback;
	params.h_App = sc;

	tx_params = &params.specificParams.nonRxParams;
	tx_params->errFqid = sc->sc_tx_conf_fqid;
	tx_params->dfltFqid = sc->sc_tx_conf_fqid;
	tx_params->qmChannel = sc->sc_port_tx_qman_chan;
#ifdef FM_OP_PARTITION_ERRATA_FMANx8
	tx_params->opLiodnOffset = 0;
#endif

	sc->sc_txph = FM_PORT_Config(&params);
	if (sc->sc_txph == NULL) {
		device_printf(sc->sc_dev, "couldn't configure FM Port TX.\n");
		return (ENXIO);
	}

	error = FM_PORT_Init(sc->sc_txph);
	if (error != E_OK) {
		device_printf(sc->sc_dev, "couldn't initialize FM Port TX.\n");
		FM_PORT_Free(sc->sc_txph);
		return (ENXIO);
	}

	if (bootverbose)
		device_printf(sc->sc_dev, "TX hw port 0x%02x initialized.\n",
		    sc->sc_port_tx_hw_id);

	return (0);
}