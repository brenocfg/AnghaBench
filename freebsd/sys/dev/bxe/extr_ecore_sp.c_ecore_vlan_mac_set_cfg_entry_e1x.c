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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mac_configuration_entry {int /*<<< orphan*/  flags; int /*<<< orphan*/  lsb_mac_addr; int /*<<< orphan*/  middle_mac_addr; int /*<<< orphan*/  msb_mac_addr; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  pf_id; int /*<<< orphan*/  clients_bit_vector; } ;
struct ecore_raw_obj {int cl_id; int /*<<< orphan*/  func_id; } ;
struct ecore_vlan_mac_obj {struct ecore_raw_obj raw; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_CPU_TO_LE32 (int) ; 
 int /*<<< orphan*/  ECORE_SET_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAC_CONFIGURATION_ENTRY_ACTION_TYPE ; 
 int /*<<< orphan*/  MAC_CONFIGURATION_ENTRY_VLAN_FILTERING_MODE ; 
 int T_ETH_MAC_COMMAND_INVALIDATE ; 
 int T_ETH_MAC_COMMAND_SET ; 
 int /*<<< orphan*/  ecore_set_fw_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ecore_vlan_mac_set_cfg_entry_e1x(struct bxe_softc *sc,
	struct ecore_vlan_mac_obj *o, bool add, int opcode, uint8_t *mac,
	uint16_t vlan_id, struct mac_configuration_entry *cfg_entry)
{
	struct ecore_raw_obj *r = &o->raw;
	uint32_t cl_bit_vec = (1 << r->cl_id);

	cfg_entry->clients_bit_vector = ECORE_CPU_TO_LE32(cl_bit_vec);
	cfg_entry->pf_id = r->func_id;
	cfg_entry->vlan_id = ECORE_CPU_TO_LE16(vlan_id);

	if (add) {
		ECORE_SET_FLAG(cfg_entry->flags,
			       MAC_CONFIGURATION_ENTRY_ACTION_TYPE,
			       T_ETH_MAC_COMMAND_SET);
		ECORE_SET_FLAG(cfg_entry->flags,
			       MAC_CONFIGURATION_ENTRY_VLAN_FILTERING_MODE,
			       opcode);

		/* Set a MAC in a ramrod data */
		ecore_set_fw_mac_addr(&cfg_entry->msb_mac_addr,
				      &cfg_entry->middle_mac_addr,
				      &cfg_entry->lsb_mac_addr, mac);
	} else
		ECORE_SET_FLAG(cfg_entry->flags,
			       MAC_CONFIGURATION_ENTRY_ACTION_TYPE,
			       T_ETH_MAC_COMMAND_INVALIDATE);
}