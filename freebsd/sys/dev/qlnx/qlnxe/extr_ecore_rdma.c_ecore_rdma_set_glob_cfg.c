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
typedef  int u32 ;
struct ecore_rdma_glob_cfg {scalar_t__ dscp; int dscp_en; scalar_t__ ecn; int ecn_en; scalar_t__ vlan_pri; int vlan_pri_en; } ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  glob_cfg ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {struct ecore_rdma_glob_cfg glob_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  DP_VERBOSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int,scalar_t__,int,scalar_t__,int) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_RDMA_DCSP_BIT_MASK ; 
 int ECORE_RDMA_DCSP_EN_BIT_MASK ; 
 int ECORE_RDMA_ECN_BIT_MASK ; 
 int ECORE_RDMA_ECN_EN_BIT_MASK ; 
 int ECORE_RDMA_VLAN_PRIO_BIT_MASK ; 
 int ECORE_RDMA_VLAN_PRIO_EN_BIT_MASK ; 
 int ECORE_SUCCESS ; 
 scalar_t__ INET_ECN_ECT_0 ; 
 scalar_t__ MAX_DSCP ; 
 scalar_t__ MAX_VLAN_PRIO ; 
 int /*<<< orphan*/  OSAL_MEMCPY (struct ecore_rdma_glob_cfg*,struct ecore_rdma_glob_cfg*,int) ; 

enum _ecore_status_t
ecore_rdma_set_glob_cfg(struct ecore_hwfn *p_hwfn,
			struct ecore_rdma_glob_cfg *in_params,
			u32 glob_cfg_bits)
{
	struct ecore_rdma_glob_cfg glob_cfg;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	DP_VERBOSE(p_hwfn->p_dev, ECORE_MSG_RDMA,
		   "dscp %d dscp en %d ecn %d ecn en %d vlan pri %d vlan_pri_en %d\n",
		   in_params->dscp, in_params->dscp_en,
		   in_params->ecn, in_params->ecn_en, in_params->vlan_pri,
		   in_params->vlan_pri_en);

	/* Read global cfg to local */
	OSAL_MEMCPY(&glob_cfg, &p_hwfn->p_rdma_info->glob_cfg,
		    sizeof(glob_cfg));

	if (glob_cfg_bits & ECORE_RDMA_DCSP_BIT_MASK) {
		if (in_params->dscp > MAX_DSCP) {
			DP_ERR(p_hwfn->p_dev, "invalid glob dscp %d\n",
			       in_params->dscp);
			return ECORE_INVAL;
		}
		glob_cfg.dscp = in_params->dscp;
	}

	if (glob_cfg_bits & ECORE_RDMA_DCSP_EN_BIT_MASK) {
		if (in_params->dscp_en > 1) {
			DP_ERR(p_hwfn->p_dev, "invalid glob_dscp_en %d\n",
			       in_params->dscp_en);
			return ECORE_INVAL;
		}
		glob_cfg.dscp_en = in_params->dscp_en;
	}

	if (glob_cfg_bits & ECORE_RDMA_ECN_BIT_MASK) {
		if (in_params->ecn > INET_ECN_ECT_0) {
			DP_ERR(p_hwfn->p_dev, "invalid glob ecn %d\n",
			       in_params->ecn);
			return ECORE_INVAL;
		}
		glob_cfg.ecn = in_params->ecn;
	}

	if (glob_cfg_bits & ECORE_RDMA_ECN_EN_BIT_MASK) {
		if (in_params->ecn_en > 1) {
			DP_ERR(p_hwfn->p_dev, "invalid glob ecn en %d\n",
			       in_params->ecn_en);
			return ECORE_INVAL;
		}
		glob_cfg.ecn_en = in_params->ecn_en;
	}

	if (glob_cfg_bits & ECORE_RDMA_VLAN_PRIO_BIT_MASK) {
		if (in_params->vlan_pri > MAX_VLAN_PRIO) {
			DP_ERR(p_hwfn->p_dev, "invalid glob vlan pri %d\n",
			       in_params->vlan_pri);
			return ECORE_INVAL;
		}
		glob_cfg.vlan_pri = in_params->vlan_pri;
	}

	if (glob_cfg_bits & ECORE_RDMA_VLAN_PRIO_EN_BIT_MASK) {
		if (in_params->vlan_pri_en > 1) {
			DP_ERR(p_hwfn->p_dev, "invalid glob vlan pri en %d\n",
			       in_params->vlan_pri_en);
			return ECORE_INVAL;
		}
		glob_cfg.vlan_pri_en = in_params->vlan_pri_en;
	}

	/* Write back local cfg to global */
	OSAL_MEMCPY(&p_hwfn->p_rdma_info->glob_cfg, &glob_cfg,
		    sizeof(glob_cfg));

	return rc;
}