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
struct TYPE_8__ {int /*<<< orphan*/  f_TxConf; int /*<<< orphan*/  dataMemAttributes; int /*<<< orphan*/  dataMemId; int /*<<< orphan*/  liodnOffset; int /*<<< orphan*/  h_FmMuram; } ;
struct TYPE_6__ {TYPE_3__ imRxTxParams; } ;
struct TYPE_7__ {int portId; TYPE_1__ specificParams; struct dtsec_softc* h_App; int /*<<< orphan*/  f_Exception; int /*<<< orphan*/  liodnBase; int /*<<< orphan*/  independentModeEnable; int /*<<< orphan*/  portType; int /*<<< orphan*/  h_Fm; scalar_t__ baseAddr; } ;
typedef  TYPE_2__ t_FmPortParams ;
typedef  TYPE_3__ t_FmPortImRxTxParams ;
typedef  scalar_t__ t_Error ;
struct dtsec_softc {scalar_t__ sc_port_tx_hw_id; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_txph; int /*<<< orphan*/  sc_muramh; int /*<<< orphan*/  sc_eth_dev_type; int /*<<< orphan*/  sc_fmh; scalar_t__ sc_fm_base; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/ * FM_PORT_Config (TYPE_2__*) ; 
 int /*<<< orphan*/  FM_PORT_Free (int /*<<< orphan*/ *) ; 
 scalar_t__ FM_PORT_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FM_PORT_LIODN_BASE ; 
 int /*<<< orphan*/  FM_PORT_LIODN_OFFSET ; 
 int /*<<< orphan*/  FM_PORT_MEM_ATTR ; 
 int /*<<< orphan*/  FM_PORT_MEM_ID ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dtsec_fm_port_tx_exception_callback ; 
 int /*<<< orphan*/  dtsec_fm_port_tx_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtsec_im_fm_port_tx_conf_callback ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int
dtsec_im_fm_port_tx_init(struct dtsec_softc *sc, int unit)
{
	t_FmPortParams params;
	t_FmPortImRxTxParams *im_params;
	t_Error error;

	memset(&params, 0, sizeof(params));

	params.baseAddr = sc->sc_fm_base + sc->sc_port_tx_hw_id;
	params.h_Fm = sc->sc_fmh;
	params.portType = dtsec_fm_port_tx_type(sc->sc_eth_dev_type);
	params.portId = unit;
	params.independentModeEnable = TRUE;
	params.liodnBase = FM_PORT_LIODN_BASE;
	params.f_Exception = dtsec_fm_port_tx_exception_callback;
	params.h_App = sc;

	im_params = &params.specificParams.imRxTxParams;
	im_params->h_FmMuram = sc->sc_muramh;
	im_params->liodnOffset = FM_PORT_LIODN_OFFSET;
	im_params->dataMemId = FM_PORT_MEM_ID;
	im_params->dataMemAttributes = FM_PORT_MEM_ATTR;
	im_params->f_TxConf = dtsec_im_fm_port_tx_conf_callback;

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