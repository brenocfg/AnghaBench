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
struct ecore_vlan_mac_obj {scalar_t__ head_exe_request; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  __ecore_vlan_mac_h_exec_pending (struct bxe_softc*,struct ecore_vlan_mac_obj*) ; 

__attribute__((used)) static void __ecore_vlan_mac_h_write_unlock(struct bxe_softc *sc,
					    struct ecore_vlan_mac_obj *o)
{
	/* It's possible a new pending execution was added since this writer
	 * executed. If so, execute again. [Ad infinitum]
	 */
	while(o->head_exe_request) {
		ECORE_MSG(sc, "vlan_mac_lock - writer release encountered a pending request\n");
		__ecore_vlan_mac_h_exec_pending(sc, o);
	}
}