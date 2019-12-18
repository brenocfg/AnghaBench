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
typedef  int uint8_t ;
struct ecore_queue_update_params {int /*<<< orphan*/  update_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ setup; struct ecore_queue_update_params update; } ;
struct ecore_queue_state_params {int cmd; TYPE_2__ params; int /*<<< orphan*/  ramrod_flags; } ;
struct ecore_queue_sp_obj {int state; int num_tx_only; int pending; int next_state; int next_tx_only; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_queue_cmd { ____Placeholder_ecore_queue_cmd } ecore_queue_cmd ;
typedef  enum ecore_q_state { ____Placeholder_ecore_q_state } ecore_q_state ;

/* Variables and functions */
 int ECORE_BUSY ; 
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int,int,...) ; 
 int ECORE_Q_CMD_ACTIVATE ; 
 int ECORE_Q_CMD_CFC_DEL ; 
 int ECORE_Q_CMD_DEACTIVATE ; 
 int ECORE_Q_CMD_EMPTY ; 
 int ECORE_Q_CMD_HALT ; 
 int ECORE_Q_CMD_INIT ; 
 int ECORE_Q_CMD_SETUP ; 
 int ECORE_Q_CMD_SETUP_TX_ONLY ; 
 int ECORE_Q_CMD_TERMINATE ; 
 int ECORE_Q_CMD_UPDATE ; 
 int ECORE_Q_CMD_UPDATE_TPA ; 
 int /*<<< orphan*/  ECORE_Q_FLG_ACTIVE ; 
#define  ECORE_Q_STATE_ACTIVE 135 
#define  ECORE_Q_STATE_INACTIVE 134 
#define  ECORE_Q_STATE_INITIALIZED 133 
 int ECORE_Q_STATE_MAX ; 
#define  ECORE_Q_STATE_MCOS_TERMINATED 132 
#define  ECORE_Q_STATE_MULTI_COS 131 
#define  ECORE_Q_STATE_RESET 130 
#define  ECORE_Q_STATE_STOPPED 129 
#define  ECORE_Q_STATE_TERMINATED 128 
 int /*<<< orphan*/  ECORE_Q_UPDATE_ACTIVATE ; 
 int /*<<< orphan*/  ECORE_Q_UPDATE_ACTIVATE_CHNG ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 

__attribute__((used)) static int ecore_queue_chk_transition(struct bxe_softc *sc,
				      struct ecore_queue_sp_obj *o,
				      struct ecore_queue_state_params *params)
{
	enum ecore_q_state state = o->state, next_state = ECORE_Q_STATE_MAX;
	enum ecore_queue_cmd cmd = params->cmd;
	struct ecore_queue_update_params *update_params =
		 &params->params.update;
	uint8_t next_tx_only = o->num_tx_only;

	/* Forget all pending for completion commands if a driver only state
	 * transition has been requested.
	 */
	if (ECORE_TEST_BIT(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags)) {
		o->pending = 0;
		o->next_state = ECORE_Q_STATE_MAX;
	}

	/* Don't allow a next state transition if we are in the middle of
	 * the previous one.
	 */
	if (o->pending) {
		ECORE_ERR("Blocking transition since pending was %lx\n",
			  o->pending);
		return ECORE_BUSY;
	}

	switch (state) {
	case ECORE_Q_STATE_RESET:
		if (cmd == ECORE_Q_CMD_INIT)
			next_state = ECORE_Q_STATE_INITIALIZED;

		break;
	case ECORE_Q_STATE_INITIALIZED:
		if (cmd == ECORE_Q_CMD_SETUP) {
			if (ECORE_TEST_BIT(ECORE_Q_FLG_ACTIVE,
					   &params->params.setup.flags))
				next_state = ECORE_Q_STATE_ACTIVE;
			else
				next_state = ECORE_Q_STATE_INACTIVE;
		}

		break;
	case ECORE_Q_STATE_ACTIVE:
		if (cmd == ECORE_Q_CMD_DEACTIVATE)
			next_state = ECORE_Q_STATE_INACTIVE;

		else if ((cmd == ECORE_Q_CMD_EMPTY) ||
			 (cmd == ECORE_Q_CMD_UPDATE_TPA))
			next_state = ECORE_Q_STATE_ACTIVE;

		else if (cmd == ECORE_Q_CMD_SETUP_TX_ONLY) {
			next_state = ECORE_Q_STATE_MULTI_COS;
			next_tx_only = 1;
		}

		else if (cmd == ECORE_Q_CMD_HALT)
			next_state = ECORE_Q_STATE_STOPPED;

		else if (cmd == ECORE_Q_CMD_UPDATE) {
			/* If "active" state change is requested, update the
			 *  state accordingly.
			 */
			if (ECORE_TEST_BIT(ECORE_Q_UPDATE_ACTIVATE_CHNG,
					   &update_params->update_flags) &&
			    !ECORE_TEST_BIT(ECORE_Q_UPDATE_ACTIVATE,
					    &update_params->update_flags))
				next_state = ECORE_Q_STATE_INACTIVE;
			else
				next_state = ECORE_Q_STATE_ACTIVE;
		}

		break;
	case ECORE_Q_STATE_MULTI_COS:
		if (cmd == ECORE_Q_CMD_TERMINATE)
			next_state = ECORE_Q_STATE_MCOS_TERMINATED;

		else if (cmd == ECORE_Q_CMD_SETUP_TX_ONLY) {
			next_state = ECORE_Q_STATE_MULTI_COS;
			next_tx_only = o->num_tx_only + 1;
		}

		else if ((cmd == ECORE_Q_CMD_EMPTY) ||
			 (cmd == ECORE_Q_CMD_UPDATE_TPA))
			next_state = ECORE_Q_STATE_MULTI_COS;

		else if (cmd == ECORE_Q_CMD_UPDATE) {
			/* If "active" state change is requested, update the
			 *  state accordingly.
			 */
			if (ECORE_TEST_BIT(ECORE_Q_UPDATE_ACTIVATE_CHNG,
					   &update_params->update_flags) &&
			    !ECORE_TEST_BIT(ECORE_Q_UPDATE_ACTIVATE,
					    &update_params->update_flags))
				next_state = ECORE_Q_STATE_INACTIVE;
			else
				next_state = ECORE_Q_STATE_MULTI_COS;
		}

		break;
	case ECORE_Q_STATE_MCOS_TERMINATED:
		if (cmd == ECORE_Q_CMD_CFC_DEL) {
			next_tx_only = o->num_tx_only - 1;
			if (next_tx_only == 0)
				next_state = ECORE_Q_STATE_ACTIVE;
			else
				next_state = ECORE_Q_STATE_MULTI_COS;
		}

		break;
	case ECORE_Q_STATE_INACTIVE:
		if (cmd == ECORE_Q_CMD_ACTIVATE)
			next_state = ECORE_Q_STATE_ACTIVE;

		else if ((cmd == ECORE_Q_CMD_EMPTY) ||
			 (cmd == ECORE_Q_CMD_UPDATE_TPA))
			next_state = ECORE_Q_STATE_INACTIVE;

		else if (cmd == ECORE_Q_CMD_HALT)
			next_state = ECORE_Q_STATE_STOPPED;

		else if (cmd == ECORE_Q_CMD_UPDATE) {
			/* If "active" state change is requested, update the
			 * state accordingly.
			 */
			if (ECORE_TEST_BIT(ECORE_Q_UPDATE_ACTIVATE_CHNG,
					   &update_params->update_flags) &&
			    ECORE_TEST_BIT(ECORE_Q_UPDATE_ACTIVATE,
					   &update_params->update_flags)){
				if (o->num_tx_only == 0)
					next_state = ECORE_Q_STATE_ACTIVE;
				else /* tx only queues exist for this queue */
					next_state = ECORE_Q_STATE_MULTI_COS;
			} else
				next_state = ECORE_Q_STATE_INACTIVE;
		}

		break;
	case ECORE_Q_STATE_STOPPED:
		if (cmd == ECORE_Q_CMD_TERMINATE)
			next_state = ECORE_Q_STATE_TERMINATED;

		break;
	case ECORE_Q_STATE_TERMINATED:
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
		o->next_tx_only = next_tx_only;
		return ECORE_SUCCESS;
	}

	ECORE_MSG(sc, "Bad state transition request: %d %d\n", state, cmd);

	return ECORE_INVAL;
}