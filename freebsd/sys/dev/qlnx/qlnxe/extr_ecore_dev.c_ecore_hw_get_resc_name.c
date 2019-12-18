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

const char *ecore_hw_get_resc_name(enum ecore_resources res_id)
{
	switch (res_id) {
	case ECORE_L2_QUEUE:
		return "L2_QUEUE";
	case ECORE_VPORT:
		return "VPORT";
	case ECORE_RSS_ENG:
		return "RSS_ENG";
	case ECORE_PQ:
		return "PQ";
	case ECORE_RL:
		return "RL";
	case ECORE_MAC:
		return "MAC";
	case ECORE_VLAN:
		return "VLAN";
	case ECORE_RDMA_CNQ_RAM:
		return "RDMA_CNQ_RAM";
	case ECORE_ILT:
		return "ILT";
	case ECORE_LL2_QUEUE:
		return "LL2_QUEUE";
	case ECORE_CMDQS_CQS:
		return "CMDQS_CQS";
	case ECORE_RDMA_STATS_QUEUE:
		return "RDMA_STATS_QUEUE";
	case ECORE_BDQ:
		return "BDQ";
	case ECORE_SB:
		return "SB";
	default:
		return "UNKNOWN_RESOURCE";
	}
}