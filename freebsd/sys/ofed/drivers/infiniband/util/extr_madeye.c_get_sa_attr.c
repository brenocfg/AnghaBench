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
typedef  int __be16 ;

/* Variables and functions */
#define  IB_SA_ATTR_CLASS_PORTINFO 149 
#define  IB_SA_ATTR_GUID_INFO_REC 148 
#define  IB_SA_ATTR_INFORM_INFO 147 
#define  IB_SA_ATTR_INFORM_INFO_REC 146 
#define  IB_SA_ATTR_LINEAR_FDB_REC 145 
#define  IB_SA_ATTR_LINK_REC 144 
#define  IB_SA_ATTR_MCAST_FDB_REC 143 
#define  IB_SA_ATTR_MC_MEMBER_REC 142 
#define  IB_SA_ATTR_MULTI_PATH_REC 141 
#define  IB_SA_ATTR_NODE_REC 140 
#define  IB_SA_ATTR_NOTICE 139 
#define  IB_SA_ATTR_PARTITION_REC 138 
#define  IB_SA_ATTR_PATH_REC 137 
#define  IB_SA_ATTR_PORT_INFO_REC 136 
#define  IB_SA_ATTR_RANDOM_FDB_REC 135 
#define  IB_SA_ATTR_SERVICE_ASSOC_REC 134 
#define  IB_SA_ATTR_SERVICE_REC 133 
#define  IB_SA_ATTR_SL2VL_REC 132 
#define  IB_SA_ATTR_SM_INFO_REC 131 
#define  IB_SA_ATTR_SWITCH_REC 130 
#define  IB_SA_ATTR_TRACE_REC 129 
#define  IB_SA_ATTR_VL_ARB_REC 128 

__attribute__((used)) static char * get_sa_attr(__be16 attr)
{
	switch(attr) {
	case IB_SA_ATTR_CLASS_PORTINFO:
		return "Class Port Info";
	case IB_SA_ATTR_NOTICE:
		return "Notice";
	case IB_SA_ATTR_INFORM_INFO:
		return "Inform Info";
	case IB_SA_ATTR_NODE_REC:
		return "Node Record";
	case IB_SA_ATTR_PORT_INFO_REC:
		return "PortInfo Record";
	case IB_SA_ATTR_SL2VL_REC:
		return "SL to VL Record";
	case IB_SA_ATTR_SWITCH_REC:
		return "Switch Record";
	case IB_SA_ATTR_LINEAR_FDB_REC:
		return "Linear FDB Record";
	case IB_SA_ATTR_RANDOM_FDB_REC:
		return "Random FDB Record";
	case IB_SA_ATTR_MCAST_FDB_REC:
		return "Multicast FDB Record";
	case IB_SA_ATTR_SM_INFO_REC:
		return "SM Info Record";
	case IB_SA_ATTR_LINK_REC:
		return "Link Record";
	case IB_SA_ATTR_GUID_INFO_REC:
		return "Guid Info Record";
	case IB_SA_ATTR_SERVICE_REC:
		return "Service Record";
	case IB_SA_ATTR_PARTITION_REC:
		return "Partition Record";
	case IB_SA_ATTR_PATH_REC:
		return "Path Record";
	case IB_SA_ATTR_VL_ARB_REC:
		return "VL Arb Record";
	case IB_SA_ATTR_MC_MEMBER_REC:
		return "MC Member Record";
	case IB_SA_ATTR_TRACE_REC:
		return "Trace Record";
	case IB_SA_ATTR_MULTI_PATH_REC:
		return "Multi Path Record";
	case IB_SA_ATTR_SERVICE_ASSOC_REC:
		return "Service Assoc Record";
	case IB_SA_ATTR_INFORM_INFO_REC:
		return "Inform Info Record";
	default:
		return "";
	}
}