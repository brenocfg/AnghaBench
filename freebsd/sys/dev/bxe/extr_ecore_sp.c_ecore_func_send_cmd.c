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
struct ecore_func_state_params {int cmd; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
#define  ECORE_F_CMD_AFEX_UPDATE 137 
#define  ECORE_F_CMD_AFEX_VIFLISTS 136 
#define  ECORE_F_CMD_HW_INIT 135 
#define  ECORE_F_CMD_HW_RESET 134 
#define  ECORE_F_CMD_SET_TIMESYNC 133 
#define  ECORE_F_CMD_START 132 
#define  ECORE_F_CMD_STOP 131 
#define  ECORE_F_CMD_SWITCH_UPDATE 130 
#define  ECORE_F_CMD_TX_START 129 
#define  ECORE_F_CMD_TX_STOP 128 
 int ECORE_INVAL ; 
 int ecore_func_hw_init (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int ecore_func_hw_reset (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int ecore_func_send_afex_update (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int ecore_func_send_afex_viflists (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int ecore_func_send_set_timesync (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int ecore_func_send_start (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int ecore_func_send_stop (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int ecore_func_send_switch_update (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int ecore_func_send_tx_start (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int ecore_func_send_tx_stop (struct bxe_softc*,struct ecore_func_state_params*) ; 

__attribute__((used)) static int ecore_func_send_cmd(struct bxe_softc *sc,
			       struct ecore_func_state_params *params)
{
	switch (params->cmd) {
	case ECORE_F_CMD_HW_INIT:
		return ecore_func_hw_init(sc, params);
	case ECORE_F_CMD_START:
		return ecore_func_send_start(sc, params);
	case ECORE_F_CMD_STOP:
		return ecore_func_send_stop(sc, params);
	case ECORE_F_CMD_HW_RESET:
		return ecore_func_hw_reset(sc, params);
	case ECORE_F_CMD_AFEX_UPDATE:
		return ecore_func_send_afex_update(sc, params);
	case ECORE_F_CMD_AFEX_VIFLISTS:
		return ecore_func_send_afex_viflists(sc, params);
	case ECORE_F_CMD_TX_STOP:
		return ecore_func_send_tx_stop(sc, params);
	case ECORE_F_CMD_TX_START:
		return ecore_func_send_tx_start(sc, params);
	case ECORE_F_CMD_SWITCH_UPDATE:
		return ecore_func_send_switch_update(sc, params);
	case ECORE_F_CMD_SET_TIMESYNC:
		return ecore_func_send_set_timesync(sc, params);
	default:
		ECORE_ERR("Unknown command: %d\n", params->cmd);
		return ECORE_INVAL;
	}
}