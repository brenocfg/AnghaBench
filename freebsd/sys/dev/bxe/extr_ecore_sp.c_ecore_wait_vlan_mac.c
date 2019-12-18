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
struct ecore_raw_obj {int (* wait_comp ) (struct bxe_softc*,struct ecore_raw_obj*) ;} ;
struct ecore_exe_queue_obj {int dummy; } ;
struct ecore_vlan_mac_obj {struct ecore_raw_obj raw; struct ecore_exe_queue_obj exe_queue; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 int /*<<< orphan*/  ECORE_WAIT (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  ecore_exe_queue_empty (struct ecore_exe_queue_obj*) ; 
 int stub1 (struct bxe_softc*,struct ecore_raw_obj*) ; 

__attribute__((used)) static int ecore_wait_vlan_mac(struct bxe_softc *sc,
			       struct ecore_vlan_mac_obj *o)
{
	int cnt = 5000, rc;
	struct ecore_exe_queue_obj *exeq = &o->exe_queue;
	struct ecore_raw_obj *raw = &o->raw;

	while (cnt--) {
		/* Wait for the current command to complete */
		rc = raw->wait_comp(sc, raw);
		if (rc)
			return rc;

		/* Wait until there are no pending commands */
		if (!ecore_exe_queue_empty(exeq))
			ECORE_WAIT(sc, 1000);
		else
			return ECORE_SUCCESS;
	}

	return ECORE_TIMEOUT;
}