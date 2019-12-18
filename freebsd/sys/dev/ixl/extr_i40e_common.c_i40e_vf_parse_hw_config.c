#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtchnl_vsi_resource {scalar_t__ vsi_type; int /*<<< orphan*/  default_mac_addr; } ;
struct virtchnl_vf_resource {int num_vsis; int vf_cap_flags; int /*<<< orphan*/  max_vectors; int /*<<< orphan*/  num_queue_pairs; struct virtchnl_vsi_resource* vsi_res; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  perm_addr; } ;
struct TYPE_3__ {int num_vsis; int dcb; int iwarp; int /*<<< orphan*/  num_msix_vectors_vf; int /*<<< orphan*/  num_tx_qp; int /*<<< orphan*/  num_rx_qp; } ;
struct i40e_hw {TYPE_2__ mac; TYPE_1__ dev_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  I40E_NONDMA_TO_NONDMA ; 
 int VIRTCHNL_VF_OFFLOAD_IWARP ; 
 int VIRTCHNL_VF_OFFLOAD_L2 ; 
 scalar_t__ VIRTCHNL_VSI_SRIOV ; 
 int /*<<< orphan*/  i40e_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40e_vf_parse_hw_config(struct i40e_hw *hw,
			     struct virtchnl_vf_resource *msg)
{
	struct virtchnl_vsi_resource *vsi_res;
	int i;

	vsi_res = &msg->vsi_res[0];

	hw->dev_caps.num_vsis = msg->num_vsis;
	hw->dev_caps.num_rx_qp = msg->num_queue_pairs;
	hw->dev_caps.num_tx_qp = msg->num_queue_pairs;
	hw->dev_caps.num_msix_vectors_vf = msg->max_vectors;
	hw->dev_caps.dcb = msg->vf_cap_flags &
			   VIRTCHNL_VF_OFFLOAD_L2;
	hw->dev_caps.iwarp = (msg->vf_cap_flags &
			      VIRTCHNL_VF_OFFLOAD_IWARP) ? 1 : 0;
	for (i = 0; i < msg->num_vsis; i++) {
		if (vsi_res->vsi_type == VIRTCHNL_VSI_SRIOV) {
			i40e_memcpy(hw->mac.perm_addr,
				    vsi_res->default_mac_addr,
				    ETH_ALEN,
				    I40E_NONDMA_TO_NONDMA);
			i40e_memcpy(hw->mac.addr, vsi_res->default_mac_addr,
				    ETH_ALEN,
				    I40E_NONDMA_TO_NONDMA);
		}
		vsi_res++;
	}
}