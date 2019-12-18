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
typedef  int /*<<< orphan*/  PLOGICAL_DEVICE_INFO_V3 ;
typedef  int /*<<< orphan*/  LOGICAL_DEVICE_INFO_V3 ;
typedef  int /*<<< orphan*/  DEVICEID ;

/* Variables and functions */
 int HPT_DO_IOCTL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPT_IOCTL_GET_DEVICE_INFO_V3 ; 

__attribute__((used)) static int hpt_get_device_info_v3(DEVICEID id, PLOGICAL_DEVICE_INFO_V3 pInfo)
{
	return HPT_DO_IOCTL(HPT_IOCTL_GET_DEVICE_INFO_V3,
				&id, sizeof(DEVICEID), pInfo, sizeof(LOGICAL_DEVICE_INFO_V3));
}