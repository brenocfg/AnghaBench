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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct virtchnl_vsi_queue_config_info {int num_queue_pairs; } ;
struct virtchnl_vlan_filter_list {int num_elements; } ;
struct virtchnl_vf_res_request {int dummy; } ;
struct virtchnl_version_info {int dummy; } ;
struct virtchnl_vector_map {int dummy; } ;
struct virtchnl_txq_info {int dummy; } ;
struct virtchnl_rxq_info {int dummy; } ;
struct virtchnl_rss_lut {int /*<<< orphan*/  lut_entries; } ;
struct virtchnl_rss_key {int /*<<< orphan*/  key_len; } ;
struct virtchnl_rss_hena {int dummy; } ;
struct virtchnl_queue_select {int dummy; } ;
struct virtchnl_queue_pair_info {int dummy; } ;
struct virtchnl_promisc_info {int dummy; } ;
struct virtchnl_iwarp_qvlist_info {int /*<<< orphan*/  num_vectors; } ;
struct virtchnl_iwarp_qv_info {int dummy; } ;
struct virtchnl_irq_map_info {int num_vectors; } ;
struct virtchnl_ether_addr_list {int num_elements; } ;
struct virtchnl_ether_addr {int dummy; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  VF_IS_V11 (struct virtchnl_version_info*) ; 
 int VIRTCHNL_ERR_PARAM ; 
#define  VIRTCHNL_OP_ADD_ETH_ADDR 154 
#define  VIRTCHNL_OP_ADD_VLAN 153 
#define  VIRTCHNL_OP_CONFIG_IRQ_MAP 152 
#define  VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP 151 
#define  VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE 150 
#define  VIRTCHNL_OP_CONFIG_RSS_KEY 149 
#define  VIRTCHNL_OP_CONFIG_RSS_LUT 148 
#define  VIRTCHNL_OP_CONFIG_RX_QUEUE 147 
#define  VIRTCHNL_OP_CONFIG_TX_QUEUE 146 
#define  VIRTCHNL_OP_CONFIG_VSI_QUEUES 145 
#define  VIRTCHNL_OP_DEL_ETH_ADDR 144 
#define  VIRTCHNL_OP_DEL_VLAN 143 
#define  VIRTCHNL_OP_DISABLE_QUEUES 142 
#define  VIRTCHNL_OP_DISABLE_VLAN_STRIPPING 141 
#define  VIRTCHNL_OP_ENABLE_QUEUES 140 
#define  VIRTCHNL_OP_ENABLE_VLAN_STRIPPING 139 
#define  VIRTCHNL_OP_EVENT 138 
#define  VIRTCHNL_OP_GET_RSS_HENA_CAPS 137 
#define  VIRTCHNL_OP_GET_STATS 136 
#define  VIRTCHNL_OP_GET_VF_RESOURCES 135 
#define  VIRTCHNL_OP_IWARP 134 
#define  VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP 133 
#define  VIRTCHNL_OP_REQUEST_QUEUES 132 
#define  VIRTCHNL_OP_RESET_VF 131 
#define  VIRTCHNL_OP_SET_RSS_HENA 130 
#define  VIRTCHNL_OP_UNKNOWN 129 
#define  VIRTCHNL_OP_VERSION 128 
 int VIRTCHNL_STATUS_ERR_OPCODE_MISMATCH ; 

__attribute__((used)) static inline int
virtchnl_vc_validate_vf_msg(struct virtchnl_version_info *ver, u32 v_opcode,
			    u8 *msg, u16 msglen)
{
	bool err_msg_format = FALSE;
	int valid_len = 0;

	/* Validate message length. */
	switch (v_opcode) {
	case VIRTCHNL_OP_VERSION:
		valid_len = sizeof(struct virtchnl_version_info);
		break;
	case VIRTCHNL_OP_RESET_VF:
		break;
	case VIRTCHNL_OP_GET_VF_RESOURCES:
		if (VF_IS_V11(ver))
			valid_len = sizeof(u32);
		break;
	case VIRTCHNL_OP_CONFIG_TX_QUEUE:
		valid_len = sizeof(struct virtchnl_txq_info);
		break;
	case VIRTCHNL_OP_CONFIG_RX_QUEUE:
		valid_len = sizeof(struct virtchnl_rxq_info);
		break;
	case VIRTCHNL_OP_CONFIG_VSI_QUEUES:
		valid_len = sizeof(struct virtchnl_vsi_queue_config_info);
		if (msglen >= valid_len) {
			struct virtchnl_vsi_queue_config_info *vqc =
			    (struct virtchnl_vsi_queue_config_info *)msg;
			valid_len += (vqc->num_queue_pairs *
				      sizeof(struct
					     virtchnl_queue_pair_info));
			if (vqc->num_queue_pairs == 0)
				err_msg_format = TRUE;
		}
		break;
	case VIRTCHNL_OP_CONFIG_IRQ_MAP:
		valid_len = sizeof(struct virtchnl_irq_map_info);
		if (msglen >= valid_len) {
			struct virtchnl_irq_map_info *vimi =
			    (struct virtchnl_irq_map_info *)msg;
			valid_len += (vimi->num_vectors *
				      sizeof(struct virtchnl_vector_map));
			if (vimi->num_vectors == 0)
				err_msg_format = TRUE;
		}
		break;
	case VIRTCHNL_OP_ENABLE_QUEUES:
	case VIRTCHNL_OP_DISABLE_QUEUES:
		valid_len = sizeof(struct virtchnl_queue_select);
		break;
	case VIRTCHNL_OP_ADD_ETH_ADDR:
	case VIRTCHNL_OP_DEL_ETH_ADDR:
		valid_len = sizeof(struct virtchnl_ether_addr_list);
		if (msglen >= valid_len) {
			struct virtchnl_ether_addr_list *veal =
			    (struct virtchnl_ether_addr_list *)msg;
			valid_len += veal->num_elements *
			    sizeof(struct virtchnl_ether_addr);
			if (veal->num_elements == 0)
				err_msg_format = TRUE;
		}
		break;
	case VIRTCHNL_OP_ADD_VLAN:
	case VIRTCHNL_OP_DEL_VLAN:
		valid_len = sizeof(struct virtchnl_vlan_filter_list);
		if (msglen >= valid_len) {
			struct virtchnl_vlan_filter_list *vfl =
			    (struct virtchnl_vlan_filter_list *)msg;
			valid_len += vfl->num_elements * sizeof(u16);
			if (vfl->num_elements == 0)
				err_msg_format = TRUE;
		}
		break;
	case VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE:
		valid_len = sizeof(struct virtchnl_promisc_info);
		break;
	case VIRTCHNL_OP_GET_STATS:
		valid_len = sizeof(struct virtchnl_queue_select);
		break;
	case VIRTCHNL_OP_IWARP:
		/* These messages are opaque to us and will be validated in
		 * the RDMA client code. We just need to check for nonzero
		 * length. The firmware will enforce max length restrictions.
		 */
		if (msglen)
			valid_len = msglen;
		else
			err_msg_format = TRUE;
		break;
	case VIRTCHNL_OP_RELEASE_IWARP_IRQ_MAP:
		break;
	case VIRTCHNL_OP_CONFIG_IWARP_IRQ_MAP:
		valid_len = sizeof(struct virtchnl_iwarp_qvlist_info);
		if (msglen >= valid_len) {
			struct virtchnl_iwarp_qvlist_info *qv =
				(struct virtchnl_iwarp_qvlist_info *)msg;
			if (qv->num_vectors == 0) {
				err_msg_format = TRUE;
				break;
			}
			valid_len += ((qv->num_vectors - 1) *
				sizeof(struct virtchnl_iwarp_qv_info));
		}
		break;
	case VIRTCHNL_OP_CONFIG_RSS_KEY:
		valid_len = sizeof(struct virtchnl_rss_key);
		if (msglen >= valid_len) {
			struct virtchnl_rss_key *vrk =
				(struct virtchnl_rss_key *)msg;
			valid_len += vrk->key_len - 1;
		}
		break;
	case VIRTCHNL_OP_CONFIG_RSS_LUT:
		valid_len = sizeof(struct virtchnl_rss_lut);
		if (msglen >= valid_len) {
			struct virtchnl_rss_lut *vrl =
				(struct virtchnl_rss_lut *)msg;
			valid_len += vrl->lut_entries - 1;
		}
		break;
	case VIRTCHNL_OP_GET_RSS_HENA_CAPS:
		break;
	case VIRTCHNL_OP_SET_RSS_HENA:
		valid_len = sizeof(struct virtchnl_rss_hena);
		break;
	case VIRTCHNL_OP_ENABLE_VLAN_STRIPPING:
	case VIRTCHNL_OP_DISABLE_VLAN_STRIPPING:
		break;
	case VIRTCHNL_OP_REQUEST_QUEUES:
		valid_len = sizeof(struct virtchnl_vf_res_request);
		break;
	/* These are always errors coming from the VF. */
	case VIRTCHNL_OP_EVENT:
	case VIRTCHNL_OP_UNKNOWN:
	default:
		return VIRTCHNL_ERR_PARAM;
	}
	/* few more checks */
	if (err_msg_format || valid_len != msglen)
		return VIRTCHNL_STATUS_ERR_OPCODE_MISMATCH;

	return 0;
}