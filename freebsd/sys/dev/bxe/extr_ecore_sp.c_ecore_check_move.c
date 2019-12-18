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
typedef  union ecore_classification_ramrod_data {int dummy; } ecore_classification_ramrod_data ;
struct ecore_vlan_mac_registry_elem {int dummy; } ;
struct ecore_vlan_mac_obj {int (* check_add ) (struct bxe_softc*,struct ecore_vlan_mac_obj*,union ecore_classification_ramrod_data*) ;struct ecore_vlan_mac_registry_elem* (* check_del ) (struct bxe_softc*,struct ecore_vlan_mac_obj*,union ecore_classification_ramrod_data*) ;} ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 struct ecore_vlan_mac_registry_elem* stub1 (struct bxe_softc*,struct ecore_vlan_mac_obj*,union ecore_classification_ramrod_data*) ; 
 int stub2 (struct bxe_softc*,struct ecore_vlan_mac_obj*,union ecore_classification_ramrod_data*) ; 

__attribute__((used)) static bool ecore_check_move(struct bxe_softc *sc,
			     struct ecore_vlan_mac_obj *src_o,
			     struct ecore_vlan_mac_obj *dst_o,
			     union ecore_classification_ramrod_data *data)
{
	struct ecore_vlan_mac_registry_elem *pos;
	int rc;

	/* Check if we can delete the requested configuration from the first
	 * object.
	 */
	pos = src_o->check_del(sc, src_o, data);

	/*  check if configuration can be added */
	rc = dst_o->check_add(sc, dst_o, data);

	/* If this classification can not be added (is already set)
	 * or can't be deleted - return an error.
	 */
	if (rc || !pos)
		return FALSE;

	return TRUE;
}