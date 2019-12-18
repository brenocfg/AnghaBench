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
#define  ECORE_Q_CMD_ACTIVATE 138 
#define  ECORE_Q_CMD_CFC_DEL 137 
#define  ECORE_Q_CMD_DEACTIVATE 136 
#define  ECORE_Q_CMD_EMPTY 135 
#define  ECORE_Q_CMD_HALT 134 
#define  ECORE_Q_CMD_INIT 133 
#define  ECORE_Q_CMD_SETUP 132 
#define  ECORE_Q_CMD_SETUP_TX_ONLY 131 
#define  ECORE_Q_CMD_TERMINATE 130 
#define  ECORE_Q_CMD_UPDATE 129 
#define  ECORE_Q_CMD_UPDATE_TPA 128 
 int ecore_q_send_setup_e2 (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int ecore_queue_send_cmd_cmn (struct bxe_softc*,struct ecore_queue_state_params*) ; 

__attribute__((used)) static int ecore_queue_send_cmd_e2(struct bxe_softc *sc,
				   struct ecore_queue_state_params *params)
{
	switch (params->cmd) {
	case ECORE_Q_CMD_SETUP:
		return ecore_q_send_setup_e2(sc, params);
	case ECORE_Q_CMD_INIT:
	case ECORE_Q_CMD_SETUP_TX_ONLY:
	case ECORE_Q_CMD_DEACTIVATE:
	case ECORE_Q_CMD_ACTIVATE:
	case ECORE_Q_CMD_UPDATE:
	case ECORE_Q_CMD_UPDATE_TPA:
	case ECORE_Q_CMD_HALT:
	case ECORE_Q_CMD_CFC_DEL:
	case ECORE_Q_CMD_TERMINATE:
	case ECORE_Q_CMD_EMPTY:
		return ecore_queue_send_cmd_cmn(sc, params);
	default:
		ECORE_ERR("Unknown command: %d\n", params->cmd);
		return ECORE_INVAL;
	}
}