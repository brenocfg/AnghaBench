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
typedef  int /*<<< orphan*/  uint8_t ;
struct adb_devinfo {int /*<<< orphan*/  handler_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct adb_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

uint8_t 
adb_get_device_handler(device_t dev) 
{
	struct adb_devinfo *dinfo;

	dinfo = device_get_ivars(dev);
	return (dinfo->handler_id);
}