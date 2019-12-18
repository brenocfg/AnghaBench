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
typedef  int uint16_t ;

/* Variables and functions */
#define  VIRTCHNL_OP_ADD_ETH_ADDR 148 
#define  VIRTCHNL_OP_ADD_VLAN 147 
#define  VIRTCHNL_OP_CONFIG_IRQ_MAP 146 
#define  VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE 145 
#define  VIRTCHNL_OP_CONFIG_RSS_KEY 144 
#define  VIRTCHNL_OP_CONFIG_RSS_LUT 143 
#define  VIRTCHNL_OP_CONFIG_RX_QUEUE 142 
#define  VIRTCHNL_OP_CONFIG_TX_QUEUE 141 
#define  VIRTCHNL_OP_CONFIG_VSI_QUEUES 140 
#define  VIRTCHNL_OP_DEL_ETH_ADDR 139 
#define  VIRTCHNL_OP_DEL_VLAN 138 
#define  VIRTCHNL_OP_DISABLE_QUEUES 137 
#define  VIRTCHNL_OP_ENABLE_QUEUES 136 
#define  VIRTCHNL_OP_EVENT 135 
#define  VIRTCHNL_OP_GET_RSS_HENA_CAPS 134 
#define  VIRTCHNL_OP_GET_STATS 133 
#define  VIRTCHNL_OP_GET_VF_RESOURCES 132 
#define  VIRTCHNL_OP_RESET_VF 131 
#define  VIRTCHNL_OP_RSVD 130 
#define  VIRTCHNL_OP_SET_RSS_HENA 129 
#define  VIRTCHNL_OP_VERSION 128 

const char *
ixl_vc_opcode_str(uint16_t op)
{
	switch (op) {
	case VIRTCHNL_OP_VERSION:
		return ("VERSION");
	case VIRTCHNL_OP_RESET_VF:
		return ("RESET_VF");
	case VIRTCHNL_OP_GET_VF_RESOURCES:
		return ("GET_VF_RESOURCES");
	case VIRTCHNL_OP_CONFIG_TX_QUEUE:
		return ("CONFIG_TX_QUEUE");
	case VIRTCHNL_OP_CONFIG_RX_QUEUE:
		return ("CONFIG_RX_QUEUE");
	case VIRTCHNL_OP_CONFIG_VSI_QUEUES:
		return ("CONFIG_VSI_QUEUES");
	case VIRTCHNL_OP_CONFIG_IRQ_MAP:
		return ("CONFIG_IRQ_MAP");
	case VIRTCHNL_OP_ENABLE_QUEUES:
		return ("ENABLE_QUEUES");
	case VIRTCHNL_OP_DISABLE_QUEUES:
		return ("DISABLE_QUEUES");
	case VIRTCHNL_OP_ADD_ETH_ADDR:
		return ("ADD_ETH_ADDR");
	case VIRTCHNL_OP_DEL_ETH_ADDR:
		return ("DEL_ETH_ADDR");
	case VIRTCHNL_OP_ADD_VLAN:
		return ("ADD_VLAN");
	case VIRTCHNL_OP_DEL_VLAN:
		return ("DEL_VLAN");
	case VIRTCHNL_OP_CONFIG_PROMISCUOUS_MODE:
		return ("CONFIG_PROMISCUOUS_MODE");
	case VIRTCHNL_OP_GET_STATS:
		return ("GET_STATS");
	case VIRTCHNL_OP_RSVD:
		return ("RSVD");
	case VIRTCHNL_OP_EVENT:
		return ("EVENT");
	case VIRTCHNL_OP_CONFIG_RSS_KEY:
		return ("CONFIG_RSS_KEY");
	case VIRTCHNL_OP_CONFIG_RSS_LUT:
		return ("CONFIG_RSS_LUT");
	case VIRTCHNL_OP_GET_RSS_HENA_CAPS:
		return ("GET_RSS_HENA_CAPS");
	case VIRTCHNL_OP_SET_RSS_HENA:
		return ("SET_RSS_HENA");
	default:
		return ("UNKNOWN");
	}
}