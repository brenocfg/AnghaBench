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
 int IB_MGMT_RMPP_FLAG_ACTIVE ; 
 int IB_MGMT_RMPP_FLAG_FIRST ; 
 int IB_MGMT_RMPP_FLAG_LAST ; 

__attribute__((used)) static char * get_rmpp_flags(u8 rmpp_flags)
{
	if (rmpp_flags & IB_MGMT_RMPP_FLAG_ACTIVE)
		if (rmpp_flags & IB_MGMT_RMPP_FLAG_FIRST)
			if (rmpp_flags & IB_MGMT_RMPP_FLAG_LAST)
				return "Active - First & Last";
			else
				return "Active - First";
		else
			if (rmpp_flags & IB_MGMT_RMPP_FLAG_LAST)
				return "Active - Last";
			else
				return "Active";
	else
		return "Inactive";
}