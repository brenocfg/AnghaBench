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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  UMAD_SA_ATTR_CABLE_INFO_REC 150 
#define  UMAD_SA_ATTR_GUID_INFO_REC 149 
#define  UMAD_SA_ATTR_HIERARCHY_INFO_REC 148 
#define  UMAD_SA_ATTR_INFORM_INFO_REC 147 
#define  UMAD_SA_ATTR_LINEAR_FT_REC 146 
#define  UMAD_SA_ATTR_LINK_REC 145 
#define  UMAD_SA_ATTR_LINK_SPD_WIDTH_TABLE_REC 144 
#define  UMAD_SA_ATTR_MCAST_FT_REC 143 
#define  UMAD_SA_ATTR_MCMEMBER_REC 142 
#define  UMAD_SA_ATTR_MULTI_PATH_REC 141 
#define  UMAD_SA_ATTR_NODE_REC 140 
#define  UMAD_SA_ATTR_PATH_REC 139 
#define  UMAD_SA_ATTR_PKEY_TABLE_REC 138 
#define  UMAD_SA_ATTR_PORT_INFO_EXT_REC 137 
#define  UMAD_SA_ATTR_PORT_INFO_REC 136 
#define  UMAD_SA_ATTR_RANDOM_FT_REC 135 
#define  UMAD_SA_ATTR_SERVICE_ASSOC_REC 134 
#define  UMAD_SA_ATTR_SERVICE_REC 133 
#define  UMAD_SA_ATTR_SLVL_REC 132 
#define  UMAD_SA_ATTR_SM_INFO_REC 131 
#define  UMAD_SA_ATTR_SWITCH_INFO_REC 130 
#define  UMAD_SA_ATTR_TRACE_REC 129 
#define  UMAD_SA_ATTR_VL_ARB_REC 128 
 int be16toh (int /*<<< orphan*/ ) ; 
 char const* umad_common_attr_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char * umad_sa_attr_str(__be16 attr_id)
{
	switch(be16toh(attr_id)) {
		case UMAD_SA_ATTR_NODE_REC:
			return ("NodeRecord");
		case UMAD_SA_ATTR_PORT_INFO_REC:
			return ("PortInfoRecord");
		case UMAD_SA_ATTR_SLVL_REC:
			return ("SLtoVLMappingTableRecord");
		case UMAD_SA_ATTR_SWITCH_INFO_REC:
			return ("SwitchInfoRecord");
		case UMAD_SA_ATTR_LINEAR_FT_REC:
			return ("LinearForwardingTableRecord");
		case UMAD_SA_ATTR_RANDOM_FT_REC:
			return ("RandomForwardingTableRecord");
		case UMAD_SA_ATTR_MCAST_FT_REC:
			return ("MulticastForwardingTableRecord");
		case UMAD_SA_ATTR_SM_INFO_REC:
			return ("SMInfoRecord");
		case UMAD_SA_ATTR_INFORM_INFO_REC:
			return ("InformInfoRecord");
		case UMAD_SA_ATTR_LINK_REC:
			return ("LinkRecord");
		case UMAD_SA_ATTR_GUID_INFO_REC:
			return ("GuidInfoRecord");
		case UMAD_SA_ATTR_SERVICE_REC:
			return ("ServiceRecord");
		case UMAD_SA_ATTR_PKEY_TABLE_REC:
			return ("P_KeyTableRecord");
		case UMAD_SA_ATTR_PATH_REC:
			return ("PathRecord");
		case UMAD_SA_ATTR_VL_ARB_REC:
			return ("VLArbitrationTableRecord");
		case UMAD_SA_ATTR_MCMEMBER_REC:
			return ("MCMemberRecord");
		case UMAD_SA_ATTR_TRACE_REC:
			return ("TraceRecord");
		case UMAD_SA_ATTR_MULTI_PATH_REC:
			return ("MultiPathRecord");
		case UMAD_SA_ATTR_SERVICE_ASSOC_REC:
			return ("ServiceAssociationRecord");
		case UMAD_SA_ATTR_LINK_SPD_WIDTH_TABLE_REC:
			return ("LinkSpeedWidthPairsTableRecord");
		case UMAD_SA_ATTR_HIERARCHY_INFO_REC:
			return ("HierarchyInfoRecord");
		case UMAD_SA_ATTR_CABLE_INFO_REC:
			return ("CableInfoRecord");
		case UMAD_SA_ATTR_PORT_INFO_EXT_REC:
			return ("PortInfoExtendedRecord");
		default:
			return (umad_common_attr_str(attr_id));
	}
	return ("<unknown>");
}