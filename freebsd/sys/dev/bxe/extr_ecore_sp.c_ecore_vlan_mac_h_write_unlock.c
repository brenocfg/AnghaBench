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
 int /*<<< orphan*/  ECORE_SPIN_LOCK_BH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECORE_SPIN_UNLOCK_BH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ecore_vlan_mac_h_write_unlock (struct bxe_softc*,struct ecore_vlan_mac_obj*) ; 

void ecore_vlan_mac_h_write_unlock(struct bxe_softc *sc,
				   struct ecore_vlan_mac_obj *o)
{
	ECORE_SPIN_LOCK_BH(&o->exe_queue.lock);
	__ecore_vlan_mac_h_write_unlock(sc, o);
	ECORE_SPIN_UNLOCK_BH(&o->exe_queue.lock);
}