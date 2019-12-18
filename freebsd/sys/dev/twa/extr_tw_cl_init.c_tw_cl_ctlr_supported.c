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
typedef  scalar_t__ TW_INT32 ;

/* Variables and functions */
 scalar_t__ TW_CL_DEVICE_ID_9K ; 
 scalar_t__ TW_CL_DEVICE_ID_9K_E ; 
 scalar_t__ TW_CL_DEVICE_ID_9K_SA ; 
 scalar_t__ TW_CL_DEVICE_ID_9K_X ; 
 scalar_t__ TW_CL_FALSE ; 
 scalar_t__ TW_CL_TRUE ; 
 scalar_t__ TW_CL_VENDOR_ID ; 

TW_INT32
tw_cl_ctlr_supported(TW_INT32 vendor_id, TW_INT32 device_id)
{
	if ((vendor_id == TW_CL_VENDOR_ID) &&
		((device_id == TW_CL_DEVICE_ID_9K) ||
		 (device_id == TW_CL_DEVICE_ID_9K_X) ||
		 (device_id == TW_CL_DEVICE_ID_9K_E) ||
		 (device_id == TW_CL_DEVICE_ID_9K_SA)))
		return(TW_CL_TRUE);
	return(TW_CL_FALSE);
}