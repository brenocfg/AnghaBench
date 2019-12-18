#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {scalar_t__ virt; } ;
struct TYPE_23__ {scalar_t__ pci_func; TYPE_9__ payload; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* cb ) (scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ new_protocol; } ;
typedef  TYPE_1__ uint8_t ;
struct TYPE_24__ {scalar_t__ descriptor_type; int descriptor_length; } ;
typedef  TYPE_2__ sli4_resource_descriptor_v1_t ;
struct TYPE_25__ {int desc_count; scalar_t__ desc; } ;
typedef  TYPE_3__ sli4_res_common_get_profile_config_t ;
struct TYPE_26__ {int /*<<< orphan*/  desc; } ;
typedef  TYPE_4__ sli4_req_common_set_profile_config_t ;
struct TYPE_27__ {scalar_t__ pf_number; scalar_t__ pf_type; } ;
typedef  TYPE_5__ sli4_pcie_resource_descriptor_v1_t ;
struct TYPE_28__ {int descriptor_length; int iscsi_tgt; int iscsi_ini; int iscsi_dif; int fcoe_tgt; int fcoe_ini; int fcoe_dif; int /*<<< orphan*/  descriptor_type; } ;
typedef  TYPE_6__ sli4_isap_resouce_descriptor_v1_t ;
struct TYPE_29__ {int /*<<< orphan*/  os; int /*<<< orphan*/  sli; } ;
typedef  TYPE_7__ ocs_hw_t ;
typedef  TYPE_1__ ocs_hw_set_port_protocol_cb_arg_t ;
typedef  scalar_t__ ocs_hw_rtn_e ;
typedef  int ocs_hw_port_protocol_e ;
typedef  TYPE_9__ ocs_dma_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_CMD_NOWAIT ; 
#define  OCS_HW_PORT_PROTOCOL_FC 130 
#define  OCS_HW_PORT_PROTOCOL_FCOE 129 
#define  OCS_HW_PORT_PROTOCOL_ISCSI 128 
 scalar_t__ OCS_HW_RTN_NO_MEMORY ; 
 scalar_t__ OCS_HW_RTN_SUCCESS ; 
 int OCS_M_NOWAIT ; 
 int OCS_M_ZERO ; 
 int SLI4_BMBX_SIZE ; 
 scalar_t__ SLI4_PROTOCOL_DEFAULT ; 
 scalar_t__ SLI4_PROTOCOL_FC ; 
 scalar_t__ SLI4_PROTOCOL_FCOE ; 
 scalar_t__ SLI4_PROTOCOL_ISCSI ; 
 int /*<<< orphan*/  SLI4_RESOURCE_DESCRIPTOR_TYPE_ISAP ; 
 scalar_t__ SLI4_RESOURCE_DESCRIPTOR_TYPE_PCIE ; 
 scalar_t__ ocs_dma_alloc (int /*<<< orphan*/ ,TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ ocs_hw_command (TYPE_7__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_hw_set_port_protocol_cb2 ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* ocs_malloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ocs_memcpy (TYPE_1__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  sli_cmd_common_set_profile_config (int /*<<< orphan*/ *,TYPE_1__*,int,TYPE_9__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
ocs_hw_set_port_protocol_cb1(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void *arg)
{
	ocs_hw_set_port_protocol_cb_arg_t *cb_arg = arg;
	ocs_dma_t *payload = &(cb_arg->payload);
	sli4_res_common_get_profile_config_t* response = (sli4_res_common_get_profile_config_t*) payload->virt;
	int num_descriptors;
	sli4_resource_descriptor_v1_t *desc_p;
	sli4_pcie_resource_descriptor_v1_t *pcie_desc_p;
	int i;
	ocs_hw_set_port_protocol_cb_arg_t *new_cb_arg;
	ocs_hw_port_protocol_e new_protocol;
	uint8_t *dst;
	sli4_isap_resouce_descriptor_v1_t *isap_desc_p;
	uint8_t *mbxdata;
	int pci_descriptor_count;
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;
	int num_fcoe_ports = 0;
	int num_iscsi_ports = 0;

	new_protocol = (ocs_hw_port_protocol_e)cb_arg->new_protocol;

	num_descriptors = response->desc_count;

	/* Count PCI descriptors */
	pci_descriptor_count = 0;
	desc_p = (sli4_resource_descriptor_v1_t *)response->desc;
	for (i=0; i<num_descriptors; i++) {
		if (desc_p->descriptor_type == SLI4_RESOURCE_DESCRIPTOR_TYPE_PCIE) {
			++pci_descriptor_count;
		}
		desc_p = (sli4_resource_descriptor_v1_t *) ((uint8_t *)desc_p + desc_p->descriptor_length);
	}

	/* mbxdata holds the header of the command */
	mbxdata = ocs_malloc(hw->os, SLI4_BMBX_SIZE, OCS_M_ZERO | OCS_M_NOWAIT);
	if (mbxdata == NULL) {
		ocs_log_err(hw->os, "failed to malloc mbox\n");
		return OCS_HW_RTN_NO_MEMORY;
	}


	/* cb_arg holds the data that will be passed to the callback on completion */
	new_cb_arg = ocs_malloc(hw->os, sizeof(ocs_hw_set_port_protocol_cb_arg_t), OCS_M_NOWAIT);
	if (new_cb_arg == NULL) {
		ocs_log_err(hw->os, "failed to malloc cb_arg\n");
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		return OCS_HW_RTN_NO_MEMORY;
	}

	new_cb_arg->cb = cb_arg->cb;
	new_cb_arg->arg = cb_arg->arg;

	/* Allocate memory for the descriptors we're going to send.  This is
	 * one for each PCI descriptor plus one ISAP descriptor. */
	if (ocs_dma_alloc(hw->os, &new_cb_arg->payload, sizeof(sli4_req_common_set_profile_config_t) +
			  (pci_descriptor_count * sizeof(sli4_pcie_resource_descriptor_v1_t)) +
			  sizeof(sli4_isap_resouce_descriptor_v1_t), 4)) {
		ocs_log_err(hw->os, "Failed to allocate DMA buffer\n");
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		ocs_free(hw->os, new_cb_arg, sizeof(ocs_hw_set_port_protocol_cb_arg_t));
		return OCS_HW_RTN_NO_MEMORY;
	}

	sli_cmd_common_set_profile_config(&hw->sli, mbxdata, SLI4_BMBX_SIZE,
						   &new_cb_arg->payload,
						   0, pci_descriptor_count+1, 1);

	/* Point dst to the first descriptor entry in the SET_PROFILE_CONFIG command */
	dst = (uint8_t *)&(((sli4_req_common_set_profile_config_t *) new_cb_arg->payload.virt)->desc);

	/* Loop over all descriptors.  If the descriptor is a PCIe descriptor, copy it
	 * to the SET_PROFILE_CONFIG command to be written back.  If it's the descriptor
	 * that we're trying to change also set its pf_type.
	 */
	desc_p = (sli4_resource_descriptor_v1_t *)response->desc;
	for (i=0; i<num_descriptors; i++) {
		if (desc_p->descriptor_type == SLI4_RESOURCE_DESCRIPTOR_TYPE_PCIE) {
			pcie_desc_p = (sli4_pcie_resource_descriptor_v1_t*) desc_p;
			if (pcie_desc_p->pf_number == cb_arg->pci_func) {
				/* This is the PCIe descriptor for this OCS instance.
				 * Update it with the new pf_type */
				switch(new_protocol) {
				case OCS_HW_PORT_PROTOCOL_FC:
					pcie_desc_p->pf_type = SLI4_PROTOCOL_FC;
					break;
				case OCS_HW_PORT_PROTOCOL_FCOE:
					pcie_desc_p->pf_type = SLI4_PROTOCOL_FCOE;
					break;
				case OCS_HW_PORT_PROTOCOL_ISCSI:
					pcie_desc_p->pf_type = SLI4_PROTOCOL_ISCSI;
					break;
				default:
					pcie_desc_p->pf_type = SLI4_PROTOCOL_DEFAULT;
					break;
				}

			}

			if (pcie_desc_p->pf_type == SLI4_PROTOCOL_FCOE) {
				++num_fcoe_ports;
			}
			if (pcie_desc_p->pf_type == SLI4_PROTOCOL_ISCSI) {
				++num_iscsi_ports;
			}
			ocs_memcpy(dst, pcie_desc_p, sizeof(sli4_pcie_resource_descriptor_v1_t));
			dst += sizeof(sli4_pcie_resource_descriptor_v1_t);
		}

		desc_p = (sli4_resource_descriptor_v1_t *) ((uint8_t *)desc_p + desc_p->descriptor_length);
	}

	/* Create an ISAP resource descriptor */
	isap_desc_p = (sli4_isap_resouce_descriptor_v1_t*)dst;
	isap_desc_p->descriptor_type = SLI4_RESOURCE_DESCRIPTOR_TYPE_ISAP;
	isap_desc_p->descriptor_length = sizeof(sli4_isap_resouce_descriptor_v1_t);
	if (num_iscsi_ports > 0) {
		isap_desc_p->iscsi_tgt = 1;
		isap_desc_p->iscsi_ini = 1;
		isap_desc_p->iscsi_dif = 1;
	}
	if (num_fcoe_ports > 0) {
		isap_desc_p->fcoe_tgt = 1;
		isap_desc_p->fcoe_ini = 1;
		isap_desc_p->fcoe_dif = 1;
	}

	/* At this point we're done with the memory allocated by ocs_port_set_protocol */
	ocs_dma_free(hw->os, &cb_arg->payload);
	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);
	ocs_free(hw->os, cb_arg, sizeof(ocs_hw_set_port_protocol_cb_arg_t));


	/* Send a SET_PROFILE_CONFIG mailbox command with the new descriptors */
	rc = ocs_hw_command(hw, mbxdata, OCS_CMD_NOWAIT, ocs_hw_set_port_protocol_cb2, new_cb_arg);
	if (rc) {
		ocs_log_err(hw->os, "Error posting COMMON_SET_PROFILE_CONFIG\n");
		/* Call the upper level callback to report a failure */
		if (new_cb_arg->cb) {
			new_cb_arg->cb( rc, new_cb_arg->arg);
		}

		/* Free the memory allocated by this function */
		ocs_dma_free(hw->os, &new_cb_arg->payload);
		ocs_free(hw->os, mbxdata, SLI4_BMBX_SIZE);
		ocs_free(hw->os, new_cb_arg, sizeof(ocs_hw_set_port_protocol_cb_arg_t));
	}


	return rc;
}