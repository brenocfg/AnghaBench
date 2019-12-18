#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct ecore_vlan_mac_obj {TYPE_1__ exe_queue; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*) ; 
 int ECORE_PENDING ; 
 int /*<<< orphan*/  ECORE_SPIN_LOCK_BH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_SPIN_UNLOCK_BH (int /*<<< orphan*/ *) ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  __ecore_vlan_mac_h_pend (struct bxe_softc*,struct ecore_vlan_mac_obj*,unsigned long) ; 
 int __ecore_vlan_mac_h_write_trylock (struct bxe_softc*,struct ecore_vlan_mac_obj*) ; 
 int ecore_exe_queue_step (struct bxe_softc*,TYPE_1__*,unsigned long*) ; 

__attribute__((used)) static int __ecore_vlan_mac_execute_step(struct bxe_softc *sc,
					 struct ecore_vlan_mac_obj *o,
					 unsigned long *ramrod_flags)
{
	int rc = ECORE_SUCCESS;

	ECORE_SPIN_LOCK_BH(&o->exe_queue.lock);

	ECORE_MSG(sc, "vlan_mac_execute_step - trying to take writer lock\n");
	rc = __ecore_vlan_mac_h_write_trylock(sc, o);

	if (rc != ECORE_SUCCESS) {
		__ecore_vlan_mac_h_pend(sc, o, *ramrod_flags);

		/** Calling function should not diffrentiate between this case
		 *  and the case in which there is already a pending ramrod
		 */
		rc = ECORE_PENDING;
	} else {
		rc = ecore_exe_queue_step(sc, &o->exe_queue, ramrod_flags);
	}
	ECORE_SPIN_UNLOCK_BH(&o->exe_queue.lock);

	return rc;
}