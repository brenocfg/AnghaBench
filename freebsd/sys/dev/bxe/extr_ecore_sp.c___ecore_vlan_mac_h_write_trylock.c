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
struct ecore_vlan_mac_obj {scalar_t__ head_reader; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ECORE_BUSY ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*) ; 
 int ECORE_SUCCESS ; 

__attribute__((used)) static int __ecore_vlan_mac_h_write_trylock(struct bxe_softc *sc,
					    struct ecore_vlan_mac_obj *o)
{
	if (o->head_reader) {
		ECORE_MSG(sc, "vlan_mac_lock writer - There are readers; Busy\n");
		return ECORE_BUSY;
	}

	ECORE_MSG(sc, "vlan_mac_lock writer - Taken\n");
	return ECORE_SUCCESS;
}