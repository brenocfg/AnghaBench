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
typedef  int uint16_t ;
struct virtchnl_vlan_filter_list {int num_elements; scalar_t__ vsi_id; scalar_t__* vlan_id; } ;
struct TYPE_2__ {scalar_t__ vsi_num; } ;
struct ixl_vf {int vf_flags; int /*<<< orphan*/  mac; TYPE_1__ vsi; } ;
struct ixl_pf {int dummy; } ;

/* Variables and functions */
 scalar_t__ EVL_VLID_MASK ; 
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int VF_FLAG_VLAN_CAP ; 
 int /*<<< orphan*/  VIRTCHNL_OP_ADD_VLAN ; 
 int /*<<< orphan*/  VIRTCHNL_OP_DEL_VLAN ; 
 int /*<<< orphan*/  i40e_send_vf_nack (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_del_filter (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ixl_send_vf_ack (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_vf_del_vlan_msg(struct ixl_pf *pf, struct ixl_vf *vf, void *msg,
    uint16_t msg_size)
{
	struct virtchnl_vlan_filter_list *filter_list;
	int i;
	size_t expected_size;

	if (msg_size < sizeof(*filter_list)) {
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_DEL_VLAN,
		    I40E_ERR_PARAM);
		return;
	}

	filter_list = msg;
	expected_size = sizeof(*filter_list) +
	    filter_list->num_elements * sizeof(uint16_t);
	if (filter_list->num_elements == 0 ||
	    filter_list->vsi_id != vf->vsi.vsi_num ||
	    msg_size != expected_size) {
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_DEL_VLAN,
		    I40E_ERR_PARAM);
		return;
	}

	for (i = 0; i < filter_list->num_elements; i++) {
		if (filter_list->vlan_id[i] > EVL_VLID_MASK) {
			i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_ADD_VLAN,
			    I40E_ERR_PARAM);
			return;
		}
	}

	if (!(vf->vf_flags & VF_FLAG_VLAN_CAP)) {
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_ADD_VLAN,
		    I40E_ERR_PARAM);
		return;
	}

	for (i = 0; i < filter_list->num_elements; i++)
		ixl_del_filter(&vf->vsi, vf->mac, filter_list->vlan_id[i]);

	ixl_send_vf_ack(pf, vf, VIRTCHNL_OP_DEL_VLAN);
}