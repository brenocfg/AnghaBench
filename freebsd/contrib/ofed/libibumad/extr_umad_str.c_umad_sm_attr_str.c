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
#define  UMAD_SM_ATTR_CABLE_INFO 146 
#define  UMAD_SM_ATTR_GUID_INFO 145 
#define  UMAD_SM_ATTR_HIERARCHY_INFO 144 
#define  UMAD_SM_ATTR_LED_INFO 143 
#define  UMAD_SM_ATTR_LINEAR_FT 142 
#define  UMAD_SM_ATTR_LINK_SPD_WIDTH_TABLE 141 
#define  UMAD_SM_ATTR_MCAST_FT 140 
#define  UMAD_SM_ATTR_NODE_DESC 139 
#define  UMAD_SM_ATTR_NODE_INFO 138 
#define  UMAD_SM_ATTR_PKEY_TABLE 137 
#define  UMAD_SM_ATTR_PORT_INFO 136 
#define  UMAD_SM_ATTR_PORT_INFO_EXT 135 
#define  UMAD_SM_ATTR_RANDOM_FT 134 
#define  UMAD_SM_ATTR_SLVL_TABLE 133 
#define  UMAD_SM_ATTR_SM_INFO 132 
#define  UMAD_SM_ATTR_SWITCH_INFO 131 
#define  UMAD_SM_ATTR_VENDOR_DIAG 130 
#define  UMAD_SM_ATTR_VENDOR_MADS_TABLE 129 
#define  UMAD_SM_ATTR_VL_ARB_TABLE 128 
 int be16toh (int /*<<< orphan*/ ) ; 
 char const* umad_common_attr_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char * umad_sm_attr_str(__be16 attr_id)
{
	switch(be16toh(attr_id)) {
		case UMAD_SM_ATTR_NODE_DESC:
			return ("NodeDescription");
		case UMAD_SM_ATTR_NODE_INFO:
			return ("NodeInfo");
		case UMAD_SM_ATTR_SWITCH_INFO:
			return ("SwitchInfo");
		case UMAD_SM_ATTR_GUID_INFO:
			return ("GUIDInfo");
		case UMAD_SM_ATTR_PORT_INFO:
			return ("PortInfo");
		case UMAD_SM_ATTR_PKEY_TABLE:
			return ("P_KeyTable");
		case UMAD_SM_ATTR_SLVL_TABLE:
			return ("SLtoVLMappingTable");
		case UMAD_SM_ATTR_VL_ARB_TABLE:
			return ("VLArbitrationTable");
		case UMAD_SM_ATTR_LINEAR_FT:
			return ("LinearForwardingTable");
		case UMAD_SM_ATTR_RANDOM_FT:
			return ("RandomForwardingTable");
		case UMAD_SM_ATTR_MCAST_FT:
			return ("MulticastForwardingTable");
		case UMAD_SM_ATTR_SM_INFO:
			return ("SMInfo");
		case UMAD_SM_ATTR_VENDOR_DIAG:
			return ("VendorDiag");
		case UMAD_SM_ATTR_LED_INFO:
			return ("LedInfo");
		case UMAD_SM_ATTR_LINK_SPD_WIDTH_TABLE:
			return ("LinkSpeedWidthPairsTable");
		case UMAD_SM_ATTR_VENDOR_MADS_TABLE:
			return ("VendorSpecificMadsTable");
		case UMAD_SM_ATTR_HIERARCHY_INFO:
			return ("HierarchyInfo");
		case UMAD_SM_ATTR_CABLE_INFO:
			return ("CableInfo");
		case UMAD_SM_ATTR_PORT_INFO_EXT:
			return ("PortInfoExtended");
		default:
			return (umad_common_attr_str(attr_id));
	}
	return ("<unknown>");
}