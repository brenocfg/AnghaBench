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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ IB_MGMT_CLASS_VENDOR_RANGE2_END ; 
 scalar_t__ IB_MGMT_CLASS_VENDOR_RANGE2_START ; 

__attribute__((used)) static int is_vendor_class(u8 mgmt_class)
{
	if ((mgmt_class < IB_MGMT_CLASS_VENDOR_RANGE2_START) ||
	    (mgmt_class > IB_MGMT_CLASS_VENDOR_RANGE2_END))
		return 0;
	return 1;
}