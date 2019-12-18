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
struct ecore_func_state_params {int cmd; int /*<<< orphan*/  ramrod_flags; struct ecore_func_sp_obj* f_obj; } ;
struct ecore_func_sp_obj {unsigned long pending; int (* check_transition ) (struct bxe_softc*,struct ecore_func_sp_obj*,struct ecore_func_state_params*) ;int (* send_cmd ) (struct bxe_softc*,struct ecore_func_state_params*) ;int (* wait_comp ) (struct bxe_softc*,struct ecore_func_sp_obj*,int) ;int /*<<< orphan*/  next_state; int /*<<< orphan*/  one_pending_mutex; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_func_cmd { ____Placeholder_ecore_func_cmd } ecore_func_cmd ;

/* Variables and functions */
 int ECORE_BUSY ; 
 int /*<<< orphan*/  ECORE_CLEAR_BIT (int,unsigned long*) ; 
 int /*<<< orphan*/  ECORE_ERR (char*) ; 
 int /*<<< orphan*/  ECORE_F_STATE_MAX ; 
 int /*<<< orphan*/  ECORE_MSLEEP (int) ; 
 int /*<<< orphan*/  ECORE_MUTEX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_MUTEX_UNLOCK (int /*<<< orphan*/ *) ; 
 int ECORE_RET_PENDING (int,unsigned long*) ; 
 int /*<<< orphan*/  ECORE_SET_BIT (int,unsigned long*) ; 
 int /*<<< orphan*/  ECORE_SMP_MB_AFTER_CLEAR_BIT () ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  RAMROD_RETRY ; 
 int /*<<< orphan*/  ecore_func_state_change_comp (struct bxe_softc*,struct ecore_func_sp_obj*,int) ; 
 int stub1 (struct bxe_softc*,struct ecore_func_sp_obj*,struct ecore_func_state_params*) ; 
 int stub2 (struct bxe_softc*,struct ecore_func_sp_obj*,struct ecore_func_state_params*) ; 
 int stub3 (struct bxe_softc*,struct ecore_func_state_params*) ; 
 int stub4 (struct bxe_softc*,struct ecore_func_sp_obj*,int) ; 

int ecore_func_state_change(struct bxe_softc *sc,
			    struct ecore_func_state_params *params)
{
	struct ecore_func_sp_obj *o = params->f_obj;
	int rc, cnt = 300;
	enum ecore_func_cmd cmd = params->cmd;
	unsigned long *pending = &o->pending;

	ECORE_MUTEX_LOCK(&o->one_pending_mutex);

	/* Check that the requested transition is legal */
	rc = o->check_transition(sc, o, params);
	if ((rc == ECORE_BUSY) &&
	    (ECORE_TEST_BIT(RAMROD_RETRY, &params->ramrod_flags))) {
		while ((rc == ECORE_BUSY) && (--cnt > 0)) {
			ECORE_MUTEX_UNLOCK(&o->one_pending_mutex);
			ECORE_MSLEEP(10);
			ECORE_MUTEX_LOCK(&o->one_pending_mutex);
			rc = o->check_transition(sc, o, params);
		}
		if (rc == ECORE_BUSY) {
			ECORE_MUTEX_UNLOCK(&o->one_pending_mutex);
			ECORE_ERR("timeout waiting for previous ramrod completion\n");
			return rc;
		}
	} else if (rc) {
		ECORE_MUTEX_UNLOCK(&o->one_pending_mutex);
		return rc;
	}

	/* Set "pending" bit */
	ECORE_SET_BIT(cmd, pending);

	/* Don't send a command if only driver cleanup was requested */
	if (ECORE_TEST_BIT(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags)) {
		ecore_func_state_change_comp(sc, o, cmd);
		ECORE_MUTEX_UNLOCK(&o->one_pending_mutex);
	} else {
		/* Send a ramrod */
		rc = o->send_cmd(sc, params);

		ECORE_MUTEX_UNLOCK(&o->one_pending_mutex);

		if (rc) {
			o->next_state = ECORE_F_STATE_MAX;
			ECORE_CLEAR_BIT(cmd, pending);
			ECORE_SMP_MB_AFTER_CLEAR_BIT();
			return rc;
		}

		if (ECORE_TEST_BIT(RAMROD_COMP_WAIT, &params->ramrod_flags)) {
			rc = o->wait_comp(sc, o, cmd);
			if (rc)
				return rc;

			return ECORE_SUCCESS;
		}
	}

	return ECORE_RET_PENDING(cmd, pending);
}