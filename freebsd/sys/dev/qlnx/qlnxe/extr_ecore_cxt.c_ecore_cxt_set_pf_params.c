#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ecore_iscsi_pf_params {int num_cons; int /*<<< orphan*/  num_tasks; } ;
struct ecore_fcoe_pf_params {int num_cons; int /*<<< orphan*/  num_tasks; } ;
struct ecore_eth_pf_params {int num_cons; int num_arfs_filters; int /*<<< orphan*/  num_vf_cons; } ;
struct TYPE_7__ {struct ecore_iscsi_pf_params iscsi_pf_params; struct ecore_fcoe_pf_params fcoe_pf_params; struct ecore_eth_pf_params eth_pf_params; int /*<<< orphan*/  rdma_pf_params; } ;
struct TYPE_5__ {int personality; } ;
struct ecore_hwfn {TYPE_4__* p_dev; TYPE_3__ pf_params; TYPE_2__* p_cxt_mngr; TYPE_1__ hw_info; scalar_t__ using_ll2; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_8__ {int /*<<< orphan*/  mf_bits; } ;
struct TYPE_6__ {int arfs_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_INFO (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  ECORE_CXT_FCOE_TID_SEG ; 
 int /*<<< orphan*/  ECORE_CXT_ISCSI_TID_SEG ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MF_DISABLE_ARFS ; 
#define  ECORE_PCI_ETH 133 
#define  ECORE_PCI_ETH_IWARP 132 
#define  ECORE_PCI_ETH_RDMA 131 
#define  ECORE_PCI_ETH_ROCE 130 
#define  ECORE_PCI_FCOE 129 
#define  ECORE_PCI_ISCSI 128 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_PF_PARAMS_VF_CONS_DEFAULT ; 
 int /*<<< orphan*/  OSAL_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROTOCOLID_CORE ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int /*<<< orphan*/  PROTOCOLID_FCOE ; 
 int /*<<< orphan*/  PROTOCOLID_ISCSI ; 
 int /*<<< orphan*/  ecore_cxt_set_proto_cid_count (struct ecore_hwfn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_cxt_set_proto_tid_count (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecore_rdma_set_pf_params (struct ecore_hwfn*,int /*<<< orphan*/ *,int) ; 

enum _ecore_status_t ecore_cxt_set_pf_params(struct ecore_hwfn *p_hwfn,
					     u32 rdma_tasks)
{
	/* Set the number of required CORE connections */
	u32 core_cids = 1; /* SPQ */

	if (p_hwfn->using_ll2)
		core_cids += 4; /* @@@TBD Use the proper #define */

	ecore_cxt_set_proto_cid_count(p_hwfn, PROTOCOLID_CORE, core_cids, 0);

	switch (p_hwfn->hw_info.personality) {
	case ECORE_PCI_ETH_RDMA:
	case ECORE_PCI_ETH_IWARP:
	case ECORE_PCI_ETH_ROCE:
	{
		ecore_rdma_set_pf_params(p_hwfn,
					 &p_hwfn->pf_params.rdma_pf_params,
					 rdma_tasks);

		/* no need for break since RoCE coexist with Ethernet */
	}
	case ECORE_PCI_ETH:
	{
		u32 count = 0;

		struct ecore_eth_pf_params *p_params =
					&p_hwfn->pf_params.eth_pf_params;

		if (!p_params->num_vf_cons)
			p_params->num_vf_cons = ETH_PF_PARAMS_VF_CONS_DEFAULT;
		ecore_cxt_set_proto_cid_count(p_hwfn, PROTOCOLID_ETH,
					      p_params->num_cons,
					      p_params->num_vf_cons);

		count = p_params->num_arfs_filters;

		if (!OSAL_TEST_BIT(ECORE_MF_DISABLE_ARFS,
				   &p_hwfn->p_dev->mf_bits))
			p_hwfn->p_cxt_mngr->arfs_count = count;

		break;
	}
	case ECORE_PCI_FCOE:
	{
		struct ecore_fcoe_pf_params *p_params;

		p_params = &p_hwfn->pf_params.fcoe_pf_params;

		if (p_params->num_cons && p_params->num_tasks) {
			ecore_cxt_set_proto_cid_count(p_hwfn, PROTOCOLID_FCOE,
						      p_params->num_cons, 0);

			ecore_cxt_set_proto_tid_count(p_hwfn, PROTOCOLID_FCOE,
						      ECORE_CXT_FCOE_TID_SEG,
						      0, /* segment type */
						      p_params->num_tasks,
						      true);
		} else {
			DP_INFO(p_hwfn->p_dev,
				"Fcoe personality used without setting params!\n");
		}
		break;
	}
	case ECORE_PCI_ISCSI:
	{
		struct ecore_iscsi_pf_params *p_params;

		p_params = &p_hwfn->pf_params.iscsi_pf_params;

		if (p_params->num_cons && p_params->num_tasks) {
			ecore_cxt_set_proto_cid_count(p_hwfn, PROTOCOLID_ISCSI,
						      p_params->num_cons, 0);

			ecore_cxt_set_proto_tid_count(p_hwfn, PROTOCOLID_ISCSI,
						      ECORE_CXT_ISCSI_TID_SEG,
						      0, /* segment type */
						      p_params->num_tasks,
						      true);
		} else {
			DP_INFO(p_hwfn->p_dev,
				"Iscsi personality used without setting params!\n");
		}
		break;
	}
	default:
		return ECORE_INVAL;
	}

	return ECORE_SUCCESS;
}