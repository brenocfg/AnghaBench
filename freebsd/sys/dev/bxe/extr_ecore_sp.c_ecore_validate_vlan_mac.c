#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union ecore_qable_obj {int dummy; } ecore_qable_obj ;
struct TYPE_3__ {int cmd; } ;
struct TYPE_4__ {TYPE_1__ vlan_mac; } ;
struct ecore_exeq_elem {TYPE_2__ cmd_data; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ECORE_INVAL ; 
#define  ECORE_VLAN_MAC_ADD 130 
#define  ECORE_VLAN_MAC_DEL 129 
#define  ECORE_VLAN_MAC_MOVE 128 
 int ecore_validate_vlan_mac_add (struct bxe_softc*,union ecore_qable_obj*,struct ecore_exeq_elem*) ; 
 int ecore_validate_vlan_mac_del (struct bxe_softc*,union ecore_qable_obj*,struct ecore_exeq_elem*) ; 
 int ecore_validate_vlan_mac_move (struct bxe_softc*,union ecore_qable_obj*,struct ecore_exeq_elem*) ; 

__attribute__((used)) static int ecore_validate_vlan_mac(struct bxe_softc *sc,
				   union ecore_qable_obj *qo,
				   struct ecore_exeq_elem *elem)
{
	switch (elem->cmd_data.vlan_mac.cmd) {
	case ECORE_VLAN_MAC_ADD:
		return ecore_validate_vlan_mac_add(sc, qo, elem);
	case ECORE_VLAN_MAC_DEL:
		return ecore_validate_vlan_mac_del(sc, qo, elem);
	case ECORE_VLAN_MAC_MOVE:
		return ecore_validate_vlan_mac_move(sc, qo, elem);
	default:
		return ECORE_INVAL;
	}
}