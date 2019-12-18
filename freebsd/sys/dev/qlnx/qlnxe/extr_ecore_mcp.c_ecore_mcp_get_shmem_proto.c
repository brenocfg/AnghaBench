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
struct public_func {int config; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum ecore_pci_personality { ____Placeholder_ecore_pci_personality } ecore_pci_personality ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_INVAL ; 
 int ECORE_PCI_FCOE ; 
 int ECORE_PCI_ISCSI ; 
 int ECORE_SUCCESS ; 
#define  FUNC_MF_CFG_PROTOCOL_ETHERNET 131 
#define  FUNC_MF_CFG_PROTOCOL_FCOE 130 
#define  FUNC_MF_CFG_PROTOCOL_ISCSI 129 
 int FUNC_MF_CFG_PROTOCOL_MASK ; 
#define  FUNC_MF_CFG_PROTOCOL_ROCE 128 
 int /*<<< orphan*/  ecore_mcp_get_shmem_proto_legacy (struct ecore_hwfn*,int*) ; 
 int ecore_mcp_get_shmem_proto_mfw (struct ecore_hwfn*,struct ecore_ptt*,int*) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_mcp_get_shmem_proto(struct ecore_hwfn *p_hwfn,
			  struct public_func *p_info,
			  struct ecore_ptt *p_ptt,
			  enum ecore_pci_personality *p_proto)
{
	enum _ecore_status_t rc = ECORE_SUCCESS;

	switch (p_info->config & FUNC_MF_CFG_PROTOCOL_MASK) {
	case FUNC_MF_CFG_PROTOCOL_ETHERNET:
		if (ecore_mcp_get_shmem_proto_mfw(p_hwfn, p_ptt, p_proto) !=
		    ECORE_SUCCESS)
			ecore_mcp_get_shmem_proto_legacy(p_hwfn, p_proto);
		break;
	case FUNC_MF_CFG_PROTOCOL_ISCSI:
		*p_proto = ECORE_PCI_ISCSI;
		break;
	case FUNC_MF_CFG_PROTOCOL_FCOE:
		*p_proto = ECORE_PCI_FCOE;
		break;
	case FUNC_MF_CFG_PROTOCOL_ROCE:
		DP_NOTICE(p_hwfn, true, "RoCE personality is not a valid value!\n");
		/* Fallthrough */
	default:
		rc = ECORE_INVAL;
	}

	return rc;
}