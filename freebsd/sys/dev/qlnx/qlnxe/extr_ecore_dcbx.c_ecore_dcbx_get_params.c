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
struct ecore_hwfn {int dummy; } ;
struct ecore_dcbx_get {int dummy; } ;
typedef  enum ecore_mib_read_type { ____Placeholder_ecore_mib_read_type } ecore_mib_read_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
#define  ECORE_DCBX_LOCAL_LLDP_MIB 132 
#define  ECORE_DCBX_LOCAL_MIB 131 
#define  ECORE_DCBX_OPERATIONAL_MIB 130 
#define  ECORE_DCBX_REMOTE_LLDP_MIB 129 
#define  ECORE_DCBX_REMOTE_MIB 128 
 int ECORE_INVAL ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ecore_dcbx_get_local_lldp_params (struct ecore_hwfn*,struct ecore_dcbx_get*) ; 
 int /*<<< orphan*/  ecore_dcbx_get_local_params (struct ecore_hwfn*,struct ecore_dcbx_get*) ; 
 int /*<<< orphan*/  ecore_dcbx_get_operational_params (struct ecore_hwfn*,struct ecore_dcbx_get*) ; 
 int /*<<< orphan*/  ecore_dcbx_get_remote_lldp_params (struct ecore_hwfn*,struct ecore_dcbx_get*) ; 
 int /*<<< orphan*/  ecore_dcbx_get_remote_params (struct ecore_hwfn*,struct ecore_dcbx_get*) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_dcbx_get_params(struct ecore_hwfn *p_hwfn,
		      struct ecore_dcbx_get *p_params,
		      enum ecore_mib_read_type type)
{
	switch (type) {
	case ECORE_DCBX_REMOTE_MIB:
		ecore_dcbx_get_remote_params(p_hwfn, p_params);
		break;
	case ECORE_DCBX_LOCAL_MIB:
		ecore_dcbx_get_local_params(p_hwfn, p_params);
		break;
	case ECORE_DCBX_OPERATIONAL_MIB:
		ecore_dcbx_get_operational_params(p_hwfn, p_params);
		break;
	case ECORE_DCBX_REMOTE_LLDP_MIB:
		ecore_dcbx_get_remote_lldp_params(p_hwfn, p_params);
		break;
	case ECORE_DCBX_LOCAL_LLDP_MIB:
		ecore_dcbx_get_local_lldp_params(p_hwfn, p_params);
		break;
	default:
		DP_ERR(p_hwfn, "MIB read err, unknown mib type %d\n", type);
		return ECORE_INVAL;
	}

	return ECORE_SUCCESS;
}