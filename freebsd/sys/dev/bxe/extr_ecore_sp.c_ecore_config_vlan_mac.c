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
struct ecore_vlan_mac_ramrod_params {unsigned long ramrod_flags; struct ecore_vlan_mac_obj* vlan_mac_obj; } ;
struct ecore_raw_obj {int (* wait_comp ) (struct bxe_softc*,struct ecore_raw_obj*) ;int /*<<< orphan*/  (* clear_pending ) (struct ecore_raw_obj*) ;} ;
struct ecore_vlan_mac_obj {int /*<<< orphan*/  exe_queue; struct ecore_raw_obj raw; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*) ; 
 int ECORE_PENDING ; 
 int ECORE_SUCCESS ; 
 int ECORE_TEST_BIT (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_CONT ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  RAMROD_EXEC ; 
 int __ecore_vlan_mac_execute_step (struct bxe_softc*,struct ecore_vlan_mac_obj*,unsigned long*) ; 
 int /*<<< orphan*/  ecore_exe_queue_empty (int /*<<< orphan*/ *) ; 
 int ecore_exe_queue_length (int /*<<< orphan*/ *) ; 
 int ecore_vlan_mac_push_new_cmd (struct bxe_softc*,struct ecore_vlan_mac_ramrod_params*) ; 
 int /*<<< orphan*/  stub1 (struct ecore_raw_obj*) ; 
 int stub2 (struct bxe_softc*,struct ecore_raw_obj*) ; 

int ecore_config_vlan_mac(struct bxe_softc *sc,
			   struct ecore_vlan_mac_ramrod_params *p)
{
	int rc = ECORE_SUCCESS;
	struct ecore_vlan_mac_obj *o = p->vlan_mac_obj;
	unsigned long *ramrod_flags = &p->ramrod_flags;
	bool cont = ECORE_TEST_BIT(RAMROD_CONT, ramrod_flags);
	struct ecore_raw_obj *raw = &o->raw;

	/*
	 * Add new elements to the execution list for commands that require it.
	 */
	if (!cont) {
		rc = ecore_vlan_mac_push_new_cmd(sc, p);
		if (rc)
			return rc;
	}

	/* If nothing will be executed further in this iteration we want to
	 * return PENDING if there are pending commands
	 */
	if (!ecore_exe_queue_empty(&o->exe_queue))
		rc = ECORE_PENDING;

	if (ECORE_TEST_BIT(RAMROD_DRV_CLR_ONLY, ramrod_flags))  {
		ECORE_MSG(sc, "RAMROD_DRV_CLR_ONLY requested: clearing a pending bit.\n");
		raw->clear_pending(raw);
	}

	/* Execute commands if required */
	if (cont || ECORE_TEST_BIT(RAMROD_EXEC, ramrod_flags) ||
	    ECORE_TEST_BIT(RAMROD_COMP_WAIT, ramrod_flags)) {
		rc = __ecore_vlan_mac_execute_step(sc, p->vlan_mac_obj,
						   &p->ramrod_flags);
		if (rc < 0)
			return rc;
	}

	/* RAMROD_COMP_WAIT is a superset of RAMROD_EXEC. If it was set
	 * then user want to wait until the last command is done.
	 */
	if (ECORE_TEST_BIT(RAMROD_COMP_WAIT, &p->ramrod_flags)) {
		/* Wait maximum for the current exe_queue length iterations plus
		 * one (for the current pending command).
		 */
		int max_iterations = ecore_exe_queue_length(&o->exe_queue) + 1;

		while (!ecore_exe_queue_empty(&o->exe_queue) &&
		       max_iterations--) {

			/* Wait for the current command to complete */
			rc = raw->wait_comp(sc, raw);
			if (rc)
				return rc;

			/* Make a next step */
			rc = __ecore_vlan_mac_execute_step(sc,
							   p->vlan_mac_obj,
							   &p->ramrod_flags);
			if (rc < 0)
				return rc;
		}

		return ECORE_SUCCESS;
	}

	return rc;
}