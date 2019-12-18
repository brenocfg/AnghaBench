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
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ x86bios_match_device (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dpms_identify(driver_t *driver, device_t parent)
{

	if (x86bios_match_device(0xc0000, device_get_parent(parent)))
		device_add_child(parent, "dpms", 0);
}