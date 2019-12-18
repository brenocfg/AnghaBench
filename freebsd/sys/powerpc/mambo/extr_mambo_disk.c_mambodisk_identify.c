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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MAMBO_DISK_INFO ; 
 int /*<<< orphan*/  MAMBO_INFO_DEVSZ ; 
 scalar_t__ mambocall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mambodisk_identify(driver_t *driver, device_t parent)
{
	int i = 0;

	for (i = 0; mambocall(MAMBO_DISK_INFO,MAMBO_INFO_DEVSZ,i) > 0; i++)
		BUS_ADD_CHILD(parent,0,"mambodisk",i);
}