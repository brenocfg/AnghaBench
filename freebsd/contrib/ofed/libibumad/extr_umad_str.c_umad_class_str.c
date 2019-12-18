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
typedef  int uint8_t ;

/* Variables and functions */
 int UMAD_CLASS_APPLICATION_END ; 
 int UMAD_CLASS_APPLICATION_START ; 
#define  UMAD_CLASS_BIS 139 
#define  UMAD_CLASS_BM 138 
#define  UMAD_CLASS_BOOT_MGMT 137 
#define  UMAD_CLASS_CM 136 
#define  UMAD_CLASS_CONG_MGMT 135 
#define  UMAD_CLASS_DEVICE_ADM 134 
#define  UMAD_CLASS_DEVICE_MGMT 133 
#define  UMAD_CLASS_PERF_MGMT 132 
#define  UMAD_CLASS_SNMP 131 
#define  UMAD_CLASS_SUBN_ADM 130 
#define  UMAD_CLASS_SUBN_DIRECTED_ROUTE 129 
#define  UMAD_CLASS_SUBN_LID_ROUTED 128 
 int UMAD_CLASS_VENDOR_RANGE1_END ; 
 int UMAD_CLASS_VENDOR_RANGE1_START ; 
 int UMAD_CLASS_VENDOR_RANGE2_END ; 
 int UMAD_CLASS_VENDOR_RANGE2_START ; 

const char * umad_class_str(uint8_t mgmt_class)
{
	switch (mgmt_class) {
		case UMAD_CLASS_SUBN_LID_ROUTED:
		case UMAD_CLASS_SUBN_DIRECTED_ROUTE:
			return("Subn");
		case UMAD_CLASS_SUBN_ADM:
			return("SubnAdm");
		case UMAD_CLASS_PERF_MGMT:
			return("Perf");
		case UMAD_CLASS_BM:
			return("BM");
		case UMAD_CLASS_DEVICE_MGMT:
			return("DevMgt");
		case UMAD_CLASS_CM:
			return("ComMgt");
		case UMAD_CLASS_SNMP:
			return("SNMP");
		case UMAD_CLASS_DEVICE_ADM:
			return("DevAdm");
		case UMAD_CLASS_BOOT_MGMT:
			return("BootMgt");
		case UMAD_CLASS_BIS:
			return("BIS");
		case UMAD_CLASS_CONG_MGMT:
			return("CongestionManagment");
		default:
			break;
	}

	if ((UMAD_CLASS_VENDOR_RANGE1_START <= mgmt_class
		&& mgmt_class <= UMAD_CLASS_VENDOR_RANGE1_END)
	    || (UMAD_CLASS_VENDOR_RANGE2_START <= mgmt_class
		&& mgmt_class <= UMAD_CLASS_VENDOR_RANGE2_END))
		return("Vendor");

	if (UMAD_CLASS_APPLICATION_START <= mgmt_class
	    && mgmt_class <= UMAD_CLASS_APPLICATION_END) {
		return("Application");
	}
	return ("<unknown>");
}