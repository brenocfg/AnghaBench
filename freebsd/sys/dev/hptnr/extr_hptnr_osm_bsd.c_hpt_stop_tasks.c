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
typedef  int /*<<< orphan*/  ids ;
typedef  int /*<<< orphan*/  PVBUS_EXT ;
typedef  int /*<<< orphan*/  DEVICEID ;

/* Variables and functions */
 int /*<<< orphan*/  __hpt_stop_tasks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hpt_get_logical_devices (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hpt_stop_tasks(PVBUS_EXT vbus_ext)
{
	DEVICEID ids[32];
	int i, count;

	count = hpt_get_logical_devices((DEVICEID *)&ids, sizeof(ids)/sizeof(ids[0]));
	
	for (i=0; i<count; i++)
		__hpt_stop_tasks(vbus_ext, ids[i]);
}