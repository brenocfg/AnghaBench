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
typedef  union ecore_qable_obj {int dummy; } ecore_qable_obj ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ecore_vlan_mac_obj {int /*<<< orphan*/  exe_queue; int /*<<< orphan*/  ramrod_cmd; int /*<<< orphan*/  check_move; int /*<<< orphan*/  check_add; int /*<<< orphan*/  check_del; int /*<<< orphan*/  set_one_rule; int /*<<< orphan*/  put_cam_offset; int /*<<< orphan*/  get_cam_offset; int /*<<< orphan*/  put_credit; int /*<<< orphan*/  get_credit; } ;
struct ecore_credit_pool_obj {int dummy; } ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  ecore_obj_type ;
typedef  int /*<<< orphan*/  ecore_dma_addr_t ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  CLASSIFY_RULES_COUNT ; 
 int /*<<< orphan*/  ECORE_BUG () ; 
 int /*<<< orphan*/  ECORE_ERR (char*) ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES ; 
 int /*<<< orphan*/  ecore_check_move ; 
 int /*<<< orphan*/  ecore_check_vxlan_fltr_add ; 
 int /*<<< orphan*/  ecore_check_vxlan_fltr_del ; 
 int /*<<< orphan*/  ecore_exe_queue_init (struct bxe_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,union ecore_qable_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_execute_vlan_mac ; 
 int /*<<< orphan*/  ecore_exeq_get_vxlan_fltr ; 
 int /*<<< orphan*/  ecore_get_cam_offset_mac ; 
 int /*<<< orphan*/  ecore_get_credit_vlan_mac ; 
 int /*<<< orphan*/  ecore_init_vlan_mac_common (struct ecore_vlan_mac_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,unsigned long*,int /*<<< orphan*/ ,struct ecore_credit_pool_obj*,struct ecore_credit_pool_obj*) ; 
 int /*<<< orphan*/  ecore_optimize_vlan_mac ; 
 int /*<<< orphan*/  ecore_put_cam_offset_mac ; 
 int /*<<< orphan*/  ecore_put_credit_vlan_mac ; 
 int /*<<< orphan*/  ecore_remove_vlan_mac ; 
 int /*<<< orphan*/  ecore_set_one_vxlan_fltr_e2 ; 
 int /*<<< orphan*/  ecore_validate_vlan_mac ; 

void ecore_init_vxlan_fltr_obj(struct bxe_softc *sc,
				struct ecore_vlan_mac_obj *vlan_mac_obj,
				uint8_t cl_id, uint32_t cid, uint8_t func_id, void *rdata,
				ecore_dma_addr_t rdata_mapping, int state,
				unsigned long *pstate, ecore_obj_type type,
				struct ecore_credit_pool_obj *macs_pool,
				struct ecore_credit_pool_obj *vlans_pool)
{
	union ecore_qable_obj *qable_obj =
		(union ecore_qable_obj *)vlan_mac_obj;

	ecore_init_vlan_mac_common(vlan_mac_obj, cl_id, cid, func_id,
				   rdata, rdata_mapping, state, pstate,
				   type, macs_pool, vlans_pool);

	/* CAM pool handling */
	vlan_mac_obj->get_credit = ecore_get_credit_vlan_mac;
	vlan_mac_obj->put_credit = ecore_put_credit_vlan_mac;
	/* CAM offset is relevant for 57710 and 57711 chips only which have a
	 * single CAM for both MACs and VLAN-MAC pairs. So the offset
	 * will be taken from MACs' pool object only.
	 */
	vlan_mac_obj->get_cam_offset = ecore_get_cam_offset_mac;
	vlan_mac_obj->put_cam_offset = ecore_put_cam_offset_mac;

	if (CHIP_IS_E1x(sc)) {
		ECORE_ERR("Do not support chips others than E2/E3\n");
		ECORE_BUG();
	} else {
		vlan_mac_obj->set_one_rule      = ecore_set_one_vxlan_fltr_e2;
		vlan_mac_obj->check_del         = ecore_check_vxlan_fltr_del;
		vlan_mac_obj->check_add         = ecore_check_vxlan_fltr_add;
		vlan_mac_obj->check_move        = ecore_check_move;
		vlan_mac_obj->ramrod_cmd        =
			RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES;

		/* Exe Queue */
		ecore_exe_queue_init(sc,
				     &vlan_mac_obj->exe_queue,
				     CLASSIFY_RULES_COUNT,
				     qable_obj, ecore_validate_vlan_mac,
				     ecore_remove_vlan_mac,
				     ecore_optimize_vlan_mac,
				     ecore_execute_vlan_mac,
				     ecore_exeq_get_vxlan_fltr);
	}
}