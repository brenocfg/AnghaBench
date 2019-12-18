#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct ixl_vf {int vf_flags; } ;
struct TYPE_4__ {size_t vf_base_id; } ;
struct TYPE_5__ {TYPE_1__ func_caps; } ;
struct ixl_pf {size_t num_vfs; struct ixl_vf* vfs; int /*<<< orphan*/  dev; TYPE_2__ hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  cookie_high; int /*<<< orphan*/  retval; } ;
struct i40e_arq_event_info {size_t msg_len; void* msg_buf; TYPE_3__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  I40E_VC_DEBUG (struct ixl_pf*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*,size_t,size_t) ; 
 int VF_FLAG_ENABLED ; 
#define  VIRTCHNL_OP_ADD_ETH_ADDR 145 
#define  VIRTCHNL_OP_ADD_VLAN 144 
#define  VIRTCHNL_OP_CONFIG_IRQ_MAP 143 
#define  VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE 142 
#define  VIRTCHNL_OP_CONFIG_RSS_KEY 141 
#define  VIRTCHNL_OP_CONFIG_RSS_LUT 140 
#define  VIRTCHNL_OP_CONFIG_RX_QUEUE 139 
#define  VIRTCHNL_OP_CONFIG_TX_QUEUE 138 
#define  VIRTCHNL_OP_CONFIG_VSI_QUEUES 137 
#define  VIRTCHNL_OP_DEL_ETH_ADDR 136 
#define  VIRTCHNL_OP_DEL_VLAN 135 
#define  VIRTCHNL_OP_DISABLE_QUEUES 134 
#define  VIRTCHNL_OP_ENABLE_QUEUES 133 
#define  VIRTCHNL_OP_GET_STATS 132 
#define  VIRTCHNL_OP_GET_VF_RESOURCES 131 
#define  VIRTCHNL_OP_RESET_VF 130 
#define  VIRTCHNL_OP_SET_RSS_HENA 129 
#define  VIRTCHNL_OP_VERSION 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  i40e_send_vf_nack (struct ixl_pf*,struct ixl_vf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_notify_vf_link_state (struct ixl_pf*,struct ixl_vf*) ; 
 int /*<<< orphan*/  ixl_vc_opcode_level (int) ; 
 int /*<<< orphan*/  ixl_vc_opcode_str (int) ; 
 int /*<<< orphan*/  ixl_vf_add_mac_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_add_vlan_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_config_irq_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_config_promisc_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_config_rss_key_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_config_rss_lut_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_config_vsi_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_del_mac_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_del_vlan_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_disable_queues_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_enable_queues_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_get_resources_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_get_stats_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_reset_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_set_rss_hena_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 int /*<<< orphan*/  ixl_vf_version_msg (struct ixl_pf*,struct ixl_vf*,void*,size_t) ; 
 size_t le16toh (int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 

void
ixl_handle_vf_msg(struct ixl_pf *pf, struct i40e_arq_event_info *event)
{
	struct ixl_vf *vf;
	void *msg;
	uint16_t vf_num, msg_size;
	uint32_t opcode;

	vf_num = le16toh(event->desc.retval) - pf->hw.func_caps.vf_base_id;
	opcode = le32toh(event->desc.cookie_high);

	if (vf_num >= pf->num_vfs) {
		device_printf(pf->dev, "Got msg from illegal VF: %d\n", vf_num);
		return;
	}

	vf = &pf->vfs[vf_num];
	msg = event->msg_buf;
	msg_size = event->msg_len;

	I40E_VC_DEBUG(pf, ixl_vc_opcode_level(opcode),
	    "Got msg %s(%d) from%sVF-%d of size %d\n",
	    ixl_vc_opcode_str(opcode), opcode,
	    (vf->vf_flags & VF_FLAG_ENABLED) ? " " : " disabled ",
	    vf_num, msg_size);

	/* This must be a stray msg from a previously destroyed VF. */
	if (!(vf->vf_flags & VF_FLAG_ENABLED))
		return;

	switch (opcode) {
	case VIRTCHNL_OP_VERSION:
		ixl_vf_version_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_RESET_VF:
		ixl_vf_reset_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_GET_VF_RESOURCES:
		ixl_vf_get_resources_msg(pf, vf, msg, msg_size);
		/* Notify VF of link state after it obtains queues, as this is
		 * the last thing it will do as part of initialization
		 */
		ixl_notify_vf_link_state(pf, vf);
		break;
	case VIRTCHNL_OP_CONFIG_VSI_QUEUES:
		ixl_vf_config_vsi_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_CONFIG_IRQ_MAP:
		ixl_vf_config_irq_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_ENABLE_QUEUES:
		ixl_vf_enable_queues_msg(pf, vf, msg, msg_size);
		/* Notify VF of link state after it obtains queues, as this is
		 * the last thing it will do as part of initialization
		 */
		ixl_notify_vf_link_state(pf, vf);
		break;
	case VIRTCHNL_OP_DISABLE_QUEUES:
		ixl_vf_disable_queues_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_ADD_ETH_ADDR:
		ixl_vf_add_mac_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_DEL_ETH_ADDR:
		ixl_vf_del_mac_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_ADD_VLAN:
		ixl_vf_add_vlan_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_DEL_VLAN:
		ixl_vf_del_vlan_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE:
		ixl_vf_config_promisc_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_GET_STATS:
		ixl_vf_get_stats_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_CONFIG_RSS_KEY:
		ixl_vf_config_rss_key_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_CONFIG_RSS_LUT:
		ixl_vf_config_rss_lut_msg(pf, vf, msg, msg_size);
		break;
	case VIRTCHNL_OP_SET_RSS_HENA:
		ixl_vf_set_rss_hena_msg(pf, vf, msg, msg_size);
		break;

	/* These two opcodes have been superseded by CONFIG_VSI_QUEUES. */
	case VIRTCHNL_OP_CONFIG_TX_QUEUE:
	case VIRTCHNL_OP_CONFIG_RX_QUEUE:
	default:
		i40e_send_vf_nack(pf, vf, opcode, I40E_ERR_NOT_IMPLEMENTED);
		break;
	}
}