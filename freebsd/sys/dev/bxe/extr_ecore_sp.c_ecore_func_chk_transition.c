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
struct ecore_func_state_params {int cmd; scalar_t__ ramrod_flags; } ;
struct ecore_func_sp_obj {int state; int next_state; scalar_t__ pending; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_func_state { ____Placeholder_ecore_func_state } ecore_func_state ;
typedef  enum ecore_func_cmd { ____Placeholder_ecore_func_cmd } ecore_func_cmd ;

/* Variables and functions */
 int ECORE_BUSY ; 
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int ECORE_F_CMD_AFEX_UPDATE ; 
 int ECORE_F_CMD_AFEX_VIFLISTS ; 
 int ECORE_F_CMD_HW_INIT ; 
 int ECORE_F_CMD_HW_RESET ; 
 int ECORE_F_CMD_SET_TIMESYNC ; 
 int ECORE_F_CMD_START ; 
 int ECORE_F_CMD_STOP ; 
 int ECORE_F_CMD_SWITCH_UPDATE ; 
 int ECORE_F_CMD_TX_START ; 
 int ECORE_F_CMD_TX_STOP ; 
#define  ECORE_F_STATE_INITIALIZED 131 
 int ECORE_F_STATE_MAX ; 
#define  ECORE_F_STATE_RESET 130 
#define  ECORE_F_STATE_STARTED 129 
#define  ECORE_F_STATE_TX_STOPPED 128 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int,int,...) ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_TEST_BIT (int,scalar_t__*) ; 
 int RAMROD_DRV_CLR_ONLY ; 

__attribute__((used)) static int ecore_func_chk_transition(struct bxe_softc *sc,
				     struct ecore_func_sp_obj *o,
				     struct ecore_func_state_params *params)
{
	enum ecore_func_state state = o->state, next_state = ECORE_F_STATE_MAX;
	enum ecore_func_cmd cmd = params->cmd;

	/* Forget all pending for completion commands if a driver only state
	 * transition has been requested.
	 */
	if (ECORE_TEST_BIT(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags)) {
		o->pending = 0;
		o->next_state = ECORE_F_STATE_MAX;
	}

	/* Don't allow a next state transition if we are in the middle of
	 * the previous one.
	 */
	if (o->pending)
		return ECORE_BUSY;

	switch (state) {
	case ECORE_F_STATE_RESET:
		if (cmd == ECORE_F_CMD_HW_INIT)
			next_state = ECORE_F_STATE_INITIALIZED;

		break;
	case ECORE_F_STATE_INITIALIZED:
		if (cmd == ECORE_F_CMD_START)
			next_state = ECORE_F_STATE_STARTED;

		else if (cmd == ECORE_F_CMD_HW_RESET)
			next_state = ECORE_F_STATE_RESET;

		break;
	case ECORE_F_STATE_STARTED:
		if (cmd == ECORE_F_CMD_STOP)
			next_state = ECORE_F_STATE_INITIALIZED;
		/* afex ramrods can be sent only in started mode, and only
		 * if not pending for function_stop ramrod completion
		 * for these events - next state remained STARTED.
		 */
		else if ((cmd == ECORE_F_CMD_AFEX_UPDATE) &&
			 (!ECORE_TEST_BIT(ECORE_F_CMD_STOP, &o->pending)))
			next_state = ECORE_F_STATE_STARTED;

		else if ((cmd == ECORE_F_CMD_AFEX_VIFLISTS) &&
			 (!ECORE_TEST_BIT(ECORE_F_CMD_STOP, &o->pending)))
			next_state = ECORE_F_STATE_STARTED;

		/* Switch_update ramrod can be sent in either started or
		 * tx_stopped state, and it doesn't change the state.
		 */
		else if ((cmd == ECORE_F_CMD_SWITCH_UPDATE) &&
			 (!ECORE_TEST_BIT(ECORE_F_CMD_STOP, &o->pending)))
			next_state = ECORE_F_STATE_STARTED;

		else if ((cmd == ECORE_F_CMD_SET_TIMESYNC) &&
			 (!ECORE_TEST_BIT(ECORE_F_CMD_STOP, &o->pending)))
			next_state = ECORE_F_STATE_STARTED;

		else if (cmd == ECORE_F_CMD_TX_STOP)
			next_state = ECORE_F_STATE_TX_STOPPED;

		break;
	case ECORE_F_STATE_TX_STOPPED:
		if ((cmd == ECORE_F_CMD_SWITCH_UPDATE) &&
		    (!ECORE_TEST_BIT(ECORE_F_CMD_STOP, &o->pending)))
			next_state = ECORE_F_STATE_TX_STOPPED;

		else if ((cmd == ECORE_F_CMD_SET_TIMESYNC) &&
		    (!ECORE_TEST_BIT(ECORE_F_CMD_STOP, &o->pending)))
			next_state = ECORE_F_STATE_TX_STOPPED;

		else if (cmd == ECORE_F_CMD_TX_START)
			next_state = ECORE_F_STATE_STARTED;

		break;
	default:
		ECORE_ERR("Unknown state: %d\n", state);
	}

	/* Transition is assured */
	if (next_state != ECORE_F_STATE_MAX) {
		ECORE_MSG(sc, "Good function state transition: %d(%d)->%d\n",
			  state, cmd, next_state);
		o->next_state = next_state;
		return ECORE_SUCCESS;
	}

	ECORE_MSG(sc, "Bad function state transition request: %d %d\n",
		  state, cmd);

	return ECORE_INVAL;
}