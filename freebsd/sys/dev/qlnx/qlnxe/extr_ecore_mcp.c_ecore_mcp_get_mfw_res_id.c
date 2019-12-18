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
typedef  enum resource_id_enum { ____Placeholder_resource_id_enum } resource_id_enum ;
typedef  enum ecore_resources { ____Placeholder_ecore_resources } ecore_resources ;

/* Variables and functions */
#define  ECORE_BDQ 141 
#define  ECORE_CMDQS_CQS 140 
#define  ECORE_ILT 139 
#define  ECORE_L2_QUEUE 138 
#define  ECORE_LL2_QUEUE 137 
#define  ECORE_MAC 136 
#define  ECORE_PQ 135 
#define  ECORE_RDMA_CNQ_RAM 134 
#define  ECORE_RDMA_STATS_QUEUE 133 
#define  ECORE_RL 132 
#define  ECORE_RSS_ENG 131 
#define  ECORE_SB 130 
#define  ECORE_VLAN 129 
#define  ECORE_VPORT 128 
 int RESOURCE_BDQ_E ; 
 int RESOURCE_CQS_E ; 
 int RESOURCE_ILT_E ; 
 int RESOURCE_LL2_QUEUE_E ; 
 int RESOURCE_NUM_INVALID ; 
 int RESOURCE_NUM_L2_QUEUE_E ; 
 int RESOURCE_NUM_PQ_E ; 
 int RESOURCE_NUM_RL_E ; 
 int RESOURCE_NUM_RSS_ENGINES_E ; 
 int RESOURCE_NUM_SB_E ; 
 int RESOURCE_NUM_VPORT_E ; 
 int RESOURCE_RDMA_STATS_QUEUE_E ; 
 int RESOURCE_VFC_FILTER_E ; 

__attribute__((used)) static enum resource_id_enum
ecore_mcp_get_mfw_res_id(enum ecore_resources res_id)
{
	enum resource_id_enum mfw_res_id = RESOURCE_NUM_INVALID;

	switch (res_id) {
	case ECORE_SB:
		mfw_res_id = RESOURCE_NUM_SB_E;
		break;
	case ECORE_L2_QUEUE:
		mfw_res_id = RESOURCE_NUM_L2_QUEUE_E;
		break;
	case ECORE_VPORT:
		mfw_res_id = RESOURCE_NUM_VPORT_E;
		break;
	case ECORE_RSS_ENG:
		mfw_res_id = RESOURCE_NUM_RSS_ENGINES_E;
		break;
	case ECORE_PQ:
		mfw_res_id = RESOURCE_NUM_PQ_E;
		break;
	case ECORE_RL:
		mfw_res_id = RESOURCE_NUM_RL_E;
		break;
	case ECORE_MAC:
	case ECORE_VLAN:
		/* Each VFC resource can accommodate both a MAC and a VLAN */
		mfw_res_id = RESOURCE_VFC_FILTER_E;
		break;
	case ECORE_ILT:
		mfw_res_id = RESOURCE_ILT_E;
		break;
	case ECORE_LL2_QUEUE:
		mfw_res_id = RESOURCE_LL2_QUEUE_E;
		break;
	case ECORE_RDMA_CNQ_RAM:
	case ECORE_CMDQS_CQS:
		/* CNQ/CMDQS are the same resource */
		mfw_res_id = RESOURCE_CQS_E;
		break;
	case ECORE_RDMA_STATS_QUEUE:
		mfw_res_id = RESOURCE_RDMA_STATS_QUEUE_E;
		break;
	case ECORE_BDQ:
		mfw_res_id = RESOURCE_BDQ_E;
		break;
	default:
		break;
	}

	return mfw_res_id;
}