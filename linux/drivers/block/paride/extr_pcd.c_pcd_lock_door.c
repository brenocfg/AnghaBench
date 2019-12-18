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
struct cdrom_device_info {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int pcd_atapi (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcd_scratch ; 

__attribute__((used)) static int pcd_lock_door(struct cdrom_device_info *cdi, int lock)
{
	char un_cmd[12] = { 0x1e, 0, 0, 0, lock, 0, 0, 0, 0, 0, 0, 0 };

	return pcd_atapi(cdi->handle, un_cmd, 0, pcd_scratch,
			 lock ? "lock door" : "unlock door");
}