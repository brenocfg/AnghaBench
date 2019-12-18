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
struct ecore_vlan_mac_obj {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int FALSE ; 

__attribute__((used)) static bool ecore_check_move_always_err(
	struct bxe_softc *sc,
	struct ecore_vlan_mac_obj *src_o,
	struct ecore_vlan_mac_obj *dst_o,
	union ecore_classification_ramrod_data *data)
{
	return FALSE;
}