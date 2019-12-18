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

/* Variables and functions */
#define  IB_BOARD_MGMT_CLASS 134 
#define  IB_CC_CLASS 133 
#define  IB_DEVICE_MGMT_CLASS 132 
#define  IB_PERFORMANCE_CLASS 131 
#define  IB_SA_CLASS 130 
#define  IB_SMI_CLASS 129 
#define  IB_SMI_DIRECT_CLASS 128 
 int IB_VENDOR_RANGE1_END_CLASS ; 
 int IB_VENDOR_RANGE1_START_CLASS ; 
 int IB_VENDOR_RANGE2_END_CLASS ; 
 int IB_VENDOR_RANGE2_START_CLASS ; 

__attribute__((used)) static int mgmt_class_vers(int mgmt_class)
{
	if ((mgmt_class >= IB_VENDOR_RANGE1_START_CLASS &&
	     mgmt_class <= IB_VENDOR_RANGE1_END_CLASS) ||
	    (mgmt_class >= IB_VENDOR_RANGE2_START_CLASS &&
	     mgmt_class <= IB_VENDOR_RANGE2_END_CLASS))
		return 1;

	switch (mgmt_class) {
	case IB_SMI_CLASS:
	case IB_SMI_DIRECT_CLASS:
		return 1;
	case IB_SA_CLASS:
		return 2;
	case IB_PERFORMANCE_CLASS:
		return 1;
	case IB_DEVICE_MGMT_CLASS:
		return 1;
	case IB_CC_CLASS:
		return 2;
	case IB_BOARD_MGMT_CLASS:
		return 1;
	}

	return 0;
}