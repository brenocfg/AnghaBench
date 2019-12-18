#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ virt; } ;
struct TYPE_12__ {scalar_t__ pci_func; TYPE_7__ payload; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ uint8_t ;
struct TYPE_13__ {scalar_t__ descriptor_type; int descriptor_length; } ;
typedef  TYPE_2__ sli4_resource_descriptor_v1_t ;
struct TYPE_14__ {int desc_count; scalar_t__ desc; } ;
typedef  TYPE_3__ sli4_res_common_get_profile_config_t ;
struct TYPE_15__ {scalar_t__ pf_number; int pf_type; } ;
typedef  TYPE_4__ sli4_pcie_resource_descriptor_v1_t ;
struct TYPE_16__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_5__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_port_protocol_e ;
typedef  TYPE_1__ ocs_hw_get_port_protocol_cb_arg_t ;
typedef  TYPE_7__ ocs_dma_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_PORT_PROTOCOL_FC ; 
 int /*<<< orphan*/  OCS_HW_PORT_PROTOCOL_FCOE ; 
 int /*<<< orphan*/  OCS_HW_PORT_PROTOCOL_ISCSI ; 
 int /*<<< orphan*/  OCS_HW_PORT_PROTOCOL_OTHER ; 
 int SLI4_BMBX_SIZE ; 
 scalar_t__ SLI4_RESOURCE_DESCRIPTOR_TYPE_PCIE ; 
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_get_port_protocol_cb(ocs_hw_t *hw, int32_t status,
			    uint8_t *mqe, void *arg)
{
	ocs_hw_get_port_protocol_cb_arg_t *cb_arg = arg;
	ocs_dma_t *payload = &(cb_arg->payload);
	sli4_res_common_get_profile_config_t* response = (sli4_res_common_get_profile_config_t*) payload->virt;
	ocs_hw_port_protocol_e port_protocol;
	int num_descriptors;
	sli4_resource_descriptor_v1_t *desc_p;
	sli4_pcie_resource_descriptor_v1_t *pcie_desc_p;
	int i;

	port_protocol = OCS_HW_PORT_PROTOCOL_OTHER;

	num_descriptors = response->desc_count;
	desc_p = (sli4_resource_descriptor_v1_t *)response->desc;
	for (i=0; i<num_descriptors; i++) {
		if (desc_p->descriptor_type == SLI4_RESOURCE_DESCRIPTOR_TYPE_PCIE) {
			pcie_desc_p = (sli4_pcie_resource_descriptor_v1_t*) desc_p;
			if (pcie_desc_p->pf_number == cb_arg->pci_func) {
				switch(pcie_desc_p->pf_type) {
				case 0x02:
					port_protocol = OCS_HW_PORT_PROTOCOL_ISCSI;
					break;
				case 0x04:
					port_protocol = OCS_HW_PORT_PROTOCOL_FCOE;
					break;
				case 0x10:
					port_protocol = OCS_HW_PORT_PROTOCOL_FC;
					break;
				default:
					port_protocol = OCS_HW_PORT_PROTOCOL_OTHER;
					break;
				}
			}
		}

		desc_p = (sli4_resource_descriptor_v1_t *) ((uint8_t *)desc_p + desc_p->descriptor_length);
	}

	if (cb_arg->cb) {
		cb_arg->cb(status, port_protocol, cb_arg->arg);

	}

	ocs_dma_free(hw->os, &cb_arg->payload);
	ocs_free(hw->os, cb_arg, sizeof(ocs_hw_get_port_protocol_cb_arg_t));
	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);

	return 0;
}