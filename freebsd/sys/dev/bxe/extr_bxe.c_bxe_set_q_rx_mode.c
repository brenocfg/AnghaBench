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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ecore_rx_mode_ramrod_params {unsigned long ramrod_flags; unsigned long rx_mode_flags; unsigned long rx_accept_flags; unsigned long tx_accept_flags; int /*<<< orphan*/  rdata_mapping; int /*<<< orphan*/  rdata; int /*<<< orphan*/  state; int /*<<< orphan*/ * pstate; int /*<<< orphan*/  func_id; int /*<<< orphan*/ * rx_mode_obj; int /*<<< orphan*/  cl_id; scalar_t__ cid; } ;
struct bxe_softc {int /*<<< orphan*/  rx_mode; int /*<<< orphan*/  sp_state; int /*<<< orphan*/  rx_mode_obj; } ;
typedef  int /*<<< orphan*/  ramrod_param ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BXE_SP (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXE_SP_MAPPING (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_FILTER_RX_MODE_PENDING ; 
 int /*<<< orphan*/  SC_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_config_rx_mode (struct bxe_softc*,struct ecore_rx_mode_ramrod_params*) ; 
 int /*<<< orphan*/  memset (struct ecore_rx_mode_ramrod_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rx_mode_rdata ; 

__attribute__((used)) static int
bxe_set_q_rx_mode(struct bxe_softc *sc,
                  uint8_t          cl_id,
                  unsigned long    rx_mode_flags,
                  unsigned long    rx_accept_flags,
                  unsigned long    tx_accept_flags,
                  unsigned long    ramrod_flags)
{
    struct ecore_rx_mode_ramrod_params ramrod_param;
    int rc;

    memset(&ramrod_param, 0, sizeof(ramrod_param));

    /* Prepare ramrod parameters */
    ramrod_param.cid = 0;
    ramrod_param.cl_id = cl_id;
    ramrod_param.rx_mode_obj = &sc->rx_mode_obj;
    ramrod_param.func_id = SC_FUNC(sc);

    ramrod_param.pstate = &sc->sp_state;
    ramrod_param.state = ECORE_FILTER_RX_MODE_PENDING;

    ramrod_param.rdata = BXE_SP(sc, rx_mode_rdata);
    ramrod_param.rdata_mapping = BXE_SP_MAPPING(sc, rx_mode_rdata);

    bxe_set_bit(ECORE_FILTER_RX_MODE_PENDING, &sc->sp_state);

    ramrod_param.ramrod_flags = ramrod_flags;
    ramrod_param.rx_mode_flags = rx_mode_flags;

    ramrod_param.rx_accept_flags = rx_accept_flags;
    ramrod_param.tx_accept_flags = tx_accept_flags;

    rc = ecore_config_rx_mode(sc, &ramrod_param);
    if (rc < 0) {
        BLOGE(sc, "Set rx_mode %d cli_id 0x%x rx_mode_flags 0x%x "
            "rx_accept_flags 0x%x tx_accept_flags 0x%x "
            "ramrod_flags 0x%x rc %d failed\n", sc->rx_mode, cl_id,
            (uint32_t)rx_mode_flags, (uint32_t)rx_accept_flags,
            (uint32_t)tx_accept_flags, (uint32_t)ramrod_flags, rc);
        return (rc);
    }

    return (0);
}