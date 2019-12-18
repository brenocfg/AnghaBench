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
struct ecore_vlan_mac_obj {scalar_t__ head_exe_request; int /*<<< orphan*/  head_reader; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ERR (char*) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,...) ; 
 int /*<<< orphan*/  __ecore_vlan_mac_h_write_unlock (struct bxe_softc*,struct ecore_vlan_mac_obj*) ; 
 int /*<<< orphan*/  ecore_panic () ; 

__attribute__((used)) static void __ecore_vlan_mac_h_read_unlock(struct bxe_softc *sc,
					  struct ecore_vlan_mac_obj *o)
{
	if (!o->head_reader) {
		ECORE_ERR("Need to release vlan mac reader lock, but lock isn't taken\n");
#ifdef ECORE_STOP_ON_ERROR
		ecore_panic();
#endif
	} else {
		o->head_reader--;
		ECORE_MSG(sc, "vlan_mac_lock - decreased readers to %d\n",
			  o->head_reader);
	}

	/* It's possible a new pending execution was added, and that this reader
	 * was last - if so we need to execute the command.
	 */
	if (!o->head_reader && o->head_exe_request) {
		ECORE_MSG(sc, "vlan_mac_lock - reader release encountered a pending request\n");

		/* Writer release will do the trick */
		__ecore_vlan_mac_h_write_unlock(sc, o);
	}
}