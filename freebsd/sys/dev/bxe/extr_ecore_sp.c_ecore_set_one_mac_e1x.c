#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mac_configuration_cmd {int dummy; } ;
struct ecore_raw_obj {int /*<<< orphan*/  state; scalar_t__ rdata; } ;
struct ecore_vlan_mac_obj {struct ecore_raw_obj raw; } ;
struct TYPE_5__ {int /*<<< orphan*/  mac; } ;
struct TYPE_6__ {TYPE_1__ mac; } ;
struct TYPE_7__ {scalar_t__ cmd; TYPE_2__ u; } ;
struct TYPE_8__ {TYPE_3__ vlan_mac; } ;
struct ecore_exeq_elem {TYPE_4__ cmd_data; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MEMSET (struct mac_configuration_cmd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ECORE_VLAN_MAC_ADD ; 
 int /*<<< orphan*/  ETH_VLAN_FILTER_ANY_VLAN ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  ecore_vlan_mac_set_rdata_e1x (struct bxe_softc*,struct ecore_vlan_mac_obj*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mac_configuration_cmd*) ; 

__attribute__((used)) static void ecore_set_one_mac_e1x(struct bxe_softc *sc,
				  struct ecore_vlan_mac_obj *o,
				  struct ecore_exeq_elem *elem, int rule_idx,
				  int cam_offset)
{
	struct ecore_raw_obj *raw = &o->raw;
	struct mac_configuration_cmd *config =
		(struct mac_configuration_cmd *)(raw->rdata);
	/* 57710 and 57711 do not support MOVE command,
	 * so it's either ADD or DEL
	 */
	bool add = (elem->cmd_data.vlan_mac.cmd == ECORE_VLAN_MAC_ADD) ?
		TRUE : FALSE;

	/* Reset the ramrod data buffer */
	ECORE_MEMSET(config, 0, sizeof(*config));

	ecore_vlan_mac_set_rdata_e1x(sc, o, raw->state,
				     cam_offset, add,
				     elem->cmd_data.vlan_mac.u.mac.mac, 0,
				     ETH_VLAN_FILTER_ANY_VLAN, config);
}