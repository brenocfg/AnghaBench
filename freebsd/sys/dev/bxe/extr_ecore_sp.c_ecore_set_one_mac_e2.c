#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* inner_mac; int /*<<< orphan*/  mac_lsb; int /*<<< orphan*/  mac_mid; int /*<<< orphan*/  mac_msb; int /*<<< orphan*/  header; } ;
union eth_classify_rule_cmd {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct eth_classify_rules_ramrod_data {int /*<<< orphan*/  header; union eth_classify_rule_cmd* rules; } ;
struct ecore_raw_obj {int /*<<< orphan*/  state; int /*<<< orphan*/  cid; int /*<<< orphan*/  cl_id; scalar_t__ rdata; } ;
struct ecore_vlan_mac_obj {struct ecore_raw_obj raw; } ;
struct TYPE_7__ {int /*<<< orphan*/  is_inner_mac; int /*<<< orphan*/ * mac; } ;
struct TYPE_8__ {TYPE_2__ mac; } ;
struct TYPE_9__ {int cmd; unsigned long vlan_mac_flags; TYPE_3__ u; struct ecore_vlan_mac_obj* target_obj; } ;
struct TYPE_10__ {TYPE_4__ vlan_mac; } ;
struct ecore_exeq_elem {TYPE_5__ cmd_data; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSIFY_RULE_OPCODE_MAC ; 
 void* ECORE_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_ETH_MAC ; 
 int /*<<< orphan*/  ECORE_ISCSI_ETH_MAC ; 
 int /*<<< orphan*/  ECORE_LLH_CAM_ETH_LINE ; 
 int /*<<< orphan*/  ECORE_LLH_CAM_ISCSI_ETH_LINE ; 
 int /*<<< orphan*/  ECORE_MEMSET (struct eth_classify_rules_ramrod_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ECORE_TEST_BIT (int /*<<< orphan*/ ,unsigned long*) ; 
 int ECORE_VLAN_MAC_ADD ; 
 int ECORE_VLAN_MAC_MOVE ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  ecore_set_fw_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_set_mac_in_nig (struct bxe_softc*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_vlan_mac_set_cmd_hdr_e2 (struct bxe_softc*,struct ecore_vlan_mac_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_vlan_mac_set_rdata_hdr_e2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ecore_set_one_mac_e2(struct bxe_softc *sc,
				 struct ecore_vlan_mac_obj *o,
				 struct ecore_exeq_elem *elem, int rule_idx,
				 int cam_offset)
{
	struct ecore_raw_obj *raw = &o->raw;
	struct eth_classify_rules_ramrod_data *data =
		(struct eth_classify_rules_ramrod_data *)(raw->rdata);
	int rule_cnt = rule_idx + 1, cmd = elem->cmd_data.vlan_mac.cmd;
	union eth_classify_rule_cmd *rule_entry = &data->rules[rule_idx];
	bool add = (cmd == ECORE_VLAN_MAC_ADD) ? TRUE : FALSE;
	unsigned long *vlan_mac_flags = &elem->cmd_data.vlan_mac.vlan_mac_flags;
	uint8_t *mac = elem->cmd_data.vlan_mac.u.mac.mac;

	/* Set LLH CAM entry: currently only iSCSI and ETH macs are
	 * relevant. In addition, current implementation is tuned for a
	 * single ETH MAC.
	 *
	 * When multiple unicast ETH MACs PF configuration in switch
	 * independent mode is required (NetQ, multiple netdev MACs,
	 * etc.), consider better utilisation of 8 per function MAC
	 * entries in the LLH register. There is also
	 * NIG_REG_P[01]_LLH_FUNC_MEM2 registers that complete the
	 * total number of CAM entries to 16.
	 *
	 * Currently we won't configure NIG for MACs other than a primary ETH
	 * MAC and iSCSI L2 MAC.
	 *
	 * If this MAC is moving from one Queue to another, no need to change
	 * NIG configuration.
	 */
	if (cmd != ECORE_VLAN_MAC_MOVE) {
		if (ECORE_TEST_BIT(ECORE_ISCSI_ETH_MAC, vlan_mac_flags))
			ecore_set_mac_in_nig(sc, add, mac,
					     ECORE_LLH_CAM_ISCSI_ETH_LINE);
		else if (ECORE_TEST_BIT(ECORE_ETH_MAC, vlan_mac_flags))
			ecore_set_mac_in_nig(sc, add, mac,
					     ECORE_LLH_CAM_ETH_LINE);
	}

	/* Reset the ramrod data buffer for the first rule */
	if (rule_idx == 0)
		ECORE_MEMSET(data, 0, sizeof(*data));

	/* Setup a command header */
	ecore_vlan_mac_set_cmd_hdr_e2(sc, o, add, CLASSIFY_RULE_OPCODE_MAC,
				      &rule_entry->mac.header);

	ECORE_MSG(sc, "About to %s MAC %02x:%02x:%02x:%02x:%02x:%02x for Queue %d\n",
		  (add ? "add" : "delete"), mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], raw->cl_id);

	/* Set a MAC itself */
	ecore_set_fw_mac_addr(&rule_entry->mac.mac_msb,
			      &rule_entry->mac.mac_mid,
			      &rule_entry->mac.mac_lsb, mac);
	rule_entry->mac.inner_mac =
		ECORE_CPU_TO_LE16(elem->cmd_data.vlan_mac.u.mac.is_inner_mac);

	/* MOVE: Add a rule that will add this MAC to the target Queue */
	if (cmd == ECORE_VLAN_MAC_MOVE) {
		rule_entry++;
		rule_cnt++;

		/* Setup ramrod data */
		ecore_vlan_mac_set_cmd_hdr_e2(sc,
					elem->cmd_data.vlan_mac.target_obj,
					      TRUE, CLASSIFY_RULE_OPCODE_MAC,
					      &rule_entry->mac.header);

		/* Set a MAC itself */
		ecore_set_fw_mac_addr(&rule_entry->mac.mac_msb,
				      &rule_entry->mac.mac_mid,
				      &rule_entry->mac.mac_lsb, mac);
		rule_entry->mac.inner_mac =
			ECORE_CPU_TO_LE16(elem->cmd_data.vlan_mac.
				       u.mac.is_inner_mac);
	}

	/* Set the ramrod data header */
	/* TODO: take this to the higher level in order to prevent multiple
		 writing */
	ecore_vlan_mac_set_rdata_hdr_e2(raw->cid, raw->state, &data->header,
					rule_cnt);
}