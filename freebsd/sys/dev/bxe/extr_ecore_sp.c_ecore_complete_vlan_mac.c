#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ error; } ;
union event_ring_elem {TYPE_1__ message; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct ecore_raw_obj {int /*<<< orphan*/  (* clear_pending ) (struct ecore_raw_obj*) ;} ;
struct ecore_vlan_mac_obj {TYPE_2__ exe_queue; struct ecore_raw_obj raw; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ECORE_INVAL ; 
 int ECORE_PENDING ; 
 int /*<<< orphan*/  ECORE_SPIN_LOCK_BH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_SPIN_UNLOCK_BH (int /*<<< orphan*/ *) ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_TEST_BIT (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  RAMROD_CONT ; 
 int /*<<< orphan*/  __ecore_exe_queue_reset_pending (struct bxe_softc*,TYPE_2__*) ; 
 int __ecore_vlan_mac_execute_step (struct bxe_softc*,struct ecore_vlan_mac_obj*,unsigned long*) ; 
 int /*<<< orphan*/  ecore_exe_queue_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct ecore_raw_obj*) ; 

__attribute__((used)) static int ecore_complete_vlan_mac(struct bxe_softc *sc,
				   struct ecore_vlan_mac_obj *o,
				   union event_ring_elem *cqe,
				   unsigned long *ramrod_flags)
{
	struct ecore_raw_obj *r = &o->raw;
	int rc;

	/* Clearing the pending list & raw state should be made
	 * atomically (as execution flow assumes they represent the same)
	 */
	ECORE_SPIN_LOCK_BH(&o->exe_queue.lock);

	/* Reset pending list */
	__ecore_exe_queue_reset_pending(sc, &o->exe_queue);

	/* Clear pending */
	r->clear_pending(r);

	ECORE_SPIN_UNLOCK_BH(&o->exe_queue.lock);

	/* If ramrod failed this is most likely a SW bug */
	if (cqe->message.error)
		return ECORE_INVAL;

	/* Run the next bulk of pending commands if requested */
	if (ECORE_TEST_BIT(RAMROD_CONT, ramrod_flags)) {
		rc = __ecore_vlan_mac_execute_step(sc, o, ramrod_flags);
		if (rc < 0)
			return rc;
	}

	/* If there is more work to do return PENDING */
	if (!ecore_exe_queue_empty(&o->exe_queue))
		return ECORE_PENDING;

	return ECORE_SUCCESS;
}