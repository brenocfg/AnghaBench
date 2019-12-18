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
struct TYPE_10__ {int /*<<< orphan*/  imac_lsb; int /*<<< orphan*/  imac_mid; int /*<<< orphan*/  imac_msb; void* vni; int /*<<< orphan*/  header; } ;
union eth_classify_rule_cmd {TYPE_5__ imac_vni; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct eth_classify_rules_ramrod_data {int /*<<< orphan*/  header; union eth_classify_rule_cmd* rules; } ;
struct ecore_raw_obj {int /*<<< orphan*/  state; int /*<<< orphan*/  cid; scalar_t__ rdata; } ;
struct ecore_vlan_mac_obj {struct ecore_raw_obj raw; } ;
struct TYPE_6__ {int /*<<< orphan*/ * innermac; void* vni; } ;
struct TYPE_7__ {TYPE_1__ vxlan_fltr; } ;
struct TYPE_8__ {int cmd; struct ecore_vlan_mac_obj* target_obj; TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_3__ vlan_mac; } ;
struct ecore_exeq_elem {TYPE_4__ cmd_data; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_vlan_mac_cmd { ____Placeholder_ecore_vlan_mac_cmd } ecore_vlan_mac_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CLASSIFY_RULE_OPCODE_IMAC_VNI ; 
 int /*<<< orphan*/  ECORE_MEMSET (struct eth_classify_rules_ramrod_data*,int /*<<< orphan*/ ,int) ; 
 int ECORE_VLAN_MAC_ADD ; 
 int ECORE_VLAN_MAC_MOVE ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  ecore_set_fw_mac_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_vlan_mac_set_cmd_hdr_e2 (struct bxe_softc*,struct ecore_vlan_mac_obj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_vlan_mac_set_rdata_hdr_e2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ecore_set_one_vxlan_fltr_e2(struct bxe_softc *sc,
						struct ecore_vlan_mac_obj *o,
						struct ecore_exeq_elem *elem,
						int rule_idx, int cam_offset)
{
	struct ecore_raw_obj *raw = &o->raw;
	struct eth_classify_rules_ramrod_data *data =
		(struct eth_classify_rules_ramrod_data *)(raw->rdata);
	int rule_cnt = rule_idx + 1;
	union eth_classify_rule_cmd *rule_entry = &data->rules[rule_idx];
	enum ecore_vlan_mac_cmd cmd = elem->cmd_data.vlan_mac.cmd;
	bool add = (cmd == ECORE_VLAN_MAC_ADD) ? TRUE : FALSE;
	uint32_t vni = elem->cmd_data.vlan_mac.u.vxlan_fltr.vni;
	uint8_t *mac = elem->cmd_data.vlan_mac.u.vxlan_fltr.innermac;

	/* Reset the ramrod data buffer for the first rule */
	if (rule_idx == 0)
		ECORE_MEMSET(data, 0, sizeof(*data));

	/* Set a rule header */
	ecore_vlan_mac_set_cmd_hdr_e2(sc, o, add,
				      CLASSIFY_RULE_OPCODE_IMAC_VNI,
				      &rule_entry->imac_vni.header);

	/* Set VLAN and MAC themselves */
	rule_entry->imac_vni.vni = vni;
	ecore_set_fw_mac_addr(&rule_entry->imac_vni.imac_msb,
			      &rule_entry->imac_vni.imac_mid,
			      &rule_entry->imac_vni.imac_lsb, mac);

	/* MOVE: Add a rule that will add this MAC to the target Queue */
	if (cmd == ECORE_VLAN_MAC_MOVE) {
		rule_entry++;
		rule_cnt++;

		/* Setup ramrod data */
		ecore_vlan_mac_set_cmd_hdr_e2(sc,
					      elem->cmd_data.vlan_mac.target_obj,
					      TRUE, CLASSIFY_RULE_OPCODE_IMAC_VNI,
					      &rule_entry->imac_vni.header);

		/* Set a VLAN itself */
		rule_entry->imac_vni.vni = vni;
		ecore_set_fw_mac_addr(&rule_entry->imac_vni.imac_msb,
				      &rule_entry->imac_vni.imac_mid,
				      &rule_entry->imac_vni.imac_lsb, mac);
	}

	/* Set the ramrod data header */
	/* TODO: take this to the higher level in order to prevent multiple
	   * writing
	*/
	ecore_vlan_mac_set_rdata_hdr_e2(raw->cid, raw->state,
					&data->header, rule_cnt);
}