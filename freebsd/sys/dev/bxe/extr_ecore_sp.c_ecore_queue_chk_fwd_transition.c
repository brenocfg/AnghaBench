#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ tx_only; } ;
struct ecore_queue_state_params {int cmd; TYPE_2__ params; } ;
struct ecore_queue_sp_obj {int state; int next_state; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_queue_cmd { ____Placeholder_ecore_queue_cmd } ecore_queue_cmd ;
typedef  enum ecore_q_state { ____Placeholder_ecore_q_state } ecore_q_state ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int,int,...) ; 
 int ECORE_Q_CMD_CFC_DEL ; 
 int ECORE_Q_CMD_INIT ; 
 int ECORE_Q_CMD_SETUP_TX_ONLY ; 
 int /*<<< orphan*/  ECORE_Q_FLG_ACTIVE ; 
#define  ECORE_Q_STATE_ACTIVE 131 
#define  ECORE_Q_STATE_INACTIVE 130 
#define  ECORE_Q_STATE_INITIALIZED 129 
 int ECORE_Q_STATE_MAX ; 
#define  ECORE_Q_STATE_RESET 128 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecore_queue_chk_fwd_transition(struct bxe_softc *sc,
					  struct ecore_queue_sp_obj *o,
					struct ecore_queue_state_params *params)
{
	enum ecore_q_state state = o->state, next_state = ECORE_Q_STATE_MAX;
	enum ecore_queue_cmd cmd = params->cmd;

	switch (state) {
	case ECORE_Q_STATE_RESET:
		if (cmd == ECORE_Q_CMD_INIT)
			next_state = ECORE_Q_STATE_INITIALIZED;

		break;
	case ECORE_Q_STATE_INITIALIZED:
		if (cmd == ECORE_Q_CMD_SETUP_TX_ONLY) {
			if (ECORE_TEST_BIT(ECORE_Q_FLG_ACTIVE,
					   &params->params.tx_only.flags))
				next_state = ECORE_Q_STATE_ACTIVE;
			else
				next_state = ECORE_Q_STATE_INACTIVE;
		}

		break;
	case ECORE_Q_STATE_ACTIVE:
	case ECORE_Q_STATE_INACTIVE:
		if (cmd == ECORE_Q_CMD_CFC_DEL)
			next_state = ECORE_Q_STATE_RESET;

		break;
	default:
		ECORE_ERR("Illegal state: %d\n", state);
	}

	/* Transition is assured */
	if (next_state != ECORE_Q_STATE_MAX) {
		ECORE_MSG(sc, "Good state transition: %d(%d)->%d\n",
			  state, cmd, next_state);
		o->next_state = next_state;
		return ECORE_SUCCESS;
	}

	ECORE_MSG(sc, "Bad state transition request: %d %d\n", state, cmd);
	return ECORE_INVAL;
}