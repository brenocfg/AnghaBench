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
union ecore_mcast_config_data {int /*<<< orphan*/  mac; } ;
struct mac_configuration_cmd {TYPE_1__* config_table; } ;
struct ecore_raw_obj {int cl_id; int /*<<< orphan*/  func_id; scalar_t__ rdata; } ;
struct ecore_mcast_obj {struct ecore_raw_obj raw; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_mcast_cmd { ____Placeholder_ecore_mcast_cmd } ecore_mcast_cmd ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  clients_bit_vector; int /*<<< orphan*/  pf_id; scalar_t__ vlan_id; int /*<<< orphan*/  lsb_mac_addr; int /*<<< orphan*/  middle_mac_addr; int /*<<< orphan*/  msb_mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CPU_TO_LE32 (int) ; 
 int ECORE_MCAST_CMD_ADD ; 
 int ECORE_MCAST_CMD_RESTORE ; 
 int /*<<< orphan*/  ECORE_SET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_CONFIGURATION_ENTRY_ACTION_TYPE ; 
 int /*<<< orphan*/  T_ETH_MAC_COMMAND_SET ; 
 int /*<<< orphan*/  ecore_set_fw_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_mcast_set_one_rule_e1(struct bxe_softc *sc,
					struct ecore_mcast_obj *o, int idx,
					union ecore_mcast_config_data *cfg_data,
					enum ecore_mcast_cmd cmd)
{
	struct ecore_raw_obj *r = &o->raw;
	struct mac_configuration_cmd *data =
		(struct mac_configuration_cmd *)(r->rdata);

	/* copy mac */
	if ((cmd == ECORE_MCAST_CMD_ADD) || (cmd == ECORE_MCAST_CMD_RESTORE)) {
		ecore_set_fw_mac_addr(&data->config_table[idx].msb_mac_addr,
				      &data->config_table[idx].middle_mac_addr,
				      &data->config_table[idx].lsb_mac_addr,
				      cfg_data->mac);

		data->config_table[idx].vlan_id = 0;
		data->config_table[idx].pf_id = r->func_id;
		data->config_table[idx].clients_bit_vector =
			ECORE_CPU_TO_LE32(1 << r->cl_id);

		ECORE_SET_FLAG(data->config_table[idx].flags,
			       MAC_CONFIGURATION_ENTRY_ACTION_TYPE,
			       T_ETH_MAC_COMMAND_SET);
	}
}