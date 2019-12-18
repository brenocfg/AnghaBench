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
#define  IB_MGMT_RMPP_TYPE_ABORT 131 
#define  IB_MGMT_RMPP_TYPE_ACK 130 
#define  IB_MGMT_RMPP_TYPE_DATA 129 
#define  IB_MGMT_RMPP_TYPE_STOP 128 

__attribute__((used)) static char * get_rmpp_type(u8 rmpp_type)
{
	switch (rmpp_type) {
	case IB_MGMT_RMPP_TYPE_DATA:
		return "Data";
	case IB_MGMT_RMPP_TYPE_ACK:
		return "Ack";
	case IB_MGMT_RMPP_TYPE_STOP:
		return "Stop";
	case IB_MGMT_RMPP_TYPE_ABORT:
		return "Abort";
	default:
		return "Unknown";
	}
}