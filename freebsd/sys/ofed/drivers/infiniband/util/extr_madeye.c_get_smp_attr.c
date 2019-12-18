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
#define  IB_SMP_ATTR_GUID_INFO 142 
#define  IB_SMP_ATTR_LED_INFO 141 
#define  IB_SMP_ATTR_LINEAR_FORWARD_TABLE 140 
#define  IB_SMP_ATTR_MCAST_FORWARD_TABLE 139 
#define  IB_SMP_ATTR_NODE_DESC 138 
#define  IB_SMP_ATTR_NODE_INFO 137 
#define  IB_SMP_ATTR_NOTICE 136 
#define  IB_SMP_ATTR_PKEY_TABLE 135 
#define  IB_SMP_ATTR_PORT_INFO 134 
#define  IB_SMP_ATTR_RANDOM_FORWARD_TABLE 133 
#define  IB_SMP_ATTR_SL_TO_VL_TABLE 132 
#define  IB_SMP_ATTR_SM_INFO 131 
#define  IB_SMP_ATTR_SWITCH_INFO 130 
#define  IB_SMP_ATTR_VENDOR_DIAG 129 
#define  IB_SMP_ATTR_VL_ARB_TABLE 128 

__attribute__((used)) static char * get_smp_attr(__be16 attr)
{
	switch (attr) {
	case IB_SMP_ATTR_NOTICE:
		return "notice";
	case IB_SMP_ATTR_NODE_DESC:
		return "node description";
	case IB_SMP_ATTR_NODE_INFO:
		return "node info";
	case IB_SMP_ATTR_SWITCH_INFO:
		return "switch info";
	case IB_SMP_ATTR_GUID_INFO:
		return "GUID info";
	case IB_SMP_ATTR_PORT_INFO:
		return "port info";
	case IB_SMP_ATTR_PKEY_TABLE:
		return "pkey table";
	case IB_SMP_ATTR_SL_TO_VL_TABLE:
		return "SL to VL table";
	case IB_SMP_ATTR_VL_ARB_TABLE:
		return "VL arbitration table";
	case IB_SMP_ATTR_LINEAR_FORWARD_TABLE:
		return "linear forwarding table";
	case IB_SMP_ATTR_RANDOM_FORWARD_TABLE:
		return "random forward table";
	case IB_SMP_ATTR_MCAST_FORWARD_TABLE:
		return "multicast forward table";
	case IB_SMP_ATTR_SM_INFO:
		return "SM info";
	case IB_SMP_ATTR_VENDOR_DIAG:
		return "vendor diags";
	case IB_SMP_ATTR_LED_INFO:
		return "LED info";
	default:
		return "";
	}
}