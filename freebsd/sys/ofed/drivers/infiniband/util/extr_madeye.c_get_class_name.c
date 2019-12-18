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
typedef  int u8 ;

/* Variables and functions */
#define  IB_MGMT_CLASS_BM 135 
#define  IB_MGMT_CLASS_CM 134 
#define  IB_MGMT_CLASS_DEVICE_MGMT 133 
#define  IB_MGMT_CLASS_PERF_MGMT 132 
#define  IB_MGMT_CLASS_SNMP 131 
#define  IB_MGMT_CLASS_SUBN_ADM 130 
#define  IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE 129 
#define  IB_MGMT_CLASS_SUBN_LID_ROUTED 128 

__attribute__((used)) static char * get_class_name(u8 mgmt_class)
{
	switch(mgmt_class) {
	case IB_MGMT_CLASS_SUBN_LID_ROUTED:
		return "LID routed SMP";
	case IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE:
		return "Directed route SMP";
	case IB_MGMT_CLASS_SUBN_ADM:
		return "Subnet admin.";
	case IB_MGMT_CLASS_PERF_MGMT:
		return "Perf. mgmt.";
	case IB_MGMT_CLASS_BM:
		return "Baseboard mgmt.";
	case IB_MGMT_CLASS_DEVICE_MGMT:
		return "Device mgmt.";
	case IB_MGMT_CLASS_CM:
		return "Comm. mgmt.";
	case IB_MGMT_CLASS_SNMP:
		return "SNMP";
	default:
		return "Unknown vendor/application";
	}
}