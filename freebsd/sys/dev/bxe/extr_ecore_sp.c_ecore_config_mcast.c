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
struct ecore_raw_obj {int /*<<< orphan*/  (* clear_pending ) (struct ecore_raw_obj*) ;int /*<<< orphan*/  (* set_pending ) (struct ecore_raw_obj*) ;scalar_t__ (* check_pending ) (struct ecore_raw_obj*) ;} ;
struct ecore_mcast_ramrod_params {int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/  mcast_list_len; struct ecore_mcast_obj* mcast_obj; } ;
struct ecore_mcast_obj {int (* get_registry_size ) (struct ecore_mcast_obj*) ;int (* validate ) (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int) ;scalar_t__ total_pending_num; scalar_t__ max_cmd_len; int (* enqueue_cmd ) (struct bxe_softc*,struct ecore_mcast_obj*,struct ecore_mcast_ramrod_params*,int) ;int (* config_mcast ) (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int) ;int (* wait_comp ) (struct bxe_softc*,struct ecore_mcast_obj*) ;int /*<<< orphan*/  (* revert ) (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int) ;int /*<<< orphan*/  (* check_sched ) (struct ecore_mcast_obj*) ;struct ecore_raw_obj raw; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_mcast_cmd { ____Placeholder_ecore_mcast_cmd } ecore_mcast_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int stub1 (struct ecore_mcast_obj*) ; 
 int /*<<< orphan*/  stub10 (struct ecore_raw_obj*) ; 
 int /*<<< orphan*/  stub11 (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int) ; 
 int stub2 (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int) ; 
 int /*<<< orphan*/  stub3 (struct ecore_mcast_obj*) ; 
 scalar_t__ stub4 (struct ecore_raw_obj*) ; 
 int stub5 (struct bxe_softc*,struct ecore_mcast_obj*,struct ecore_mcast_ramrod_params*,int) ; 
 scalar_t__ stub6 (struct ecore_raw_obj*) ; 
 int /*<<< orphan*/  stub7 (struct ecore_raw_obj*) ; 
 int stub8 (struct bxe_softc*,struct ecore_mcast_ramrod_params*,int) ; 
 int stub9 (struct bxe_softc*,struct ecore_mcast_obj*) ; 

int ecore_config_mcast(struct bxe_softc *sc,
		       struct ecore_mcast_ramrod_params *p,
		       enum ecore_mcast_cmd cmd)
{
	struct ecore_mcast_obj *o = p->mcast_obj;
	struct ecore_raw_obj *r = &o->raw;
	int rc = 0, old_reg_size;

	/* This is needed to recover number of currently configured mcast macs
	 * in case of failure.
	 */
	old_reg_size = o->get_registry_size(o);

	/* Do some calculations and checks */
	rc = o->validate(sc, p, cmd);
	if (rc)
		return rc;

	/* Return if there is no work to do */
	if ((!p->mcast_list_len) && (!o->check_sched(o)))
		return ECORE_SUCCESS;

	ECORE_MSG(sc, "o->total_pending_num=%d p->mcast_list_len=%d o->max_cmd_len=%d\n",
		  o->total_pending_num, p->mcast_list_len, o->max_cmd_len);

	/* Enqueue the current command to the pending list if we can't complete
	 * it in the current iteration
	 */
	if (r->check_pending(r) ||
	    ((o->max_cmd_len > 0) && (o->total_pending_num > o->max_cmd_len))) {
		rc = o->enqueue_cmd(sc, p->mcast_obj, p, cmd);
		if (rc < 0)
			goto error_exit1;

		/* As long as the current command is in a command list we
		 * don't need to handle it separately.
		 */
		p->mcast_list_len = 0;
	}

	if (!r->check_pending(r)) {

		/* Set 'pending' state */
		r->set_pending(r);

		/* Configure the new classification in the chip */
		rc = o->config_mcast(sc, p, cmd);
		if (rc < 0)
			goto error_exit2;

		/* Wait for a ramrod completion if was requested */
		if (ECORE_TEST_BIT(RAMROD_COMP_WAIT, &p->ramrod_flags))
			rc = o->wait_comp(sc, o);
	}

	return rc;

error_exit2:
	r->clear_pending(r);

error_exit1:
	o->revert(sc, p, old_reg_size);

	return rc;
}