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
struct ecore_queue_state_params {int /*<<< orphan*/  ramrod_flags; struct ecore_queue_sp_obj* q_obj; } ;
struct ecore_queue_sp_obj {unsigned long pending; int (* check_transition ) (struct bxe_softc*,struct ecore_queue_sp_obj*,struct ecore_queue_state_params*) ;int (* set_pending ) (struct ecore_queue_sp_obj*,struct ecore_queue_state_params*) ;int (* send_cmd ) (struct bxe_softc*,struct ecore_queue_state_params*) ;int (* wait_comp ) (struct bxe_softc*,struct ecore_queue_sp_obj*,int) ;int /*<<< orphan*/  next_state; int /*<<< orphan*/  (* complete_cmd ) (struct bxe_softc*,struct ecore_queue_sp_obj*,int) ;} ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CLEAR_BIT (int,unsigned long*) ; 
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,unsigned long) ; 
 int /*<<< orphan*/  ECORE_Q_STATE_MAX ; 
 int ECORE_RET_PENDING (int,unsigned long*) ; 
 int /*<<< orphan*/  ECORE_SMP_MB_AFTER_CLEAR_BIT () ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int stub1 (struct bxe_softc*,struct ecore_queue_sp_obj*,struct ecore_queue_state_params*) ; 
 int stub2 (struct ecore_queue_sp_obj*,struct ecore_queue_state_params*) ; 
 int /*<<< orphan*/  stub3 (struct bxe_softc*,struct ecore_queue_sp_obj*,int) ; 
 int stub4 (struct bxe_softc*,struct ecore_queue_state_params*) ; 
 int stub5 (struct bxe_softc*,struct ecore_queue_sp_obj*,int) ; 

int ecore_queue_state_change(struct bxe_softc *sc,
			     struct ecore_queue_state_params *params)
{
	struct ecore_queue_sp_obj *o = params->q_obj;
	int rc, pending_bit;
	unsigned long *pending = &o->pending;

	/* Check that the requested transition is legal */
	rc = o->check_transition(sc, o, params);
	if (rc) {
		ECORE_ERR("check transition returned an error. rc %d\n", rc);
		return ECORE_INVAL;
	}

	/* Set "pending" bit */
	ECORE_MSG(sc, "pending bit was=%lx\n", o->pending);
	pending_bit = o->set_pending(o, params);
	ECORE_MSG(sc, "pending bit now=%lx\n", o->pending);

	/* Don't send a command if only driver cleanup was requested */
	if (ECORE_TEST_BIT(RAMROD_DRV_CLR_ONLY, &params->ramrod_flags))
		o->complete_cmd(sc, o, pending_bit);
	else {
		/* Send a ramrod */
		rc = o->send_cmd(sc, params);
		if (rc) {
			o->next_state = ECORE_Q_STATE_MAX;
			ECORE_CLEAR_BIT(pending_bit, pending);
			ECORE_SMP_MB_AFTER_CLEAR_BIT();
			return rc;
		}

		if (ECORE_TEST_BIT(RAMROD_COMP_WAIT, &params->ramrod_flags)) {
			rc = o->wait_comp(sc, o, pending_bit);
			if (rc)
				return rc;

			return ECORE_SUCCESS;
		}
	}

	return ECORE_RET_PENDING(pending_bit, pending);
}