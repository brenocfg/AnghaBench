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
struct ecore_queue_state_params {int cmd; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int ECORE_INVAL ; 
#define  ECORE_Q_CMD_ACTIVATE 137 
#define  ECORE_Q_CMD_CFC_DEL 136 
#define  ECORE_Q_CMD_DEACTIVATE 135 
#define  ECORE_Q_CMD_EMPTY 134 
#define  ECORE_Q_CMD_HALT 133 
#define  ECORE_Q_CMD_INIT 132 
#define  ECORE_Q_CMD_SETUP_TX_ONLY 131 
#define  ECORE_Q_CMD_TERMINATE 130 
#define  ECORE_Q_CMD_UPDATE 129 
#define  ECORE_Q_CMD_UPDATE_TPA 128 
 int ecore_q_init (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_q_send_activate (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_q_send_cfc_del (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_q_send_deactivate (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_q_send_empty (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_q_send_halt (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_q_send_setup_tx_only (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_q_send_terminate (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_q_send_update (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_q_send_update_tpa (struct bxe_softc*,struct ecore_queue_state_params*) ; 

__attribute__((used)) static inline int ecore_queue_send_cmd_cmn(struct bxe_softc *sc,
					struct ecore_queue_state_params *params)
{
	switch (params->cmd) {
	case ECORE_Q_CMD_INIT:
		return ecore_q_init(sc, params);
	case ECORE_Q_CMD_SETUP_TX_ONLY:
		return ecore_q_send_setup_tx_only(sc, params);
	case ECORE_Q_CMD_DEACTIVATE:
		return ecore_q_send_deactivate(sc, params);
	case ECORE_Q_CMD_ACTIVATE:
		return ecore_q_send_activate(sc, params);
	case ECORE_Q_CMD_UPDATE:
		return ecore_q_send_update(sc, params);
	case ECORE_Q_CMD_UPDATE_TPA:
		return ecore_q_send_update_tpa(sc, params);
	case ECORE_Q_CMD_HALT:
		return ecore_q_send_halt(sc, params);
	case ECORE_Q_CMD_CFC_DEL:
		return ecore_q_send_cfc_del(sc, params);
	case ECORE_Q_CMD_TERMINATE:
		return ecore_q_send_terminate(sc, params);
	case ECORE_Q_CMD_EMPTY:
		return ecore_q_send_empty(sc, params);
	default:
		ECORE_ERR("Unknown command: %d\n", params->cmd);
		return ECORE_INVAL;
	}
}