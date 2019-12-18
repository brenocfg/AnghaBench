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
struct ecore_vlan_mac_obj {unsigned long saved_ramrod_flags; int /*<<< orphan*/  exe_queue; int /*<<< orphan*/  head_exe_request; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ERR (char*,int) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,unsigned long) ; 
 int ECORE_PENDING ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int ecore_exe_queue_step (struct bxe_softc*,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  ecore_panic () ; 

__attribute__((used)) static void __ecore_vlan_mac_h_exec_pending(struct bxe_softc *sc,
					    struct ecore_vlan_mac_obj *o)
{
	int rc;
	unsigned long ramrod_flags = o->saved_ramrod_flags;

	ECORE_MSG(sc, "vlan_mac_lock execute pending command with ramrod flags %lu\n",
		  ramrod_flags);
	o->head_exe_request = FALSE;
	o->saved_ramrod_flags = 0;
	rc = ecore_exe_queue_step(sc, &o->exe_queue, &ramrod_flags);
	if ((rc != ECORE_SUCCESS) && (rc != ECORE_PENDING)) {
		ECORE_ERR("execution of pending commands failed with rc %d\n",
			  rc);
#ifdef ECORE_STOP_ON_ERROR
		ecore_panic();
#endif
	}
}