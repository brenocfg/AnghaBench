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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  personality; } ;
struct ecore_hwfn {int num_funcs_on_engine; int port_id; int enabled_func_idx; TYPE_1__ hw_info; TYPE_2__* p_dev; } ;
typedef  enum ecore_resources { ____Placeholder_ecore_resources } ecore_resources ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_4__ {int num_ports_in_engine; } ;

/* Variables and functions */
#define  ECORE_BDQ 141 
#define  ECORE_CMDQS_CQS 140 
#define  ECORE_ILT 139 
 int ECORE_INVAL ; 
 int ECORE_IS_AH (TYPE_2__*) ; 
#define  ECORE_L2_QUEUE 138 
#define  ECORE_LL2_QUEUE 137 
#define  ECORE_MAC 136 
 int /*<<< orphan*/  ECORE_PCI_FCOE ; 
 int /*<<< orphan*/  ECORE_PCI_ISCSI ; 
#define  ECORE_PQ 135 
#define  ECORE_RDMA_CNQ_RAM 134 
#define  ECORE_RDMA_STATS_QUEUE 133 
#define  ECORE_RL 132 
#define  ECORE_RSS_ENG 131 
#define  ECORE_SB 130 
 int ECORE_SUCCESS ; 
#define  ECORE_VLAN 129 
#define  ECORE_VPORT 128 
 int ETH_NUM_MAC_FILTERS ; 
 int ETH_RSS_ENGINE_NUM_BB ; 
 int ETH_RSS_ENGINE_NUM_K2 ; 
 int MAX_NUM_L2_QUEUES_BB ; 
 int MAX_NUM_L2_QUEUES_K2 ; 
 int MAX_NUM_LL2_RX_QUEUES ; 
 int MAX_NUM_VPORTS_BB ; 
 int MAX_NUM_VPORTS_K2 ; 
 int MAX_QM_GLOBAL_RLS ; 
 int MAX_QM_TX_QUEUES_BB ; 
 int MAX_QM_TX_QUEUES_K2 ; 
 int NUM_OF_GLOBAL_QUEUES ; 
 int PXP_NUM_ILT_RECORDS_BB ; 
 int PXP_NUM_ILT_RECORDS_K2 ; 
 int RDMA_NUM_STATISTIC_COUNTERS_BB ; 
 int RDMA_NUM_STATISTIC_COUNTERS_K2 ; 

__attribute__((used)) static
enum _ecore_status_t ecore_hw_get_dflt_resc(struct ecore_hwfn *p_hwfn,
					    enum ecore_resources res_id,
					    u32 *p_resc_num, u32 *p_resc_start)
{
	u8 num_funcs = p_hwfn->num_funcs_on_engine;
	bool b_ah = ECORE_IS_AH(p_hwfn->p_dev);

	switch (res_id) {
	case ECORE_L2_QUEUE:
		*p_resc_num = (b_ah ? MAX_NUM_L2_QUEUES_K2 :
				      MAX_NUM_L2_QUEUES_BB) / num_funcs;
		break;
	case ECORE_VPORT:
		*p_resc_num = (b_ah ? MAX_NUM_VPORTS_K2 :
				      MAX_NUM_VPORTS_BB) / num_funcs;
		break;
	case ECORE_RSS_ENG:
		*p_resc_num = (b_ah ? ETH_RSS_ENGINE_NUM_K2 :
				      ETH_RSS_ENGINE_NUM_BB) / num_funcs;
		break;
	case ECORE_PQ:
		*p_resc_num = (b_ah ? MAX_QM_TX_QUEUES_K2 :
				      MAX_QM_TX_QUEUES_BB) / num_funcs;
		*p_resc_num &= ~0x7; /* The granularity of the PQs is 8 */
		break;
	case ECORE_RL:
		*p_resc_num = MAX_QM_GLOBAL_RLS / num_funcs;
		break;
	case ECORE_MAC:
	case ECORE_VLAN:
		/* Each VFC resource can accommodate both a MAC and a VLAN */
		*p_resc_num = ETH_NUM_MAC_FILTERS / num_funcs;
		break;
	case ECORE_ILT:
		*p_resc_num = (b_ah ? PXP_NUM_ILT_RECORDS_K2 :
				      PXP_NUM_ILT_RECORDS_BB) / num_funcs;
		break;
	case ECORE_LL2_QUEUE:
		*p_resc_num = MAX_NUM_LL2_RX_QUEUES / num_funcs;
		break;
	case ECORE_RDMA_CNQ_RAM:
	case ECORE_CMDQS_CQS:
		/* CNQ/CMDQS are the same resource */
		*p_resc_num = NUM_OF_GLOBAL_QUEUES / num_funcs;
		break;
	case ECORE_RDMA_STATS_QUEUE:
		*p_resc_num = (b_ah ? RDMA_NUM_STATISTIC_COUNTERS_K2 :
				      RDMA_NUM_STATISTIC_COUNTERS_BB) /
			      num_funcs;
		break;
	case ECORE_BDQ:
		if (p_hwfn->hw_info.personality != ECORE_PCI_ISCSI &&
		    p_hwfn->hw_info.personality != ECORE_PCI_FCOE)
			*p_resc_num = 0;
		else
			*p_resc_num = 1;
		break;
	case ECORE_SB:
		/* Since we want its value to reflect whether MFW supports
		 * the new scheme, have a default of 0.
		 */
		*p_resc_num = 0;
		break;
	default:
		return ECORE_INVAL;
	}

	switch (res_id) {
	case ECORE_BDQ:
		if (!*p_resc_num)
			*p_resc_start = 0;
		else if (p_hwfn->p_dev->num_ports_in_engine == 4)
			*p_resc_start = p_hwfn->port_id;
		else if (p_hwfn->hw_info.personality == ECORE_PCI_ISCSI)
			*p_resc_start = p_hwfn->port_id;
		else if (p_hwfn->hw_info.personality == ECORE_PCI_FCOE)
			*p_resc_start = p_hwfn->port_id + 2;
		break;
	default:
		*p_resc_start = *p_resc_num * p_hwfn->enabled_func_idx;
		break;
	}

	return ECORE_SUCCESS;
}