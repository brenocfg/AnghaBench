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
struct TYPE_2__ {int personality; } ;
struct ecore_hwfn {TYPE_1__ hw_info; int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
#define  ECORE_PCI_ETH 132 
#define  ECORE_PCI_ETH_IWARP 131 
#define  ECORE_PCI_ETH_ROCE 130 
#define  ECORE_PCI_FCOE 129 
#define  ECORE_PCI_ISCSI 128 
 scalar_t__ IS_ECORE_DCQCN (struct ecore_hwfn*) ; 
 scalar_t__ IS_ECORE_SRIOV (int /*<<< orphan*/ ) ; 
 int PQ_FLAGS_ACK ; 
 int PQ_FLAGS_LB ; 
 int PQ_FLAGS_LLT ; 
 int PQ_FLAGS_MCOS ; 
 int PQ_FLAGS_OFLD ; 
 int PQ_FLAGS_OOO ; 
 int PQ_FLAGS_RLS ; 
 int PQ_FLAGS_VFS ; 

__attribute__((used)) static u32 ecore_get_pq_flags(struct ecore_hwfn *p_hwfn)
{
	u32 flags;

	/* common flags */
	flags = PQ_FLAGS_LB;

	/* feature flags */
	if (IS_ECORE_SRIOV(p_hwfn->p_dev))
		flags |= PQ_FLAGS_VFS;
	if (IS_ECORE_DCQCN(p_hwfn))
		flags |= PQ_FLAGS_RLS;

	/* protocol flags */
	switch (p_hwfn->hw_info.personality) {
	case ECORE_PCI_ETH:
		flags |= PQ_FLAGS_MCOS;
		break;
	case ECORE_PCI_FCOE:
		flags |= PQ_FLAGS_OFLD;
		break;
	case ECORE_PCI_ISCSI:
		flags |= PQ_FLAGS_ACK | PQ_FLAGS_OOO | PQ_FLAGS_OFLD;
		break;
	case ECORE_PCI_ETH_ROCE:
		flags |= PQ_FLAGS_MCOS | PQ_FLAGS_OFLD | PQ_FLAGS_LLT;
		break;
	case ECORE_PCI_ETH_IWARP:
		flags |= PQ_FLAGS_MCOS | PQ_FLAGS_ACK | PQ_FLAGS_OOO | PQ_FLAGS_OFLD;
		break;
	default:
		DP_ERR(p_hwfn, "unknown personality %d\n", p_hwfn->hw_info.personality);
		return 0;
	}

	return flags;
}